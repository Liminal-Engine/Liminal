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
#include "_private/_error/_Errors.hpp"

#include <parseop/parseop.hpp>

namespace jsonio {
    namespace _private {

        _JsonValue::_JsonValue(const _lexing::_types::_Token_s &token) :
        _type{[&]() ->  _JsonValueTypes {
            if (token.getType() == _lexing::_types::_TokenTypes_e_c::SYNTAX)
                THROW(_private::_error::_Parsing, "Error : _JsonValue constructor received a syntax token. Got : %s", token.getValueAsStr().c_str());
            return this->__tokenTypeToJsonValueType(token.getType());
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

        _JsonValue::_JsonValue(const types::ValueTypes &type) :
        _type(__valueTypeToJsonValueType(type)),
        _value(__getDefaultValueFromType(type))
        {}

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
                    THROW(_private::_error::_Type, "Unknown type, got : %d", this->_type);
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

        template <typename T>
        requires is_in_variant_v<T, types::Any_t>
        Status _JsonValue::update(const T &value) {        
            if constexpr (is_in_variant_v<T, types::SimpleTypes_t>) {
                this->_value = value;
                this->_type = __realTypeToJsonValueType<T>();
                return Status::OK;
            } else if constexpr (std::is_same_v<T, types::Object_t>) {
                this->_value = _parsing::_types::_Object_t();
                this->_type = _JsonValueTypes::_OBJECT;
                return Status::OK;
            } else if constexpr (std::is_same_v<T, types::Array_t>) {
                this->_value = _parsing::_types::_Array_t();
                this->_type = _JsonValueTypes::_ARRAY;
                return Status::OK;
            } else return Status::E_TYPE;
            return Status::E_NOK;
        };

        #define instantiate_jsonvalue_value_method(TYPE)\
            template Status _JsonValue::update<TYPE>(const TYPE &);

            instantiate_jsonvalue_value_method(types::String_t)
            instantiate_jsonvalue_value_method(types::IntNum_t)
            instantiate_jsonvalue_value_method(types::FloatNum_t)
            instantiate_jsonvalue_value_method(types::Bool_t)
            instantiate_jsonvalue_value_method(types::Null_t)
            instantiate_jsonvalue_value_method(types::Object_t)
            instantiate_jsonvalue_value_method(types::Array_t)
        #undef instantiate_jsonvalue_value_method

            template<typename T>
            requires is_in_variant_v<T, types::Any_t>
            Status _JsonValue::update(const types::Key_t &key, const T &value) {
                if (
                    !std::holds_alternative<_parsing::_types::_Object_t>(this->_value) ||
                    this->getType() != _JsonValueTypes::_OBJECT
                ) return Status::E_TYPE;
                
                // 1. First, get the object as a _parsing::_types::_Object_t and add key and empty value
                _parsing::_types::_Object_t &valueAsObject = std::get<_parsing::_types::_Object_t>(this->_value);
                valueAsObject.push_back({key, std::make_shared<_JsonValue>()});
                // 2. Then, get the object as _JsonValue now that the key exists and update with the actual real value
                // It's important to understand here that both valueAsObject and jsonValue points to the same json object
                std::optional<std::shared_ptr<_JsonValue>> jsonValue = this->getOptionalJsonValueOfObject(valueAsObject, key);
                if ( !jsonValue.has_value() ) return Status::E_KEY_EXISTS;
                return jsonValue.value()->update(value); // create value
            }

        #define instantiate_jsonvalue_key_value_method(TYPE)\
            template Status _JsonValue::update<TYPE>(const types::Key_t &, const TYPE &);

            instantiate_jsonvalue_key_value_method(types::String_t)
            instantiate_jsonvalue_key_value_method(types::IntNum_t)
            instantiate_jsonvalue_key_value_method(types::FloatNum_t)
            instantiate_jsonvalue_key_value_method(types::Bool_t)
            instantiate_jsonvalue_key_value_method(types::Null_t)
            instantiate_jsonvalue_key_value_method(types::Object_t)
            instantiate_jsonvalue_key_value_method(types::Array_t)
        #undef instantiate_jsonvalue_key_value_method

            template<typename T>
            requires is_in_variant_v<T, types::Any_t>
            Status _JsonValue::update(const std::size_t &index, const T &value) {
                if (
                    !std::holds_alternative<_parsing::_types::_Array_t>(this->_value) ||
                    this->getType() != _JsonValueTypes::_ARRAY
                ) return Status::E_TYPE;

                _parsing::_types::_Array_t &valueAsArray = std::get<_parsing::_types::_Array_t>(this->_value);
                // create new entry in array if given index is last index
                if (index == valueAsArray.size()) valueAsArray.push_back(std::make_shared<_JsonValue>());
                if (index < valueAsArray.size()) {
                    valueAsArray[index]->update<T>(value);
                    return Status::OK;
                }
                return Status::E_INDEX;
            }
        
        #define instantiate_jsonvalue_index_value_method(TYPE) \
            template Status _JsonValue::update<TYPE>(const std::size_t &, const TYPE &);

            instantiate_jsonvalue_index_value_method(types::String_t)
            instantiate_jsonvalue_index_value_method(types::IntNum_t)
            instantiate_jsonvalue_index_value_method(types::FloatNum_t)
            instantiate_jsonvalue_index_value_method(types::Bool_t)
            instantiate_jsonvalue_index_value_method(types::Null_t)
            instantiate_jsonvalue_index_value_method(types::Object_t)
            instantiate_jsonvalue_index_value_method(types::Array_t)
        #undef instantiate_jsonvalue_index_value_method

        Status _JsonValue::addKey(
            const _parsing::_types::_Key_t &key,
            const types::ValueTypes &type,
            const bool &erase
        ) {
            if (
                this->getType() != _JsonValueTypes::_OBJECT ||
                !std::holds_alternative<_parsing::_types::_Object_t>(this->_value)
            ) {
                return Status::E_TYPE;
            }
            _parsing::_types::_Object_t &object = std::get<_parsing::_types::_Object_t>(this->_value);
            std::optional< std::shared_ptr<_JsonValue> > jsonValue = this->getOptionalJsonValueOfObject(object, key);
            if ( jsonValue.has_value() || erase ) {
                jsonValue.value() = std::make_shared<_JsonValue>(type);
                return Status::OK;
            }
            return Status::E_KEY_EXISTS;

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
                    THROW(_private::_error::_Type, "Unknown type given, got: %d", tokenType);
            }
        }

        _parsing::_types::_Any_t _JsonValue::__tokenToValue(const _lexing::_types::_Token_s &token) const {
            switch (token.getType()) {
                case _lexing::_types::_TokenTypes_e_c::STRING:
                    return token.getValueAsStr();
                case _lexing::_types::_TokenTypes_e_c::INT_NUM:
                    return parseop::toLongInt(token.getValueAsStr());
                case _lexing::_types::_TokenTypes_e_c::FLOAT_NUM: 
                    return parseop::toLongDouble(token.getValueAsStr());
                case _lexing::_types::_TokenTypes_e_c::BOOL:
                    return parseop::toBool(token.getValueAsStr());
                case _lexing::_types::_TokenTypes_e_c::NULL_:
                    return nullptr;
                case _lexing::_types::_TokenTypes_e_c::SYNTAX:
                    THROW(_private::_error::_Parsing, "Error : syntax token encoutered.");
                default:
                    THROW(_private::_error::_Parsing, "Unknown type given. Got: %d", token.getType());
            }
        }

        template<typename T>
        requires is_in_variant_v<T, types::Any_t>
        _JsonValueTypes _JsonValue::__realTypeToJsonValueType(void) {
            if constexpr (std::is_same_v<T, types::Object_t>) return _JsonValueTypes::_OBJECT;
            if constexpr (std::is_same_v<T, types::Array_t>) return _JsonValueTypes::_ARRAY;
            if constexpr (std::is_same_v<T, types::String_t>) return _JsonValueTypes::_STRING;
            if constexpr (std::is_same_v<T, types::IntNum_t>) return _JsonValueTypes::_INT;
            if constexpr (std::is_same_v<T, types::FloatNum_t>) return _JsonValueTypes::_FLOAT;
            if constexpr (std::is_same_v<T, types::Bool_t>) return _JsonValueTypes::_BOOL;
            if constexpr (std::is_same_v<T, types::Null_t>) return _JsonValueTypes::_JSON_NULL;
            return _JsonValueTypes::_UNKNOWN;
        }

        _JsonValueTypes _JsonValue::__valueTypeToJsonValueType(const types::ValueTypes &type) {
            switch (type) {
                case types::ValueTypes::STRING :
                    return _JsonValueTypes::_STRING;
                case types::ValueTypes::INT_NUM :
                    return _JsonValueTypes::_INT;
                case types::ValueTypes::FLOAT_NUM :
                    return _JsonValueTypes::_FLOAT;
                case types::ValueTypes::BOOL :
                    return _JsonValueTypes::_BOOL;
                case types::ValueTypes::NULL_VALUE :
                    return _JsonValueTypes::_JSON_NULL;
                case types::ValueTypes::ARRAY :
                    return _JsonValueTypes::_ARRAY;
                case types::ValueTypes::OBJECT :
                    return _JsonValueTypes::_OBJECT;
                case types::ValueTypes::UNKNOWN :
                    return _JsonValueTypes::_UNKNOWN;
                default:
                    return _JsonValueTypes::_UNKNOWN;
            }
            return _JsonValueTypes::_UNKNOWN;
        }

        _parsing::_types::_Any_t _JsonValue::__getDefaultValueFromType(const types::ValueTypes &type) {
            switch (type) {
                case types::ValueTypes::STRING :
                    return "";
                case types::ValueTypes::INT_NUM :
                    return 0;
                case types::ValueTypes::FLOAT_NUM :
                    return 0.0f;
                case types::ValueTypes::BOOL :
                    return false;
                case types::ValueTypes::NULL_VALUE :
                case types::ValueTypes::UNKNOWN :
                    return nullptr;
                case types::ValueTypes::ARRAY :
                    return _parsing::_types::_Array_t{};
                case types::ValueTypes::OBJECT :
                    return _parsing::_types::_Object_t();
                default:
                    return nullptr;
            }
            return nullptr;
        }

        bool _JsonValue::keyIsInObject(
            const _parsing::_types::_Object_t &object,
            const _parsing::_types::_Key_t &key
        ) {
            return __getIteratorOfObject(object, key) != object.end();
        }

        std::optional<std::shared_ptr<class _JsonValue>> _JsonValue::getOptionalJsonValueOfObject(
            const _parsing::_types::_Object_t &object,
            const _parsing::_types::_Key_t &key
        ) {
            auto it = __getIteratorOfObject(object, key);
            return it != object.end() ? std::optional<std::shared_ptr<_JsonValue>>(it->second) : std::nullopt;
        }

        std::shared_ptr<class _JsonValue> _JsonValue::getJsonValueOfObject(
            const _parsing::_types::_Object_t &object,
            const _parsing::_types::_Key_t &key
        ) {
            auto it = __getIteratorOfObject(object, key);
            return it != object.end() ? it->second : nullptr;
        }

        

        _parsing::_types::_Object_t::const_iterator _JsonValue::__getIteratorOfObject(
            const _parsing::_types::_Object_t &object,
            const _parsing::_types::_Key_t &key
        ) {
            return std::find_if(object.begin(), object.end(), [&key](const auto &pair) { return pair.first == key; });
        }


    } // namespace _private
} // namespace jsonio
