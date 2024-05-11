/**
 * @file User.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright Copyright (c) 2024
 * 
*/


#ifndef LIMINAL_LIB_FS_INCLUDE_PUBLIC_FS_USER_HPP_
#define LIMINAL_LIB_FS_INCLUDE_PUBLIC_FS_USER_HPP_

#include <string>
#include <memory>

namespace fs {

    class User { // FIXME : should this class be in sysop ?
        public:
            User(void);
            User(const std::string &name);
            User(const unsigned int &id);
            User(const User &other);
            ~User();

            bool operator==(const User &other) const noexcept;

            std::string getName(void) const noexcept;
            unsigned int getId(void) const noexcept;
            unsigned int getGroupId(void) const noexcept;
            bool doesExist(void) const noexcept;

        private:
            class _Pimpl;
            std::unique_ptr<_Pimpl> _impl;
    };
    
} // namespace fs


#endif // LIMINAL_LIB_FS_INCLUDE_PUBLIC_FS_USER_HPP_