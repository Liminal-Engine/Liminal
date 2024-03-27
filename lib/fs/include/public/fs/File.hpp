/**
 * @file File.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef LIMINAL_LIB_FS_FILE_HPP_
#define LIMINAL_LIB_FS_FILE_HPP_

#include "InFile.hpp"
#include "OutFile.hpp"

#include <optional>
#include <string>
#include <sstream>

namespace fs {

    // TODO  : test this class
    class File : public OutFile, public InFile;

} // namespace fs

#endif // LIMINAL_LIB_FS_FILE_HPP_