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

namespace liminal_json_io {

    // Private :
    types::JsonValue InJson::__getObjectValue(const types::JsonValue &objectAsJsonValue, const std::string &key) const {
        types::AnyType_t tmpAnyValue = objectAsJsonValue.getValue();
        types::Object_t *tmpObjectPtr = std::get_if<types::Object_t>(&tmpAnyValue);

        if (tmpObjectPtr == nullptr) {
            throw std::runtime_error("Value is set as object but is not an actual object. Critical error in parsing.");
        }
        // Now, find the specific key
        if ((*tmpObjectPtr).contains(key) == false) {
            throw std::runtime_error("Failed to find given key in Object. Got key = " + key);
        }
        types::JsonValue *nextJsonValuePtr = (*tmpObjectPtr)[key].get();
        return types::JsonValue(*nextJsonValuePtr);
    }

    types::JsonValue InJson::__getArrayValue(const types::JsonValue &arrayAsJsonValue, const std::string &indexAsString) const {
        types::AnyType_t tmpAnyValue = arrayAsJsonValue.getValue();
        types::Array_t *tmpArrayPtr = std::get_if<types::Array_t>(&tmpAnyValue);

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
        types::JsonValue *nextJsonValuePtr = (*tmpArrayPtr).at(index).get();
        return types::JsonValue(*nextJsonValuePtr);
    }
    
} // namespace liminal_json_io
