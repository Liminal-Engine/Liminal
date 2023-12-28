/**
 * @file types.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "types.hpp"

#include "string.hpp"

#include <stdexcept>

namespace liminal_json_io {

    namespace types {

        JsonValue::JsonValue(const _private::_lexing::_types::_Token_s &token) :
        _type{[&]() ->  ValueTypes {
            if (token.type == _private::_lexing::_types::_TokenTypes_e_c::SYNTAX) {
                throw std::runtime_error("Error : JsonValue constructor received a syntax token. Got : " + token.strValue);
            }
            return this->_tokenTypeToValueType(token.type);
        }()},
        _value{this->_tokenToValue(token)}
        {
            
        }

        JsonValue::JsonValue(const types::Object_t &object) :
        _type{types::ValueTypes::OBJECT},
        _value{object}
        {

        }

        JsonValue::JsonValue(const types::Array_t &array) :
        _type{types::ValueTypes::ARRAY},
        _value{array}
        {

        }

        JsonValue::JsonValue(const JsonValue &newJsonValue) :
        _type(newJsonValue.getType()),
        _value(newJsonValue.getValue())
        {            
        }

        std::string JsonValue::getTypeAsStr(void) const {
            switch (this->_type) {
                case ValueTypes::STRING:
                    return "string";
                case ValueTypes::INT:
                    return "int";
                case ValueTypes::FLOAT:
                    return "float";
                case ValueTypes::BOOL:
                    return "bool";
                case ValueTypes::JSON_NULL:
                    return "json_null";
                case ValueTypes::ARRAY:
                    return "array";
                case ValueTypes::OBJECT:
                    return "object";
                default:
                    throw std::runtime_error("Unknown type given");
            }
        }

        AnyType_t JsonValue::getValue(void) const { return this->_value; }

        ValueTypes JsonValue::getType(void) const { return this->_type; }

        // Private :
        ValueTypes JsonValue::_tokenTypeToValueType(const _private::_lexing::_types::_TokenTypes_e_c &tokenType) const {
            switch (tokenType) {
                case _private::_lexing::_types::_TokenTypes_e_c::STRING:
                    return ValueTypes::STRING;
                case _private::_lexing::_types::_TokenTypes_e_c::INT_NUM:
                    return ValueTypes::INT;
                case _private::_lexing::_types::_TokenTypes_e_c::FLOAT_NUM:
                    return ValueTypes::FLOAT;
                case _private::_lexing::_types::_TokenTypes_e_c::NULL_:
                    return ValueTypes::JSON_NULL;
                case _private::_lexing::_types::_TokenTypes_e_c::BOOL:
                    return ValueTypes::BOOL;
                default:
                    throw std::runtime_error("Unknown type given");
            }
        }

        AnyType_t JsonValue::_tokenToValue(const _private::_lexing::_types::_Token_s &token) const {
            switch (token.type) {
                case _private::_lexing::_types::_TokenTypes_e_c::STRING:
                    return token.strValue;
                case _private::_lexing::_types::_TokenTypes_e_c::INT_NUM:
                    return liminal_parser::string::toIntMax(token.strValue);
                case _private::_lexing::_types::_TokenTypes_e_c::FLOAT_NUM:
                    return liminal_parser::string::toLongDouble(token.strValue);
                case _private::_lexing::_types::_TokenTypes_e_c::BOOL:
                    return liminal_parser::string::toBool(token.strValue);
                case _private::_lexing::_types::_TokenTypes_e_c::NULL_:
                    return nullptr;
                case _private::_lexing::_types::_TokenTypes_e_c::SYNTAX:
                    throw std::runtime_error("Error : syntax token encoutered.");
                default:
                    throw std::runtime_error("Unknown type given");;
            }
        }


    } // namespace types
} // namespace liminal_json_io
