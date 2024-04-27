/**
 * @file Entry.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief An entry represents any kind of file (or directory)
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_LIB_FS_ENTRY_HPP_
#define LIMINAL_LIB_FS_ENTRY_HPP_

#include "User.hpp"
#include "Permission.hpp"

// #include <time/Date.hpp>

#include <string>
#include <cstddef>
#include <optional>

namespace fs {

    class Entry {
        public:


            enum class Type {
                REGULAR_FILE,
                DIRECTORY,
                SYM_LINK,
                BLOCK_DEVICE,
                CHARACTER_DEVICE,
                FIFO,
                SOCKET,
                UNKNOWN
            };

            class Size {
                // To, Go, etc ??? o plutôt struct ?
            };

        private:

            Type _type;
            std::string _name;
            std::size_t _size; // in bytes
            bool _isHidden;
            // time::Date _creationDate;
            // time::Date _lastModifDate;
            // time::Date _lastAccessDate;
            User _owner;
            Permission _userPermission;
            Permission _groupPermission;
            Permission _worldPermission;
            std::optional<std::string> _extension;
    };
    
} // namespace fs


#endif // LIMINAL_LIB_FS_ENTRY_HPP_