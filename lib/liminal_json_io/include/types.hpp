/**
 * @file types.h
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_

#include <string>
#include <vector>
#include <utility>
#include <variant>
#include <cstdint>

namespace liminal_json_io {
    namespace types {        

        using String_t      =   std::string;
        using IntNum_t      =   intmax_t;
        using FloatNum_t    =   long double;
        using Null_t        =   std::nullptr_t;
        using Bool_t        =   bool;

        using Key_t         =   String_t;
        using Array_t       =   std::vector<class Ivalue>;
        using Object_t      =   std::vector<std::pair<Key_t, class Ivalue>>;
        using AnyType_t     =   std::variant<String_t, IntNum_t, FloatNum_t, Null_t, Bool_t>;        

        // class IValue {
        //     public:
        //         virtual ~IValue() = default;
        //         virtual AnyType_t getValue(void) const = 0;
                
        //         // template <typename ValueType>
        //         // ValueType getValue(const AnyType_t &type) const{
        //         //     return
        //         // }
        // };

        // class StringValue : public IValue {

        // }



    } // namespace types
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_