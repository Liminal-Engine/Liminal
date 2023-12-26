/**
 * @file types.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-25
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIN_LIMINAL_JSON_IO_TYPES_HPP_
#define LIMINAL_LIN_LIMINAL_JSON_IO_TYPES_HPP_

#include <string>

namespace liminal_json_io {
    namespace types {

        typedef std::string type_t;

        const type_t STRING     = "string";
        const type_t INTEGER    = "intmax_t";
        const type_t FLOAT      = "long double";
        const type_t BOOL       = "bool";
        const type_t NULL_      = "null";
        const type_t TOKEN      = "token";

    } // namespace types
} // liminal_json_io


#endif // LIMINAL_LIN_LIMINAL_JSON_IO_TYPES_HPP_