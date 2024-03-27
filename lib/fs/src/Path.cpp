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

#include <vector>
#include <filesystem>

namespace fs {
    
    class Path::_PathImpl {

        private:            
            std::vector<Entry_t> _data;

            static std::vector<Entry_t> _loadData(const std::string &inputStr) {
                return parser::string::tokenize(inputStr, _private::_syntax::PATH_SEPARATOR);
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
                this->insert(entry, this->_data.size() - 1);
                return Status::OK;
            }

            Status insert(const Entry_t &entry, const std::size_t &pos) {
                if (pos > this->_data.size()) return Status::INVALID_PATH_POS;
                this->_data.insert(this->_data.begin() + pos, entry);
                return Status::OK;
            }

            // Getters
            std::optional<Entry_t> getEntry(void) const {
                return this->_data.empty() ? std::nullopt : std::optional<Entry_t>(this->_data.back());
            };

            std::optional<Entry_t> getEntry(const std::size_t &pos) const {
                return this->_data.empty() || pos > this->_data.size() ? std::nullopt : std::optional<Entry_t>(this->_data.at(pos));
            };

            std::optional<std::string> getExtension(void) const {
                return std::filesystem::path(this->toStr()).extension().string();
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
    // Getters
    std::optional<Entry_t> Path::getEntry(void) const { return this->_pImpl->getEntry(); }
    std::optional<Entry_t> Path::getEntry(const std::size_t &pos) const { return this->_pImpl->getEntry(pos); }
    std::optional<std::string> Path::getExtension(void) const { return this->_pImpl->getExtension(); }
    bool Path::exists(void) const { return this->_pImpl->exists(); }
    Path::Type Path::getType(void) const { return this->_pImpl->getType(); }
    bool Path::empty(void) const { return this->_pImpl->empty(); }

    Path Path::getAbsolute(void) const { return this->_pImpl->getAbsolute(); }
    std::string Path::toStr(void) const { return this->_pImpl->toStr(); }
    Path Path::operator=(const Path &other) const { return this->_pImpl->operator=(other); }

    bool Path::isPath(const std::string &str) { return Path::_PathImpl::isPath(str); }

}