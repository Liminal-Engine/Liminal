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

    // Static:
    std::optional<types::Object_t> InJson::jsonValueToObject(const _private::_JsonValue &objectAsJsonValue) {
        if (objectAsJsonValue.getType() != _private::_JsonValueTypes::_OBJECT) {
            std::cerr << "Value is requested as object but not mark as object. It may be a user error or a critical parsing error." << std::endl;
            return std::optional<types::Object_t>{};
        }
        types::Object_t object{};
        _private::_parsing::_types::_AnyType_t tmpAnyValue = objectAsJsonValue.getValue();
        _private::_parsing::_types::_Object_t *parsingObjectPtr = std::get_if<_private::_parsing::_types::_Object_t>(&tmpAnyValue);
        if (parsingObjectPtr == nullptr) {
            std::cerr << "Failed to find an object value. It may be a user error or a critical parsing error.";
            return std::optional<types::Object_t>{};
        }
        for (const auto &[key, value] : (*parsingObjectPtr)) {
            object.insert({key, _private::_JsonValue(*(value.get()))});
        }
        return object;
    }
      
    std::optional<types::Array_t> InJson::jsonValueToArray(const _private::_JsonValue &arrayAsJsonValue) {
        if (arrayAsJsonValue.getType() != _private::_JsonValueTypes::_ARRAY) {
            std::cerr << "Value is requested as array but not mark as array. It may be a user error or a critical parsing error." << std::endl;
            return std::optional<types::Array_t>{};
        }
        types::Array_t array{};
        _private::_parsing::_types::_AnyType_t tmpAnyValue = arrayAsJsonValue.getValue();
        _private::_parsing::_types::_Array_t *parsingArrayPtr = std::get_if<_private::_parsing::_types::_Array_t>(&tmpAnyValue);
        if (parsingArrayPtr == nullptr) {
            std::cerr << "Failed to find an array value. It may be a user error or a critical parsing error.";
            return std::optional<types::Array_t>{};
        }
        for (const auto &element : (*parsingArrayPtr)) {
            array.push_back(_private::_JsonValue(*(element.get())));
        }
        return array;
    }


    // Private :
    _private::_JsonValue InJson::__getObjectValue(const _private::_JsonValue &objectAsJsonValue, const std::string &key) const {
        _private::_parsing::_types::_AnyType_t tmpAnyValue = objectAsJsonValue.getValue();
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

    _private::_JsonValue InJson::__getArrayValue(const _private::_JsonValue &arrayAsJsonValue, const std::string &indexAsString) const {
        _private::_parsing::_types::_AnyType_t tmpAnyValue = arrayAsJsonValue.getValue();
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
