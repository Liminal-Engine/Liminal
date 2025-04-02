/**
 * @file status.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef _LIMINAL_LIB_JSONIO_STATUS_HPP_
#define _LIMINAL_LIB_JSONIO_STATUS_HPP_

namespace jsonio {
    enum class Status {
        OK,
        E_NOK,
        E_PARSING,
        E_TYPE,
        E_KEY,
        E_INDEX,
        E_FILE,
        E_NOT_LOADED,
        E_JSON_PATH,
        E_VALUE_EXISTS,
        E_KEY_EXISTS,
        E_NO_ROOT_VALUE
    };
} // namespace jsonio


#endif // _LIMINAL_LIB_JSONIO_STATUS_HPP_