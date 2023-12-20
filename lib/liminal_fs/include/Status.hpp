#ifndef LIMINAL_LIB_LIMINAL_FS_STATUS_HPP
#define LIMINAL_LIB_LIMINAL_FS_STATUS_HPP

namespace liminal_fs {
    enum class Status {
        OK,
        NOK,
        OPEN_FILE_ERR,
        CLOSE_FILE_ERR,
        STR_IS_NOT_A_PATH,
        PATH_NO_TARGET, // Path point to nothing        
        CANNOT_READ_FILE_IS_CLOSED
    };
}

#endif // LIMINAL_LIB_LIMINAL_FS_STATUS_HPP