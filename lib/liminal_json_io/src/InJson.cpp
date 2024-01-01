/**
 * @file InJson.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright Copyright (c) 2023
 * 
*/


#include "InJson.hpp"

#include <iostream>

namespace liminal_json_io {

    // Public:
    std::string InJson::getType(const std::string &jsonPath) const {
        return this->__getJsonValueFromPath(jsonPath).getTypeAsStr();
    }

    // Private :
    _private::_JsonValue InJson::__getJsonValueFromPath(const std::string &jsonPath) const {
        if (this->_rootValue.has_value() == false) {
            throw std::runtime_error("JSON has not been loaded.");
        }
        std::vector<std::string> tokenizedPath = liminal_parser::string::tokenize(jsonPath, std::vector<std::string>{".", "[", "]"});
        _private::_JsonValue tmpJsonValue{this->_rootValue.value()};


        for (const std::string &key : tokenizedPath) {
            if (tmpJsonValue.getType() == _private::_JsonValueTypes::_OBJECT) {
                tmpJsonValue = _private::_JsonValue{__getObjectValue(tmpJsonValue, key)};
            } else if (tmpJsonValue.getType() == _private::_JsonValueTypes::_ARRAY) {
                tmpJsonValue = _private::_JsonValue{__getArrayValue(tmpJsonValue, key)};
            }
        }
        return tmpJsonValue;
    }

    //S Static : 
    _private::_JsonValue InJson::__getObjectValue(const _private::_JsonValue &objectAsJsonValue, const std::string &key) {
        _private::_parsing::_types::_Any_t tmpAnyValue = objectAsJsonValue.getValue();
        _private::_parsing::_types::_Object_t *tmpObjectPtr = std::get_if<_private::_parsing::_types::_Object_t>(&tmpAnyValue);

        if (tmpObjectPtr == nullptr) {
            throw std::runtime_error("Value is set as object but is not an actual object. Critical error in parsing.");
        }
        // Now, find the specific key
        if ((*tmpObjectPtr).contains(key) == false) {
            throw std::runtime_error("Failed to find given key in Object. Got key = " + key);
        }
        _private::_JsonValue *nextJsonValuePtr = (*tmpObjectPtr)[key].get();
        return _private::_JsonValue(*nextJsonValuePtr);
    }

    _private::_JsonValue InJson::__getArrayValue(const _private::_JsonValue &arrayAsJsonValue, const std::string &indexAsString) {
        _private::_parsing::_types::_Any_t tmpAnyValue = arrayAsJsonValue.getValue();
        _private::_parsing::_types::_Array_t *tmpArrayPtr = std::get_if<_private::_parsing::_types::_Array_t>(&tmpAnyValue);

        if (tmpArrayPtr == nullptr) {
            throw std::runtime_error("Value is set as array but is not an actual array. Critical error in parsing.");
        }
        if (liminal_parser::string::isNonNegativeInteger(indexAsString) == false) {
            throw std::runtime_error("Received an invalid index : " + indexAsString);
        }
        std::size_t index = liminal_parser::string::toSize_t(indexAsString);
        if (index >= (*tmpArrayPtr).size()) {
            throw std::runtime_error("Index greater than the array size. Index = " + indexAsString + " array size = " + std::to_string((*tmpArrayPtr).size()));
        }
        _private::_JsonValue *nextJsonValuePtr = (*tmpArrayPtr).at(index).get();
        return _private::_JsonValue(*nextJsonValuePtr);
    }
    
} // namespace liminal_json_io
