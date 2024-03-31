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

#include "parser/string.hpp"
#include "logger/logger.hpp"

#include <vector>
#include <filesystem>

namespace fs {
    
    class Path::_PathImpl {

        private:            
            std::vector<Entry_t> _data;

            static std::vector<Entry_t> _loadData(const std::string &inputStr) {
                return inputStr.empty() ? std::vector<Entry_t>{} : parser::string::tokenize(inputStr, _private::_syntax::PATH_SEPARATOR);
            };

        public:
            _PathImpl(void) :
            _data{std::vector<Entry_t>{}}
            {}

            _PathImpl(const std::string &path):
            _data{_PathImpl::_loadData(path)}
            {}

            _PathImpl(const _PathImpl &pathImpl):
            _data{pathImpl._data}
            {}

            // Setters

            Status insert(const Entry_t &entry) {
                return this->insert(entry, this->_data.size());
            }

            Status insert(const Entry_t &entry, const std::size_t &index) {
                if (entry == "") return Status::PATH_INVALID_ENTRY_NAME;
                for (const char &c : _private::_syntax::FORBIDEN_CHARS) {
                    // TODO : tokenize FORBIDEN_CHARS instead, avoiding loop
                    if (parser::string::contains(entry, c)) {
                        logger::error << "Wrong char in entry : \'" << c << '\'' << std::endl;
                        return Status::PATH_INVALID_ENTRY_NAME;
                    }
                }
                if (index > this->_data.size()) return Status::PATH_INVALID_INDEX;
                this->_data.insert(this->_data.begin() + index, entry);
                return Status::OK;
            }

            Status clean(void) {
                this->_data = parser::string::tokenize(
                    std::filesystem::path{this->toStr()}.lexically_normal(),
                    _private::_syntax::PATH_SEPARATOR
                );
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

            std::optional<std::string> getExtension(void) const {
                if (this->_data.empty()) return std::optional<std::string>();
                fs::Entry_t lastEntry{this->getEntry().value()};
                std::size_t dotPos{lastEntry.find(".")};
                
                if (dotPos == std::string::npos || dotPos + 1 >= lastEntry.size()) 
                    return std::optional<std::string>(std::nullopt);
                return lastEntry.substr(dotPos + 1, lastEntry.size());
            };

            Type getType(void) const {
                std::filesystem::file_type stdFsType = std::filesystem::status(this->toStr()).type();

                switch (stdFsType) {
                    case std::filesystem::file_type::regular:
                        return Type::REGULAR_FILE;
                    case std::filesystem::file_type::directory:
                        return Type::DIRECTORY;
                    case std::filesystem::file_type::symlink:
                        return Type::SYM_LINK;
                    case std::filesystem::file_type::block:
                        return Type::BLOCK_DEVICE;
                    case std::filesystem::file_type::fifo:
                        return Type::FIFO;
                    case std::filesystem::file_type::socket:
                        return Type::SOCKET;
                    default:
                        return Type::UNKNOWN;
                }
            }

            bool empty(void) const { return this->_data.empty(); }

            bool exists(void) const { return std::filesystem::exists(std::filesystem::path(this->toStr())); }

            Path getAbsolute(void) const {
                return Path{std::filesystem::absolute(std::filesystem::path(this->toStr())).string()};
            }

            std::string toStr(void) const {
                return parser::string::join(this->_data, _private::_syntax::PATH_SEPARATOR);
            };

            Path operator=(const Path &other) const {
                return Path{other};
            }

            bool operator==(const Path &other) const {
                const std::size_t thisNEntry = this->getNEntry();

                if (thisNEntry != other.getNEntry()) return false;
                for (std::size_t i = 0; i < thisNEntry; i++)
                    if (this->_data[i] != other.getEntry(i)) return false;
                return true;
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
    // Getters
    std::optional<Entry_t> Path::getEntry(void) const { return this->_pImpl->getEntry(); }
    std::optional<Entry_t> Path::getEntry(const std::size_t &pos) const { return this->_pImpl->getEntry(pos); }
    std::size_t Path::getNEntry(void) const { return this->_pImpl->getNEntry(); }
    std::optional<std::string> Path::getExtension(void) const { return this->_pImpl->getExtension(); }
    bool Path::exists(void) const { return this->_pImpl->exists(); }
    Path::Type Path::getType(void) const { return this->_pImpl->getType(); }
    bool Path::empty(void) const { return this->_pImpl->empty(); }

    Path Path::getAbsolute(void) const { return this->_pImpl->getAbsolute(); }
    std::string Path::toStr(void) const { return this->_pImpl->toStr(); }
    Path Path::operator=(const Path &other) const { return this->_pImpl->operator=(other); }
    bool Path::operator==(const Path &other) const { return this->_pImpl->operator==(other); }

    bool Path::isPath(const std::string &str) { return Path::_PathImpl::isPath(str); }

}