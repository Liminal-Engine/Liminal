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

#include "_private/_lexing/_types.hpp"

#include <string>
#include <vector>
#include <utility>
#include <variant>
#include <cstdint>
#include <any>
#include <unordered_map>
#include <memory>

namespace liminal_json_io {
    namespace types {

        using String_t      =   std::string;
        using IntNum_t      =   intmax_t;
        using FloatNum_t    =   long double;
        using Null_t        =   std::nullptr_t;
        using Bool_t        =   bool;

        using Key_t         =   String_t;
        // using Value_t       =   std::any; // TODO: change this for a class, variant or any_of.
        using Array_t       =   std::vector<std::shared_ptr<class JsonValue>>;
        using Object_t      =   std::unordered_map<Key_t, std::shared_ptr<class JsonValue>>;

        using AnyType_t     =   std::variant<String_t, IntNum_t, FloatNum_t, Bool_t, Null_t, Array_t, Object_t, std::shared_ptr<class JsonValue>>;        

        enum class ValueTypes {
            STRING,
            INT,
            FLOAT,
            BOOL,
            JSON_NULL,
            ARRAY,
            OBJECT
        };
        class JsonValue {
            public: //TODO : private this ?
                virtual ~JsonValue() = default;
                JsonValue(const _private::_lexing::_types::_Token_s &token);
                JsonValue(const types::Object_t &object);
                JsonValue(const types::Array_t &array);
                JsonValue(const JsonValue &newJsonValue);

                // Getters
                std::string getTypeAsStr(void) const;
                AnyType_t getValue(void) const;
                ValueTypes getType(void) const;

                JsonValue &operator=(const JsonValue &other);

            private:
                ValueTypes _type;
                AnyType_t _value;

                JsonValue(const ValueTypes &type, const AnyType_t &value);
                ValueTypes _tokenTypeToValueType(const _private::_lexing::_types::_TokenTypes_e_c &tokenType) const;
                AnyType_t _tokenToValue(const _private::_lexing::_types::_Token_s &token) const;
        };

    } // namespace types
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_