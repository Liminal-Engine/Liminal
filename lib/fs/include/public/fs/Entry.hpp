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

#include <string>
#include <cstddef>

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

        private:

            std::string _name;
            std::size_t _size; // in bytes
            bool _isHidden;
            int _creationDate; // TODO : before, I need to wonder how to handle dates in a general matter
            int _lastModifDate;
            //UNKNOWN_TYPE//; _owner:

            //UNKNOWN_TYPE// userPermissions
            //UNKNOWN_TYPE// groupPermissions
            //UNKNOWN_TYPE// worldPermissions


    };
    
} // namespace fs


#endif // LIMINAL_LIB_FS_ENTRY_HPP_