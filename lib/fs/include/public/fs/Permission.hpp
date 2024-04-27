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

namespace fs {

    class Permission {

        enum class Type {
            NONE,
            READ,
            WRITE,
            EXEC
        };

        public:
            bool canRead(void) const;
            bool canWrite(void) const;
            bool canExec(void) const;

        private:
            bool _canRead;
            bool _canWrite;
            bool _canExec;

    };
    
} // namespace fs


#endif // LIMINAL_FS_INCLUDE_PUBLIC_FS_PERMISION_HPP_