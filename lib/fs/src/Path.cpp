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
#include "User.hpp"
#include "Permission.hpp"
#include "_private/_syntax.hpp"
#include "_private/_error/_Errors.hpp"

#include <sysop/sysop.hpp>
#include <parseop/parseop.hpp>
#include <logger/logger.hpp>
#include <time/Date.hpp>

#include <vector>
#include <filesystem>
#include <string.h>
#include <fstream>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>

#include <iostream>

namespace fs {
    class Path::_PathImpl {

        private:         
            std::vector<std::string> _data;
            Resolution _resolution;

            static std::vector<std::string> _loadData(const std::string &inputStr) { // TODO : hanlde what to do if given empty string and test it
                if (inputStr.empty()) return std::vector<std::string>{};
                if ( parseop::isOnlyChar(inputStr, '/') ) return std::vector<std::string>{"/"}; // TODO: test this
                
                std::vector<std::string> res{parseop::tokenize(inputStr, _private::_syntax::PATH_SEPARATOR)};
                // FIXME: always make sure it is not empty ?
                // FIXME: this is wrong, a dir can have spaces at the end
                res[res.size() - 1] = parseop::trimEnd(res.at(res.size() - 1), ' ');
                return res;
            };

            Status __createRegularFile(const bool &createParents, const Permission &perms) const noexcept {
                (void)createParents;
                (void)perms;
                return Status::OK; // TODO : implement this
            };

        public:
            _PathImpl(void) :
            _data{std::vector<std::string>{}},
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

            Status insert(const std::string &entry) {
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

            Status insert(const std::string &entryName, const std::size_t &index) {
                if (
                    entryName == "" ||
                    parseop::includes(entryName, std::vector<char>{_private::_syntax::FORBIDEN_CHARS.begin(), _private::_syntax::FORBIDEN_CHARS.end()})
                )  {
                        logger::error << "Wrong char in given entry. Entry is:  \'" << entryName << '\'' << std::endl;
                        return Status::E_PATH_INVALID_ENTRY_NAME;
                }
                if (index > this->_data.size()) return Status::E_PATH_INVALID_INDEX;
                const Resolution nextResolution = index == 0 && !entryName.empty() && entryName.at(0) == '/' ? Resolution::ABSOLUTE : this->_resolution;

                if ( !entryName.empty() ) this->_data.insert(this->_data.begin() + index, entryName);
                this->_resolution = nextResolution;
                return Status::OK;
            }

            Status insert(const Entry &entry) { return this->insert(entry.getName()); }

            Status insert(const Entry &entry, const std::size_t &pos) { return this->insert(entry.getName(), pos); }

            Status clean(void) {

                if ( !(this->_data.empty() || this->_data.size() == 1 || this->_data.at(0) == "/") ) {
                    this->_data = parseop::tokenize(
                        std::filesystem::path{this->asStr()}.lexically_normal(),
                        _private::_syntax::PATH_SEPARATOR                        
                    );
                    if (this->_data.empty()) this->_data = std::vector<std::string>{"/"};
                }
                return Status::OK;
            }

            Status toAbsolute(void) {
                if (this->_data.empty()) return Status::E_PATH_EMPTY;
                if ( this->_resolution == Resolution::RELATIVE ) {
                    *this = _PathImpl{ std::string{ sysop::getCWD().asStr() + "/" + this->asStr() } };
                    this->_resolution = Resolution::ABSOLUTE;
                }
                return Status::OK;
            }

            Status toRelative(void) {
                if (this->_data.empty()) return Status::E_PATH_EMPTY;
                if (this->_resolution == Resolution::ABSOLUTE) {
                    fs::Path cwd{sysop::getCWD()};
                    if (cwd == *this) this->_data = std::vector<std::string>{"."};
                    else {
                        std::vector<std::string> cwdEntries = cwd._pImpl->_data;
                        std::vector<std::string> thisEntries = this->_data;
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

            // Getters
            std::string asStr(void) const {
                std::string prefix("");

                if (this->_resolution == Resolution::ABSOLUTE && this->_data.at(0) != "/" && this->_data.size() >= 1)
                    prefix = "/";
                return prefix + parseop::join(this->_data, _private::_syntax::PATH_SEPARATOR);
            };

            Entry getEntry(void) const {
                return Entry(Path(this->asStr()));
            };

            Entry getEntry(const std::size_t &pos) const {
                if (pos >= this->_data.size()) return Entry();

                Path::_PathImpl thisCpy = *this;
                thisCpy._data.resize(pos + 1);
                return thisCpy.getEntry();
            };

            std::size_t getNEntry(void) const { return this->_data.size(); }

            Resolution getResolution(void) const { return this->_resolution; }

            bool isEmpty(void) const { return this->_data.empty(); }

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

            bool isRoot(void) const noexcept {
                Path::_PathImpl thisCpy = *this;
                thisCpy.clean();

                return thisCpy._data == std::vector<std::string>{ "/" };
            };


            // FIXME : instead of optional is path is empty, return cwd, wouldn't it be simpler ?
            std::optional<Path> getParent(void) const noexcept {
                if (this->_data.empty() || this->_data.size() <= 1) return std::nullopt;

                std::vector<std::string> cpy = this->_data;
                if (this->_resolution == Resolution::ABSOLUTE && !cpy.at(0).empty()) cpy[0] = "/" + cpy[0];
                cpy.pop_back();
                return Path{parseop::join(cpy, _private::_syntax::PATH_SEPARATOR)};
            }

            std::vector<Path> getChildren(void) const noexcept {
                DIR *c_dir;
                struct dirent *c_entry;
                std::vector<Path> res{};
                std::string thisStr(this->asStr());

                if ( (c_dir = opendir(thisStr.c_str())) == NULL) return res; // FIXME : log returned error with errno () (and strerr ?) error here
                while ( (c_entry = readdir(c_dir)) ) res.push_back(Path(thisStr + std::string(c_entry->d_name)));
                closedir(c_dir);
                return res;
            }

            bool operator==(const _PathImpl &other) {
                if (this->getResolution() != other.getResolution() || this->_data.size() != other._data.size()) return false;
                for (std::size_t i = 0; i < this->_data.size(); i++)
                    if (this->_data[i] != other._data[i]) return false;
                return true;
            }

            bool exists(void) const { return std::filesystem::exists(std::filesystem::path(this->asStr())); }

            Status create(
                const Entry::Type &type,
                const bool &createParents,
                const Permission &perms,
                const Path &symLinkTarget
            ) const noexcept {
                // 1. Setup: create vars
                if (this->exists()) return Status::E_ALREADY_EXISTS;
                fs::Path::_PathImpl tmpImpl = *this;
                Status tmpStatus = Status::NOK;
                if ( (tmpImpl.getResolution() != Resolution::ABSOLUTE) && (tmpStatus = tmpImpl.toAbsolute()) != Status::OK) return tmpStatus;
                if ( (tmpStatus = tmpImpl.clean()) != Status::OK ) return tmpStatus;
                std::optional<fs::Path> parent{tmpImpl.getParent()};
                if (parent.has_value() && !parent.value().exists() && !createParents) return Status::E_PARENT_NO_EXISTS;
                auto createParentDirs = [&]() -> void {
                    if (parent.has_value() && !parent.value().exists() && !std::filesystem::create_directories(parent.value().asStr()))
                        THROW(_private::_error::_CreateParentDirs, "Failed to create parent dirs: ", parent.value().asStr(), " for fullpath = ", this->asStr());
                };
                // TODO : recurive call to create on parent ?-
                // 2. Create target depending on the wanted type
                try {
                    switch (type) {
                        case Entry::Type::REGULAR_FILE: return this->__createRegularFile(createParents, perms);
                        // {
                        //     createParentDirs();
                        //     std::ofstream tmp(tmpImpl.asStr());
                        //     if ( !tmp.is_open() ) return Status::E_CREATE_FILE;
                        //     tmp.close();
                        //     break;
                        // }
                        case Entry::Type::DIRECTORY: {
                            createParentDirs();
                            if ( !std::filesystem::create_directory(tmpImpl.asStr()) ) return Status::E_CREATE_FILE;
                            break;
                        }
                        case Entry::Type::SYM_LINK: {
                            (void)symLinkTarget;
                            logger::fatal << "I NEED TO IMPLEMENT THIS" << std::endl;
                            break;
                        }
                        default:
                            return Status::E_UNKNOWN_TYPE; // TODO : avoid creating the dirs before if we go here at the end
                    }
                    logger::debug << "Path: " << this->asStr() << " was created (" << tmpImpl.asStr() << ')' << std::endl;
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
                // FIXME : add "/" only if the first one does not end with "/" ?
                return Path{std::string(this->asStr() + "/" + other.asStr())};
            }

            static bool isPath(const std::string &str) noexcept {
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
    Status Path::insert(const std::string &entryName) { return this->_pImpl->insert(entryName); }
    Status Path::insert(const std::string &entry, const std::size_t &pos) { return this->_pImpl->insert(entry, pos); }
    Status Path::insert(const Entry &entry) { return this->_pImpl->insert(entry); }
    Status Path::insert(const Entry &entry, const std::size_t &pos) { return this->_pImpl->insert(entry, pos); }
    Status Path::clean(void) { return this->_pImpl->clean(); }
    Status Path::toAbsolute(void) { return this->_pImpl->toAbsolute(); }
    Status Path::toRelative(void) { return this->_pImpl->toRelative(); }

    // Getters
    std::string Path::asStr(void) const { return this->_pImpl->asStr(); }
    Entry Path::getEntry(void) const { return this->_pImpl->getEntry(); }
    Entry Path::getEntry(const std::size_t &pos) const { return this->_pImpl->getEntry(pos); }
    std::size_t Path::getNEntry(void) const { return this->_pImpl->getNEntry(); }
    Path::Resolution Path::getResolution(void) const { return this->_pImpl->getResolution(); }
    bool Path::isEmpty(void) const { return this->_pImpl->isEmpty(); }
    bool Path::pointsTo(const fs::Path &path) const { return this->_pImpl->pointsTo(path); }
    bool Path::isRoot(void) const noexcept { return this->_pImpl->isRoot(); }
    std::optional<Path> Path::getParent(void) const noexcept { return this->_pImpl->getParent(); }
    std::vector<Path> Path::getChildren(void) const noexcept { return this->_pImpl->getChildren(); }
    
    Status Path::create(
        const Entry::Type &type,
        const bool &createParents,
        const Permission &perms,
        const Path &symLinkTarget
    ) const noexcept { return this->_pImpl->create(type, createParents, perms, symLinkTarget); }
    bool Path::exists(void) const { return this->_pImpl->exists(); }
    Path Path::operator=(const Path &other) const { return this->_pImpl->operator=(other); }
    bool Path::operator==(const Path &other) const { return this->_pImpl->operator==(other); }
    Path Path::operator+(const Path &other) const { return this->_pImpl->operator+(other); }

    bool Path::isPath(const std::string &str) noexcept { return Path::_PathImpl::isPath(str); }

}
