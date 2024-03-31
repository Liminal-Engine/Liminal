#ifndef LIMINAL_LIB_FS_STATUS_HPP_
#define LIMINAL_LIB_FS_STATUS_HPP_

namespace fs {
    enum class Status {
        OK,
        NOK,
        OPEN_FILE_ERR,
        CLOSE_FILE_ERR,
        STR_IS_NOT_A_PATH,
        PATH_NO_TARGET, // Path point to nothing real
        CANNOT_READ_FILE_IS_CLOSED,
        CANNOT_WRITE_FILE_IS_CLOSED,
        PATH_INVALID_INDEX,
        PATH_INVALID_ENTRY_NAME
    };
}

#endif // LIMINAL_LIB_FS_STATUS_HPP_