/**
 * @file types.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_

#include "_private/_parsing/_types.hpp"
#include "_private/_JsonValue.hpp"

namespace liminal_json_io {
    namespace types {

        using String_t      =   _private::_parsing::_types::_String_t;
        using IntNum_t      =   _private::_parsing::_types::_IntNum_t;
        using FloatNum_t    =   _private::_parsing::_types::_FloatNum_t;
        using Null_t        =   _private::_parsing::_types::_Null_t;
        using Bool_t        =   _private::_parsing::_types::_Bool_t;

        using Key_t         =   _private::_parsing::_types::_Key_t;

        using Array_t       =   std::vector<_private::_JsonValue>;
        using Object_t      =   std::unordered_map<Key_t, _private::_JsonValue>;

        using AnyType_t     =   std::variant<
                                    String_t,
                                    IntNum_t,
                                    FloatNum_t,
                                    Bool_t,
                                    Null_t,
                                    Array_t,
                                    Object_t
                                >;

    } // namespace types
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_