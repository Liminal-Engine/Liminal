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

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO_STATUS_HPP
#define LIMINAL_LIB_LIMINAL_JSON_IO_STATUS_HPP

namespace liminal_json_io {
    enum class Status {
        OK,
        NOK,
        PARSING_ERR
    };
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO_STATUS_HPP