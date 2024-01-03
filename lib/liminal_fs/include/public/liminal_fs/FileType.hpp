#ifndef LIMINAL_LIB_LIMINAL_FS_FILETYPE_HPP
#define LIMINAL_LIB_LIMINAL_FS_FILETYPE_HPP

#include <string>

namespace liminal_fs {

    // Forward declarations :
    enum class Status;
    namespace path {
        using path_t = std::string;
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