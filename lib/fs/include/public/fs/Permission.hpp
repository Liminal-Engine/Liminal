/**
 * @file Permissions.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_FS_INCLUDE_PUBLIC_FS_PERMISION_HPP_
#define LIMINAL_FS_INCLUDE_PUBLIC_FS_PERMISION_HPP_

#include <sys/stat.h>
#include <memory>

namespace fs {

    class Permission {


        public:
            enum class Type {
                NONE = 0,
                READ = 1 << 0,
                WRITE = 1 << 1,
                EXEC = 1 << 2
            };

            Permission(const Type &ownerTypes, const Type &groupTypes, const Type &otherTypes) noexcept;
            Permission(const Permission &other) noexcept;
            Permission(const mode_t &c_mode) noexcept;
            Permission(const int &unixFormat) noexcept;
            Permission(void) noexcept;
            ~Permission() noexcept;

            bool canOwnerRead(void) const noexcept;
            bool canOwnerWrite(void) const noexcept;
            bool canOwnerExec(void) const noexcept;
            bool canGroupRead(void) const noexcept;
            bool canGroupWrite(void) const noexcept;
            bool canGroupExec(void) const noexcept;
            bool canOtherRead(void) const noexcept;
            bool canOtherWrite(void) const noexcept;
            bool canOtherExec(void) const noexcept;
            int getUnixFormat(void) const noexcept;

            Permission operator=(const Permission &other) noexcept;
            bool operator==(const Permission &other) const noexcept;
            Permission operator+(const Permission &other) const noexcept;
            Permission operator-(const Permission &other) const noexcept;
        private:
            class _PImpl;
            std::unique_ptr<_PImpl> _impl;

    };

} // namespace fs

fs::Permission::Type operator|(const fs::Permission::Type &a, const fs::Permission::Type &b);
fs::Permission::Type operator&(const fs::Permission::Type &a, const fs::Permission::Type &b);


#endif // LIMINAL_FS_INCLUDE_PUBLIC_FS_PERMISION_HPP_