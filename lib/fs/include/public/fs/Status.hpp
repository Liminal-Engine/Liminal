#ifndef LIMINAL_LIB_FS_STATUS_HPP_
#define LIMINAL_LIB_FS_STATUS_HPP_

namespace fs {
    enum class Status {
        OK,
        NOK,
        E_PATH_IS_DIR,
        E_FILE_OPEN,
        E_CANNOT_CLOSE_FILE,
        E_CLOSE_FILE_NOT_OPEN,
        E_STR_INVALID_PATH,
        E_PATH_NO_TARGET, // Path point to nothing real
        E_READ_FILE_NOT_OPENED,
        E_WRITE_FILE_CLOSED,
        E_PATH_INVALID_INDEX,
        E_PATH_INVALID_ENTRY_NAME,
        E_CREATE_FILE,
        E_TO_ABSOLUTE,
        E_PATH_EMPTY,
        E_TO_RELATIVE,
        E_ALREADY_EXISTS,
        E_UNKNOWN_TYPE,
        E_PARENT_NO_EXISTS,
        E_CREATE_PARENTS,
        E_CREATE_FORBIDDEN_TYPE,
        E_SET_PERMS,
        E_CREATE_DIR
   };

   // TODO: find a way to convert in str (I think there is a native method instead of creating a function)
}

#endif // LIMINAL_LIB_FS_STATUS_HPP_