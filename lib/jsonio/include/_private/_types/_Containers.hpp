/**
 * @file _Containers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef _LIMINAL_LIB_JSONIO__PRIVATE__TYPES_CONTAINERS_HPP_
#define _LIMINAL_LIB_JSONIO__PRIVATE__TYPES_CONTAINERS_HPP_

#include "_private/_container/_Object.hpp"
#include "_private/_container/_Array.hpp"

#include <variant>

namespace jsonio {
    namespace types {

        using Object_t          =   _private::_container::_Object;
        using Array_t           =   _private::_container::_Array;

        using Containers_t    =   std::variant<Object_t, Array_t>; 

    } // namespace types
} // namespace jsonio


#endif // _LIMINAL_LIB_JSONIO__PRIVATE__TYPES_CONTAINERS_HPP_