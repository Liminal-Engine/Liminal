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

#include "types/SimpleTypes.hpp"
#include "types/ComplexTypes.hpp"

#include <optional>
#include <iostream>

namespace liminal_json_io {
    namespace types {

        using Key_t         =   _private::_parsing::_types::_Key_t;

        using Any_t         =   std::variant<
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