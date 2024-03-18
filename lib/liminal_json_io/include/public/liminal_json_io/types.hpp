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


#include "is_in_variant_v.hpp"

#include <variant>
#include <optional>
#include <iostream>
#include <string>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <memory>

namespace liminal_json_io {

    // Forward declarations :
    //**********
    namespace _private {
        class _JsonValue;
        namespace _parsing {
            namespace _types {
                using _Key_t = std::string;
            }
        }
    }
    //**********

    namespace types {
        using String_t      =   std::string;
        using IntNum_t      =   intmax_t;
        using FloatNum_t    =   long double;
        using Null_t        =   nullptr_t;
        using Bool_t        =   bool;

        using Key_t         =   String_t;

        using SimpleTypes_t =   std::variant<
                                    String_t,
                                    IntNum_t,
                                    FloatNum_t,
                                    Null_t,
                                    Bool_t
                                >;

        class Object {
            public:
                Object(const _private::_JsonValue &objectAsJsonValue);
                Object(const Object &other);
                ~Object();

                Object &operator=(const Object &other);

                // Complex value methods re declaration
                bool hasNestedComplexValues(void) const;
                std::vector<types::Key_t> getNestedComplexValuesKeys(void) const;
                
                // Own methods :
                template <typename T>
                requires is_in_variant_v<T, types::SimpleTypes_t>
                std::optional<T> get(const types::Key_t &key) const;
                
            private:
                class _ObjectImpl; //Forward declaration
                std::unique_ptr<_ObjectImpl> _objectImpl;

        };

        class Array {
            public:
                Array(const _private::_JsonValue &arrayAsJsonValue);
                Array(const Array &other);
                ~Array();

                Array &operator=(const Array &other);

                //Complex value methods re declaration
                bool hasNestedComplexValues(void) const;
                std::vector<std::size_t> getNestedComplexValuesIndices(void) const;

                // Own methods:
                template <typename T>
                requires is_in_variant_v<T, types::SimpleTypes_t>
                std::optional<T> get(const std::size_t &index) const;

                std::size_t getLen(void) const;
            
            private:
                class _ArrayImpl; //Forward declaration
                std::unique_ptr<_ArrayImpl> _arrayImpl;
        };

        using Object_t      =   Object;
        using Array_t       =   Array;

    }
    

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

        enum class ValueTypes {
            STRING,
            INT_NUM,
            FLOAT_NUM,
            BOOL,
            NULL_VALUE,
            ARRAY,
            OBJECT,
            UNKNOWN
        };

    } // namespace types
} // namespace liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_