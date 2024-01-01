/**
 * @file OutFile.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_FS_OUTFILE_HPP_
#define LIMINAL_LIB_LIMINAL_FS_OUTFILE_HPP_

#include "_private/_File.hpp"

#include <fstream>

namespace liminal_fs {

    class OutFile : public _private::_File<std::ofstream> {

    }

} // namespace liminal_fs


#endif // LIMINAL_LIB_LIMINAL_FS_OUTFILE_HPP_