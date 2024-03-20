/**
 * @file path.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_FS_PATH_PATH_HPP_
#define LIMINAL_LIB_LIMINAL_FS_PATH_PATH_HPP_

#include <string>
#include <optional>

namespace liminal_fs {
    
    // Forward declarations :
    enum class Status;

    namespace path {

        using path_t = std::string;
        
        Status get_file_name(std::string &res, const path_t &path);
        Status get_file_extension(std::optional<std::string> &res, const path_t &path);
        Status get_absolute_path(std::string &res, const path_t &relative_path);
        Status path_exists(bool &res, const path_t &path);
        Status str_is_path(bool &res, const path_t &path);
        Status get_path_status(const path_t &path);

    } // namespace path
} // namespace liminal_fs


#endif // LIMINAL_LIB_LIMINAL_FS_PATH_PATH_HPP_