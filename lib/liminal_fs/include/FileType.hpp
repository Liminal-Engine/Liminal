#ifndef LIMINAL_LIB_LIMINAL_FS_FILETYPE_HPP
#define LIMINAL_LIB_LIMINAL_FS_FILETYPE_HPP

#include "Status.hpp"
#include "path/path.hpp"

#include <string>

namespace liminal_fs {

    // Forward declaration to avoid conflict with path/path.hpp
    namespace path {
        typedef std::string path_t;
    }

    enum FileType {
        REGULAR_FILE,
        DIRECTORY,
        SYM_LINK,
        HARD_LINK
    };
    
    Status get_file_type(FileType &res, const path::path_t &path);

} // namespace liminal_fs 


#endif // LIMINAL_LIB_LIMINAL_FS_FILETYPE_HPP