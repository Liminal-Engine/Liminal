#ifndef LIMINAL_LIB_FS_FILETYPE_HPP_
#define LIMINAL_LIB_FS_FILETYPE_HPP_

#include <string>

namespace fs {

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

} // namespace fs 


#endif // LIMINAL_LIB_FS_FILETYPE_HPP_