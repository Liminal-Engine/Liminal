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

#ifndef LIMINAL_LIB_jsonio__PRIVATE__JSONVALUE_HPP_
#define LIMINAL_LIB_jsonio__PRIVATE__JSONVALUE_HPP_

#include "Status.hpp"
#include "is_in_variant_v.hpp"
#include "_private/_parsing/_types.hpp"
#include "_private/_JsonValueTypes.hpp"
#include "_private/_lexing/_types.hpp"
#include "_private/_types/_SimpleTypes.hpp"
#include "types.hpp"

#include <cstdint>
#include <optional>

namespace jsonio {
    namespace _private {
        
        class _JsonValue {
            public:
                virtual ~_JsonValue() = default;
                _JsonValue(const _lexing::_types::_Token_s &token);
                _JsonValue(const _parsing::_types::_Object_t &object);
                _JsonValue(const _parsing::_types::_Array_t &array);
                _JsonValue(const _JsonValue &newJsonValue);
                _JsonValue(const types::ValueTypes &type = types::ValueTypes::NULL_VALUE);
                _JsonValue &operator=(const _JsonValue &other);

                // Getters
                std::string getTypeAsStr(void) const;
                _parsing::_types::_Any_t getValue(void) const;
                _JsonValueTypes getType(void) const;

                // Setters
                template <typename T>
                requires is_in_variant_v<T, types::Any_t>
                Status update(const T &value);

                template<typename T>
                requires is_in_variant_v<T, types::Any_t>
                Status update(const types::Key_t &key, const T &value);

                template<typename T>
                requires is_in_variant_v<T, types::Any_t>
                Status update(const std::size_t &index, const T &value);
                
                Status addKey(
                    const _parsing::_types::_Key_t &key,
                    const types::ValueTypes &type = types::ValueTypes::NULL_VALUE,
                    const bool &erase = false
                );

                inline bool hasComplexType(void) const { return this->_type == _JsonValueTypes::_OBJECT or this->_type == _JsonValueTypes::_ARRAY; };
                inline bool hasSimpleType(void) const { return !this->hasComplexType(); };
                
                static std::optional<std::shared_ptr<class _JsonValue>> getOptionalJsonValueOfObject(
                    const _parsing::_types::_Object_t &object,
                    const _parsing::_types::_Key_t &key
                );
                static bool keyIsInObject(
                    const _parsing::_types::_Object_t &object,
                    const _parsing::_types::_Key_t &key
                );
                static std::shared_ptr<class _JsonValue> getJsonValueOfObject(
                    const _parsing::_types::_Object_t &object,
                    const _parsing::_types::_Key_t &key
                );



            private:
                _JsonValueTypes _type;
                _parsing::_types::_Any_t _value;

                _JsonValueTypes __tokenTypeToJsonValueType(const _lexing::_types::_TokenTypes_e_c &tokenType) const;
                _parsing::_types::_Any_t __tokenToValue(const _lexing::_types::_Token_s &token) const;
                static _JsonValueTypes __valueTypeToJsonValueType(const types::ValueTypes &type);
                static _parsing::_types::_Any_t __getDefaultValueFromType(const types::ValueTypes &type);
                
                template<typename T>
                requires is_in_variant_v<T, types::Any_t>
                static _JsonValueTypes __realTypeToJsonValueType(void);                

                _parsing::_types::_Object_t::const_iterator static __getIteratorOfObject(
                    const _parsing::_types::_Object_t &object,
                    const _parsing::_types::_Key_t &key
                );

        };
        
    } // namespace _private
} // namespace jsonio

#endif // LIMINAL_LIB_jsonio__PRIVATE__JSONVALUE_HPP_
