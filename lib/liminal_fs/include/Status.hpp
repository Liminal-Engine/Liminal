#ifndef LIMINAL_LIB_LIMINAL_FS_STATUS_HPP
#define LIMINAL_LIB_LIMINAL_FS_STATUS_HPP

namespace liminal_fs {
    enum Status {
        OK  =   0,
        NOK,
        OPEN_FILE_ERR,
        STR_IS_NOT_A_PATH,
        PATH_NO_TARGET // Path point to nothing        
    };
}

#endif // LIMINAL_LIB_LIMINAL_FS_STATUS_HPP