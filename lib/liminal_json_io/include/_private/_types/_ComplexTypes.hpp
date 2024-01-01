/**
 * @file _ComplexTypes.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__TYPES_COMPLEX_TYPES_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__TYPES_COMPLEX_TYPES_HPP_

#include "_private/_complex_value/_Object.hpp"
#include "_private/_complex_value/_Array.hpp"

#include <variant>

namespace liminal_json_io {
    namespace types {

        using Object_t          =   _private::_complex_value::_Object;
        using Array_t           =   _private::_complex_value::_Array;

        using ComplexTypes_t    =   std::variant<Object_t, Array_t>; 

    } // namespace types
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__TYPES_COMPLEX_TYPES_HPP_