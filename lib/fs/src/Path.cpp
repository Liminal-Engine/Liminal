/**
 * @file Path.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-25
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "Path.hpp"
#include "_private/_syntax.hpp"
#include "_private/_error/_Errors.hpp"

#include <sysop/sysop.hpp>
#include <parseop/parseop.hpp>
#include <logger/logger.hpp>

#include <vector>
#include <filesystem>
#include <string.h>
#include <fstream>

namespace fs {

    class Path::_PathImpl {

        private:         
            std::vector<Entry_t> _data;
            Resolution _resolution;

            static std::vector<Entry_t> _loadData(const std::string &inputStr) { // TODO : hanlde what to do if given empty string and test it
                if (inputStr.empty()) return std::vector<Entry_t>{};
                if ( parseop::isOnlyChar(inputStr, '/') ) return std::vector<Entry_t>{"/"}; // TODO: test this
                
                std::vector<Entry_t> res{parseop::tokenize(inputStr, _private::_syntax::PATH_SEPARATOR)};
                // FIXME: always make sure it is not empty ?
                // FIXME: this is wrong, a dir can have spaces at the end
                res[res.size() - 1] = parseop::trimEnd(res.at(res.size() - 1), ' ');
                return res;
            };

        public:
            _PathImpl(void) :
            _data{std::vector<Entry_t>{}},
            _resolution{Resolution::RELATIVE}
            {}

            _PathImpl(const std::string &path):
            _data{_PathImpl::_loadData(path)},
            _resolution{path.size() >= 1 && path.at(0) == '/' ? Resolution::ABSOLUTE : Resolution::RELATIVE}
            {}

            _PathImpl(const _PathImpl &pathImpl):
            _data{pathImpl._data},
            _resolution{pathImpl._resolution}
            {}

            // Setters

            Status insert(const Entry_t &entry) {
                return this->insert(entry, this->_data.size());
            }

            /**
             * @brief
             * 
             * @warning entry begining by '/' is only allowed if index is 0
             * 
             * @param entry 
             * @param index 
             * @return Status 
             */

            Status insert(const Entry_t &entry, const std::size_t &index) {
                if (entry == "") return Status::E_PATH_INVALID_ENTRY_NAME;
                if (index > this->_data.size()) return Status::E_PATH_INVALID_INDEX;

                const Resolution nextResolution = index == 0 && !entry.empty() && entry.at(0) == '/' ? Resolution::ABSOLUTE : this->_resolution;
                const Entry_t newEntry = !entry.empty() && entry.at(0) == '/' ? entry.substr(1) : entry; // remove '/' from new entry

                if ( parseop::includes(newEntry, std::vector<char>{_private::_syntax::FORBIDEN_CHARS.begin(), _private::_syntax::FORBIDEN_CHARS.end()} )) {
                        logger::error << "Wrong char in given entry. Entry is:  \'" << newEntry << '\'' << std::endl;
                        return Status::E_PATH_INVALID_ENTRY_NAME;
                }
                if ( !newEntry.empty() ) this->_data.insert(this->_data.begin() + index, newEntry);
                this->_resolution = nextResolution;
                return Status::OK;
            }

            Status clean(void) {
                if ( !(this->_data.empty() || this->_data.size() == 1 || this->_data.at(0) == "/") ) {
                    this->_data = parseop::tokenize(
                        std::filesystem::path{this->toStr()}.lexically_normal(),
                        _private::_syntax::PATH_SEPARATOR
                    );
                }
                return Status::OK;
            }

            // Getters
            std::optional<Entry_t> getEntry(void) const {
                return this->_data.empty() ? std::nullopt : std::optional<Entry_t>(this->_data.back());
            };

            std::optional<Entry_t> getEntry(const std::size_t &pos) const {
                return this->_data.empty() || pos >= this->_data.size() ? std::nullopt : std::optional<Entry_t>(this->_data.at(pos));
            };

            std::size_t getNEntry(void) const { return this->_data.size(); }

            std::optional<std::string> getExtension(void) const { // FIXME : value is returned even if "        "
                if (this->_data.empty()) return std::optional<std::string>();
                fs::Entry_t lastEntry{this->getEntry().value()};
                std::size_t dotPos{lastEntry.find(".")};
                
                if (dotPos == std::string::npos || dotPos + 1 >= lastEntry.size()) 
                    return std::optional<std::string>(std::nullopt);
                return lastEntry.substr(dotPos + 1, lastEntry.size());
            };

            Entry::Type getType(void) const {
                try {
                    std::filesystem::file_type stdFsType = std::filesystem::symlink_status(this->toStr()).type();

                    switch (stdFsType) {
                        case std::filesystem::file_type::regular:
                            return Entry::Type::REGULAR_FILE;
                        case std::filesystem::file_type::directory:
                            return Entry::Type::DIRECTORY;
                        case std::filesystem::file_type::symlink:
                            return Entry::Type::SYM_LINK;
                        case std::filesystem::file_type::block:
                            return Entry::Type::BLOCK_DEVICE;
                        case std::filesystem::file_type::character:
                            return Entry::Type::CHARACTER_DEVICE;
                        case std::filesystem::file_type::fifo:
                            return Entry::Type::FIFO;
                        case std::filesystem::file_type::socket:
                            return Entry::Type::SOCKET;
                        default:
                            return Entry::Type::UNKNOWN;
                    }
                }
                catch(...) {
                    return Entry::Type::UNKNOWN;
                }
            }

            bool isEmpty(void) const { return this->_data.empty(); }


            Resolution getResolution(void) const { return this->_resolution; }

            std::optional<Path> getParent(void) const {
                if (this->_data.empty() || this->_data.size() <= 1) return std::nullopt;

                std::vector<Entry_t> cpy = this->_data;
                if (this->_resolution == Resolution::ABSOLUTE && !cpy.at(0).empty()) cpy[0] = "/" + cpy[0];
                cpy.pop_back();
                fs::Path res{parseop::join(cpy, _private::_syntax::PATH_SEPARATOR)};
                return Path{parseop::join(cpy, _private::_syntax::PATH_SEPARATOR)};
            }

            bool operator==(const _PathImpl &other) {
                if (this->getResolution() != other.getResolution() || this->_data.size() != other._data.size()) return false;
                for (std::size_t i = 0; i < this->_data.size(); i++)
                    if (this->_data[i] != other._data[i]) return false;
                return true;
            }

            bool pointsTo(const Path &target) const {
                if (this->isEmpty() && target.isEmpty()) return true;
                fs::Path::_PathImpl targetCpy = *target._pImpl;
                fs::Path::_PathImpl thisCpy = *this;

                if (targetCpy.getResolution() != Resolution::ABSOLUTE)
                    if (targetCpy.toAbsolute() != Status::OK) return false;
                if (thisCpy.getResolution() != Resolution::ABSOLUTE)
                    if (thisCpy.toAbsolute() != Status::OK) return false;
                if (targetCpy.clean() != Status::OK || thisCpy.clean() != Status::OK) return false;
                return targetCpy == thisCpy;
            }

            Status toAbsolute(void) {
                if (this->_data.empty()) return Status::E_PATH_EMPTY;
                if ( this->_resolution == Resolution::RELATIVE ) {
                    *this = _PathImpl{ std::string{ sysop::getCWD().toStr() + "/" + this->toStr() } };
                    this->_resolution = Resolution::ABSOLUTE;
                }
                return Status::OK;
            }

            Status toRelative(void) {
                if (this->_data.empty()) return Status::E_PATH_EMPTY;
                if (this->_resolution == Resolution::ABSOLUTE) {
                    fs::Path cwd{sysop::getCWD()};
                    if (cwd == *this) this->_data = std::vector<Entry_t>{"."};
                    else {
                        std::vector<Entry_t> cwdEntries = cwd._pImpl->_data;
                        std::vector<Entry_t> thisEntries = this->_data;
                        while ( !cwdEntries.empty() && !thisEntries.empty() && cwdEntries.at(0) == thisEntries.at(0) ) {
                            cwdEntries.erase(cwdEntries.begin());
                            thisEntries.erase(thisEntries.begin());
                        }
                        for (std::size_t i = 0; i < cwdEntries.size(); i++) thisEntries.insert(thisEntries.begin(), "..");
                        this->_data = thisEntries;
                    }
                    this->_resolution = Resolution::RELATIVE;
                }
                return Status::OK;
            }

            bool exists(void) const { return std::filesystem::exists(std::filesystem::path(this->toStr())); }

            std::string toStr(void) const {
                return std::string{this->_resolution == Resolution::ABSOLUTE ? "/" : ""} + parseop::join(this->_data, _private::_syntax::PATH_SEPARATOR);
            };

            Status create(const Entry::Type &type, const bool &createParents) const {
                // 1. Setup: create vars
                if (this->exists()) return Status::E_ALREADY_EXISTS;
                fs::Path::_PathImpl tmpImpl = *this;
                Status tmpStatus = Status::NOK;
                if ( (tmpImpl.getResolution() != Resolution::ABSOLUTE) && (tmpStatus = tmpImpl.toAbsolute()) != Status::OK) return tmpStatus;
                if ( (tmpStatus = tmpImpl.clean()) != Status::OK ) return tmpStatus;
                std::optional<fs::Path> parent{tmpImpl.getParent()};
                if (parent.has_value() && !parent.value().exists() && !createParents) return Status::E_PARENT_NO_EXISTS;
                auto createParentDirs = [&]() -> void {
                    if (parent.has_value() && !parent.value().exists() && !std::filesystem::create_directories(parent.value().toStr()))
                        THROW(_private::_error::_CreateParentDirs, "Failed to create parent dirs: ", parent.value().toStr(), " for fullpath = ", this->toStr());
                };
                // TODO : recurive call to create on parent ?-
                // 2. Create target depending on the wanted type
                try {
                    switch (type) {
                        case Entry::Type::REGULAR_FILE: {
                            createParentDirs();
                            std::ofstream tmp(tmpImpl.toStr());
                            if ( !tmp.is_open() ) return Status::E_CREATE_FILE;
                            tmp.close();
                            break;
                        }
                        case Entry::Type::DIRECTORY: {
                            createParentDirs();
                            if ( !std::filesystem::create_directory(tmpImpl.toStr()) ) return Status::E_CREATE_FILE;
                            break;
                        }
                        case Entry::Type::SYM_LINK: {
                            logger::fatal << "I NEED TO IMPLEMENT THIS" << std::endl;
                            break;
                        }
                        default:
                            return Status::E_UNKNOWN_TYPE; // TODO : avoid creating the dirs before if we go here at the end
                    }
                    logger::debug << "Path: " << this->toStr() << " was created (" << tmpImpl.toStr() << ')' << std::endl;
                    return Status::OK;
                } catch (const error::Base &e) {
                    e.log();
                    if (dynamic_cast<const _private::_error::_CreateParentDirs *>(&e)) return Status::E_CREATE_PARENTS;
                } catch (const std::filesystem::filesystem_error &e) {
                    logger::error << "An error occured : " << e.what() << std::endl;
                    return Status::NOK;
                } catch(...) {
                    logger::error << "An unknown error occured. Aborting path creation. It may have worked" << std::endl;
                    return Status::NOK;
                }
                return Status::NOK;
            }

            _PathImpl operator=(const _PathImpl &other) {
                this->_data = other._data;
                this->_resolution = other._resolution;
                return *this;
            }

            Path operator=(const Path &other) const {
                return Path{other};
            }

            bool operator==(const Path &other) const {
                if (this->_resolution != other._pImpl->_resolution) return false;
                fs::Path::_PathImpl thisCpy = *this;
                fs::Path::_PathImpl otherCpy = *other._pImpl;

                if (thisCpy.clean() != Status::OK || otherCpy.clean() != Status::OK) return false;
                const std::size_t thisNEntry = thisCpy.getNEntry();
                if (thisNEntry != otherCpy.getNEntry()) return false;
                for (std::size_t i = 0; i < thisNEntry; i++)
                    if (thisCpy._data[i] != otherCpy._data[i]) return false;
                return true;
            }

            Path operator+(const Path &other) const {
                return Path{std::string(this->toStr() + "/" + other.toStr())};
            }

            static bool isPath(const std::string &str) {
                try {
                    std::filesystem::path instance{str};
                    return !instance.empty() && instance.has_root_name();
                } catch (...) {
                    return false;
                }
            }
    };


    Path::Path(void):
    _pImpl{std::make_unique<Path::_PathImpl>()}
    {}

    Path::Path(const std::string &path) :
    _pImpl{std::make_unique<Path::_PathImpl>(path)}
    {}

    Path::Path(const Path &path):
    _pImpl{std::make_unique<Path::_PathImpl>(*path._pImpl)}
    {}

    Path::~Path() = default;

    // Redeclaration because pImpl
    // Setters
    Status Path::insert(const Entry_t &entry) { return this->_pImpl->insert(entry); }
    Status Path::insert(const std::string &entry, const std::size_t &pos) { return this->_pImpl->insert(entry, pos); }
    Status Path::clean(void) { return this->_pImpl->clean(); }
    Status Path::toAbsolute(void) { return this->_pImpl->toAbsolute(); }
    Status Path::toRelative(void) { return this->_pImpl->toRelative(); }

    // Getters
    std::optional<Entry_t> Path::getEntry(void) const { return this->_pImpl->getEntry(); }
    std::optional<Entry_t> Path::getEntry(const std::size_t &pos) const { return this->_pImpl->getEntry(pos); }
    std::size_t Path::getNEntry(void) const { return this->_pImpl->getNEntry(); }
    std::optional<std::string> Path::getExtension(void) const { return this->_pImpl->getExtension(); }
    Entry::Type Path::getType(void) const { return this->_pImpl->getType(); }
    bool Path::isEmpty(void) const { return this->_pImpl->isEmpty(); }
    Path::Resolution Path::getResolution(void) const { return this->_pImpl->getResolution(); }
    std::optional<Path> Path::getParent(void) const { return this->_pImpl->getParent(); }
    bool Path::pointsTo(const fs::Path &path) const { return this->_pImpl->pointsTo(path); }
    
    
    Status Path::create(const Entry::Type &type, const bool &createParents) const { return this->_pImpl->create(type, createParents); }
    bool Path::exists(void) const { return this->_pImpl->exists(); }
    std::string Path::toStr(void) const { return this->_pImpl->toStr(); }
    Path Path::operator=(const Path &other) const { return this->_pImpl->operator=(other); }
    bool Path::operator==(const Path &other) const { return this->_pImpl->operator==(other); }
    Path Path::operator+(const Path &other) const { return this->_pImpl->operator+(other); }

    bool Path::isPath(const std::string &str) { return Path::_PathImpl::isPath(str); }

}
