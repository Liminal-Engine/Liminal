/**
 * @file _JsonValue.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_JsonValue.hpp"

#include "liminal_string_extras/string.hpp"

namespace liminal_json_io {
    namespace _private {

        _JsonValue::_JsonValue(const _lexing::_types::_Token_s &token) :
        _type{[&]() ->  _JsonValueTypes {
            if (token.type == _lexing::_types::_TokenTypes_e_c::SYNTAX) {
                throw std::runtime_error("Error : _JsonValue constructor received a syntax token. Got : " + token.strValue);
            }
            return this->__tokenTypeToJsonValueType(token.type);
        }()},
        _value{this->__tokenToValue(token)}
        {
            
        }

        _JsonValue::_JsonValue(const _parsing::_types::_Object_t &object) :
        _type{_JsonValueTypes::_OBJECT},
        _value{object}
        {

        }

        _JsonValue::_JsonValue(const _parsing::_types::_Array_t &array) :
        _type{_JsonValueTypes::_ARRAY},
        _value{array}
        {

        }

        _JsonValue::_JsonValue(const _JsonValue &newJsonValue) :
        _type(newJsonValue.getType()),
        _value(newJsonValue.getValue())
        {            
        }

        std::string _JsonValue::getTypeAsStr(void) const {
            switch (this->_type) {
                case _JsonValueTypes::_STRING:
                    return "string";
                case _JsonValueTypes::_INT:
                    return "int";
                case _JsonValueTypes::_FLOAT:
                    return "float";
                case _JsonValueTypes::_BOOL:
                    return "bool";
                case _JsonValueTypes::_JSON_NULL:
                    return "json_null";
                case _JsonValueTypes::_ARRAY:
                    return "array";
                case _JsonValueTypes::_OBJECT:
                    return "object";
                default:
                    throw std::runtime_error("Unknown type given");
            }
        }

        _parsing::_types::_Any_t _JsonValue::getValue(void) const { return this->_value; }

        _JsonValueTypes _JsonValue::getType(void) const { return this->_type; }

        _JsonValue &_JsonValue::operator=(const _JsonValue &other) {
            if (this != &other) {
                this->_type = other._type;
                this->_value = other._value;
            }
            return *this;
        }

        // Private :
        _JsonValueTypes _JsonValue::__tokenTypeToJsonValueType(const _lexing::_types::_TokenTypes_e_c &tokenType) const {
            switch (tokenType) {
                case _lexing::_types::_TokenTypes_e_c::STRING:
                    return _JsonValueTypes::_STRING;
                case _lexing::_types::_TokenTypes_e_c::INT_NUM:
                    return _JsonValueTypes::_INT;
                case _lexing::_types::_TokenTypes_e_c::FLOAT_NUM:
                    return _JsonValueTypes::_FLOAT;
                case _lexing::_types::_TokenTypes_e_c::NULL_:
                    return _JsonValueTypes::_JSON_NULL;
                case _lexing::_types::_TokenTypes_e_c::BOOL:
                    return _JsonValueTypes::_BOOL;
                default:
                    throw std::runtime_error("Unknown type given");
            }
        }

        _parsing::_types::_Any_t _JsonValue::__tokenToValue(const _lexing::_types::_Token_s &token) const {
            switch (token.type) {
                case _lexing::_types::_TokenTypes_e_c::STRING:
                    return token.strValue;
                case _lexing::_types::_TokenTypes_e_c::INT_NUM:
                    return liminal_parser::string::toIntMax(token.strValue);
                case _lexing::_types::_TokenTypes_e_c::FLOAT_NUM:
                    return liminal_parser::string::toLongDouble(token.strValue);
                case _lexing::_types::_TokenTypes_e_c::BOOL:
                    return liminal_parser::string::toBool(token.strValue);
                case _lexing::_types::_TokenTypes_e_c::NULL_:
                    return nullptr;
                case _lexing::_types::_TokenTypes_e_c::SYNTAX:
                    throw std::runtime_error("Error : syntax token encoutered.");
                default:
                    throw std::runtime_error("Unknown type given");;
            }
        }

    } // namespace _private
} // namespace liminal_json_io
