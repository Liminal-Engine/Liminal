/**
 * @file InFile.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-20
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_FS_LIB_IFILE_HPP
#define LIMINAL_FS_LIB_IFILE_HPP

#include "_private/_File.hpp"

#include <fstream>

namespace liminal_fs {

    class InFile : public _private::_File<std::ifstream> {

        public:
            InFile(const path::path_t &path);
            Status read(void);
            
            // Getters :
            std::string get_content(void) const;

        private:
            std::string _buffer;


    };

}

#endif // LIMINAL_FS_LIB_IFILE_HPP