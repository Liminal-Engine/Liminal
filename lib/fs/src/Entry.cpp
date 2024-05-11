/**
 * @file Entry.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-04
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "Entry.hpp"
#include "Size.hpp"
#include "User.hpp"
#include "Permission.hpp"
#include "Path.hpp"
#include "_private/_syntax.hpp"

#include <filesystem>
#include <parseop/parseop.hpp>

#include <sys/stat.h>


#include <iostream>

namespace fs {
    class Entry::_EntryImpl {

        private:
            std::string _name;
            Type _type;
            Size _size; // in bytes
            bool _isHidden;
            time_::Date _lastModif;
            time_::Date _lastAccess;
            time_::Date _lastStatusChange;
            User _owner;
            Permission _perms;
            std::optional<std::string> _extension;

            static Entry::Type __loadType(const std::string &path) {
                try {
                    std::filesystem::file_type stdFsType = std::filesystem::symlink_status(path).type();

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

            static bool __loadIsHidden(const std::string &name) { return parseop::startsWith(name, "."); }

            static std::optional<std::string> __loadExtension(const std::string &name) {
                std::vector<std::string> vec = parseop::tokenize(name, ".");
                if (vec.empty()) return std::optional<std::string>(std::nullopt);
                std::string res = parseop::tokenize(name, ".").back();

                return (parseop::endsWith(name, res) || res.empty()) ? std::optional<std::string>(std::nullopt) : res;
            }

            static _EntryImpl __create(const Path &path) noexcept {
                Path _pathCpy(path);
                if (_pathCpy.isEmpty()) return _EntryImpl();
                _pathCpy.clean();
                std::string strPath = _pathCpy.toStr();
                struct stat pathStat;
                std::vector<std::string> pathVec(
                    _pathCpy.isRoot() ?
                    std::vector<std::string>{ "/" } :
                    parseop::tokenize(strPath, _private::_syntax::PATH_SEPARATOR)
                );
                if (pathVec.empty()) return _EntryImpl();
                std::string name = pathVec.back(); 
                Type type = __loadType(strPath);

                return (
                    !path.exists() || stat(strPath.c_str(), &pathStat) != 0 ?
                    _EntryImpl(name) :
                    _EntryImpl(name, type, pathStat)
                );
            }

            _EntryImpl(const std::string &name, const Type &type, const struct stat &c_stat) noexcept:
            _name(name),
            _type(type),
            _size(static_cast<unsigned int>(c_stat.st_size)),
            _isHidden(__loadIsHidden(name)),
            _lastModif(c_stat.st_mtim.tv_sec), // FIXME : check if I can use tv_nsec here. Edit : nano second is available since linux 2.6
            _lastAccess(c_stat.st_atim.tv_sec),
            _lastStatusChange(c_stat.st_ctim.tv_sec),
            _owner(c_stat.st_uid),
            _perms(c_stat.st_mode),
            _extension(__loadExtension(name))
            {}

        public:

            _EntryImpl(const Path &path) noexcept :
            _EntryImpl(__create(path))
            {}
            
            _EntryImpl(const Entry::_EntryImpl &other) noexcept:
            _name(other._name),
            _type(other._type),
            _size(other._size),
            _isHidden(other._isHidden),
            _lastModif(other._lastModif),
            _lastAccess(other._lastAccess),
            _lastStatusChange(other._lastStatusChange),
            _owner(other._owner),
            _perms(other._perms),
            _extension(other._extension)
            {}

            _EntryImpl(const std::string &name = "") noexcept: // equivalent to void also
            _name(name),
            _type(Entry::Type::UNKNOWN),
            _size(),
            _isHidden(__loadIsHidden(name)),
            _lastModif(),
            _lastAccess(),
            _lastStatusChange(),
            _owner(),
            _perms(),
            _extension(__loadExtension(name))
            {}

            _EntryImpl(
                const std::string &name,
                const Entry::Type &type,
                const Size &size,
                const bool &isHidden,
                const time_::Date &lastModif,
                const time_::Date &lastStatusChange,
                const time_::Date &lastAccess,
                const User &owner,
                const Permission &perms,
                const std::optional<std::string> &extension
            ):
            _name(name),
            _type{type},
            _size(size),
            _isHidden(isHidden),
            _lastModif(lastModif),
            _lastAccess(lastAccess),
            _lastStatusChange(lastStatusChange),
            _owner(owner),
            _perms(perms),
            _extension(extension)
            {}


            bool operator==(const _EntryImpl &other) const noexcept {
                return (
                    this->_name == other._name &&
                    this->_type == other._type &&
                    this->_size == other._size &&
                    this->_isHidden == other._isHidden &&
                    this->_lastModif == other._lastModif &&
                    this->_lastAccess == other._lastAccess &&
                    this->_lastStatusChange == other._lastStatusChange &&
                    this->_owner == other._owner &&
                    this->_perms == other._perms &&
                    this->_extension == other._extension
                );
            };

            std::string getName(void) const noexcept { return this->_name; }
            Entry::Type getType(void) const noexcept { return this->_type; }

            ~_EntryImpl() = default;

    };

    Entry::Entry(const Path &path) noexcept: _impl(std::make_unique<Entry::_EntryImpl>(path)) {}
    Entry::Entry(const Entry &other) noexcept: _impl(std::make_unique<Entry::_EntryImpl>(*other._impl)) {}
    Entry::Entry(Entry &&other) noexcept: _impl(std::move(other._impl)) {}
    Entry::Entry(void) noexcept: _impl(std::make_unique<Entry::_EntryImpl>()) {} //will call name="" conststructor
    Entry::~Entry() = default;

    bool Entry::operator==(const Entry &other) const noexcept { return this->_impl->operator==(*other._impl); }

    Entry::Type Entry::getType(void) const noexcept { return this->_impl->getType(); }
    std::string Entry::getName(void) const noexcept { return this->_impl->getName(); }
} // namespace fs
