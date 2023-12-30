/**
 * @file _JsonValue.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSONVALUE_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSONVALUE_HPP_

#include "_private/_parsing/_types.hpp"
#include "_private/_JsonValueTypes.hpp"
#include "_private/_lexing/_types.hpp"

namespace liminal_json_io {
    namespace _private {
        
        class _JsonValue {
            public:
                virtual ~_JsonValue() = default;
                _JsonValue(const _lexing::_types::_Token_s &token);
                _JsonValue(const _parsing::_types::_Object_t &object);
                _JsonValue(const _parsing::_types::_Array_t &array);
                _JsonValue(const _JsonValue &newJsonValue);
                _JsonValue &operator=(const _JsonValue &other);

                // Getters
                std::string getTypeAsStr(void) const;
                _parsing::_types::_AnyType_t getValue(void) const;
                _JsonValueTypes getType(void) const;

            private:
                _JsonValueTypes _type;
                _parsing::_types::_AnyType_t _value;

                _JsonValueTypes __tokenTypeToJsonValueType(const _lexing::_types::_TokenTypes_e_c &tokenType) const;
                _parsing::_types::_AnyType_t __tokenToValue(const _lexing::_types::_Token_s &token) const;
        };
        
    } // namespace _private
} // namespace liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSONVALUE_HPP_
