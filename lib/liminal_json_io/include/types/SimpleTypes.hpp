/**
 * @file SimpleTypes.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_SIMPLETYPES_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_SIMPLETYPES_HPP_

#include "_private/_parsing/_types.hpp"

namespace liminal_json_io {
    namespace types {

        using String_t      =   _private::_parsing::_types::_String_t;
        using IntNum_t      =   _private::_parsing::_types::_IntNum_t;
        using FloatNum_t    =   _private::_parsing::_types::_FloatNum_t;
        using Null_t        =   _private::_parsing::_types::_Null_t;
        using Bool_t        =   _private::_parsing::_types::_Bool_t;

        using SimpleTypes_t =   std::variant<String_t, IntNum_t, FloatNum_t, Null_t, Bool_t>;

    } // namespace types
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_SIMPLETYPES_HPP_