/**
 * @file Permission.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "Permission.hpp"

namespace fs {

    class Permission::_PImpl {
        private:
            const bool _ownerCanRead;
            const bool _ownerCanWrite;
            const bool _ownerCanExec;
            const bool _groupCanRead;
            const bool _groupCanWrite;
            const bool _groupCanExec;
            const bool _otherCanRead;
            const bool _otherCanWrite;
            const bool _otherCanExec;

        public:
            _PImpl(const Type &ownerTypes, const Type &groupTypes, const Type &otherTypes) noexcept :
            _ownerCanRead(static_cast<bool>(ownerTypes & Type::READ)),
            _ownerCanWrite(static_cast<bool>(ownerTypes & Type::WRITE)),
            _ownerCanExec(static_cast<bool>(ownerTypes & Type::EXEC)),
            _groupCanRead(static_cast<bool>(groupTypes & Type::READ)),
            _groupCanWrite(static_cast<bool>(groupTypes & Type::WRITE)),
            _groupCanExec(static_cast<bool>(groupTypes & Type::EXEC)),
            _otherCanRead(static_cast<bool>(otherTypes & Type::READ)),
            _otherCanWrite(static_cast<bool>(otherTypes & Type::WRITE)),
            _otherCanExec(static_cast<bool>(otherTypes & Type::EXEC))
            {};

            _PImpl(const Permission::_PImpl &other) noexcept :
            _ownerCanRead(other._ownerCanRead),
            _ownerCanWrite(other._ownerCanWrite),
            _ownerCanExec(other._ownerCanExec),
            _groupCanRead(other._groupCanRead),
            _groupCanWrite(other._groupCanWrite),
            _groupCanExec(other._groupCanExec),
            _otherCanRead(other._otherCanRead),
            _otherCanWrite(other._otherCanWrite),
            _otherCanExec(other._otherCanExec)
            {}

            _PImpl(const mode_t &c_mode) noexcept:
            _ownerCanRead(static_cast<bool>(c_mode & S_IRUSR)),
            _ownerCanWrite(static_cast<bool>(c_mode & S_IWUSR)),
            _ownerCanExec(static_cast<bool>(c_mode & S_IXUSR)),
            _groupCanRead(static_cast<bool>(c_mode & S_IRGRP)),
            _groupCanWrite(static_cast<bool>(c_mode & S_IWGRP)),
            _groupCanExec(static_cast<bool>(c_mode & S_IXGRP)),
            _otherCanRead(static_cast<bool>(c_mode & S_IROTH)),
            _otherCanWrite(static_cast<bool>(c_mode & S_IWOTH)),
            _otherCanExec(static_cast<bool>(c_mode & S_IXOTH))
            {}

            _PImpl(void) noexcept :
            _ownerCanRead(false),
            _ownerCanWrite(false),
            _ownerCanExec(false),
            _groupCanRead(false),
            _groupCanWrite(false),
            _groupCanExec(false),
            _otherCanRead(false),
            _otherCanWrite(false),
            _otherCanExec(false)
            {}

            bool operator==(const _PImpl &other) const noexcept {
                return (
                    this->_ownerCanRead == other._ownerCanRead &&
                    this->_ownerCanWrite == other._ownerCanWrite &&
                    this->_ownerCanExec == other._ownerCanExec &&
                    this->_groupCanRead == other._groupCanRead &&
                    this->_groupCanWrite == other._groupCanWrite &&
                    this->_groupCanExec == other._groupCanExec &&
                    this->_otherCanRead == other._otherCanRead &&
                    this->_otherCanWrite == other._otherCanWrite &&
                    this->_otherCanExec == other._otherCanExec
                );
            }

            bool canOwnerRead(void) const noexcept { return this->_ownerCanRead; }
            bool canOwnerWrite(void) const noexcept { return this->_ownerCanWrite; }
            bool canOwnerExec(void) const noexcept { return this->_ownerCanExec; }
            bool canGroupRead(void) const noexcept { return this->_groupCanRead; }
            bool canGroupWrite(void) const noexcept { return this->_groupCanWrite; }
            bool canGroupExec(void) const noexcept { return this->_groupCanExec; }
            bool canOtherRead(void) const noexcept { return this->_otherCanRead; }
            bool canOtherWrite(void) const noexcept { return this->_otherCanWrite; }
            bool canOtherExec(void) const noexcept { return this->_otherCanExec; }
    };

    Permission::Permission(const Type &ownerTypes, const Type &groupTypes, const Type &otherTypes) noexcept :
    _impl{std::make_unique<Permission::_PImpl>(ownerTypes, groupTypes, otherTypes)}
    {}

    Permission::Permission(const Permission &other) noexcept :
    _impl(std::make_unique<Permission::_PImpl>(*other._impl))
    {}

    Permission::Permission(const mode_t &c_mode) noexcept :
    _impl(std::make_unique<Permission::_PImpl>(c_mode))
    {}

    Permission::Permission(void) noexcept :
    _impl(std::make_unique<Permission::_PImpl>())
    {}

    Permission::~Permission() noexcept = default;

    bool Permission::operator==(const Permission &other) const noexcept { return this->_impl->operator==(*other._impl); }
 
    bool Permission::canOwnerRead(void) const noexcept { return this->_impl->canOwnerRead(); }
    bool Permission::canOwnerWrite(void) const noexcept { return this->_impl->canOwnerWrite(); }
    bool Permission::canOwnerExec(void) const noexcept { return this->_impl->canOwnerExec(); }
    bool Permission::canGroupRead(void) const noexcept { return this->_impl->canGroupRead(); }
    bool Permission::canGroupWrite(void) const noexcept { return this->_impl->canGroupWrite(); }
    bool Permission::canGroupExec(void) const noexcept { return this->_impl->canGroupExec(); }
    bool Permission::canOtherRead(void) const noexcept { return this->_impl->canOtherRead(); }
    bool Permission::canOtherWrite(void) const noexcept { return this->_impl->canOtherWrite(); }
    bool Permission::canOtherExec(void) const noexcept { return this->_impl->canOtherExec(); }
    
} // namespace fs

fs::Permission::Type operator|(const fs::Permission::Type &a, const fs::Permission::Type &b) {
    return static_cast<fs::Permission::Type>(static_cast<int>(a) | static_cast<int>(b));
}

fs::Permission::Type operator&(const fs::Permission::Type &a, const fs::Permission::Type &b) {
    return static_cast<fs::Permission::Type>(static_cast<int>(a) & static_cast<int>(b));
}
