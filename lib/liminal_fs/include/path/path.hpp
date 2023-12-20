#ifndef LIMINAL_LIB_LIMINAL_FS_PATH_PATH_HPP_
#define LIMINAL_LIB_LIMINAL_FS_PATH_PATH_HPP_

#include "Status.hpp"
#include "FileType.hpp"

#include <string>

namespace liminal_fs {
    namespace path {

        typedef std::string path_t;
        
        Status get_file_name(std::string &res, const path_t &path);
        Status get_file_extension(std::string &res, const path_t &path);
        Status get_absolute_path(std::string &res, const path_t &relative_path);
        Status path_exists(bool &res, const path_t &path);
        Status str_is_path(bool &res, const path_t &path);
        Status get_path_status(const path_t &path);

    } // namespace path
} // namespace liminal_fs


#endif // LIMINAL_LIB_LIMINAL_FS_PATH_PATH_HPP_