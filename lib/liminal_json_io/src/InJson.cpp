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

#include "is_in_variant_v.hpp"

#include "_private/_JsonValue.hpp"
#include "_private/_parsing/_types.hpp"
#include "_private/_JSON.hpp"

#include <iostream>

namespace liminal_json_io
{

    class InJson::_InJsonImpl : public _private::_JSON
    {

        public:
            _InJsonImpl(void) :
            _private::_JSON{}
            {

            }

            std::string getType(const std::string &jsonPath) const {
               return this->__getJsonValueFromPath(jsonPath).getTypeAsStr();
            }

            template <typename T>
            requires is_in_variant_v<T, types::Any_t>
            std::optional<T> get(const std::string &jsonPath = "") const {
                _private::_JsonValue jsonValue{__getJsonValueFromPath(jsonPath)};
                if constexpr (!std::is_same_v<T, types::Object_t> && !std::is_same_v<T, types::Array_t>)
                {
                    std::optional<T> res{};
                    _private::_parsing::_types::_Any_t resAnyValue = jsonValue.getValue();
                    T *resPtr = std::get_if<T>(&resAnyValue);
                    if (resPtr != nullptr) {
                        res.emplace(*resPtr);
                    }
                    return res;
                }
                if constexpr (std::is_same_v<T, types::Object_t>) return types::Object_t(jsonValue);
                if constexpr (std::is_same_v<T, types::Array_t>) return types::Array_t(jsonValue);
            }

        private:
            _private::_JsonValue __getJsonValueFromPath(const std::string &jsonPath) const {
                if (this->_rootValue.has_value() == false) {
                    throw std::runtime_error("JSON has not been loaded.");
                }
                std::vector<std::string> tokenizedPath = liminal_parser::string::tokenize(jsonPath, std::vector<std::string>{".", "[", "]"});
                _private::_JsonValue tmpJsonValue{this->_rootValue.value()};

                for (const std::string &key : tokenizedPath) {
                    if (tmpJsonValue.getType() == _private::_JsonValueTypes::_OBJECT) {
                        tmpJsonValue = _private::_JsonValue{__getObjectValue(tmpJsonValue, key)};
                    }
                    else if (tmpJsonValue.getType() == _private::_JsonValueTypes::_ARRAY) {
                        tmpJsonValue = _private::_JsonValue{__getArrayValue(tmpJsonValue, key)};
                    }
                }
                return tmpJsonValue;
            }

            static _private::_JsonValue __getObjectValue(const _private::_JsonValue &objectAsJsonValue, const std::string &key) {
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

            static _private::_JsonValue __getArrayValue(const _private::_JsonValue &arrayAsJsonValue, const std::string &indexAsString) {
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

    };

    // Public :
    InJson::InJson(void) :
    _inJsonImpl{std::make_unique<_InJsonImpl>()}
    {
    }

    InJson::~InJson() = default;

    // Re declaration of _JSON methods :
    Status InJson::parse(const std::string &path) { return this->_inJsonImpl->parse(path); }

    // Own methods 

    template <typename T>
    requires is_in_variant_v<T, types::Any_t>
    std::optional<T> InJson::get(const std::string &jsonPath) const {
        return this->_inJsonImpl->get<T>(jsonPath);
    }

        #define instantiate_template_function(type)\
            template std::optional<type> InJson::get(const std::string &) const;

        instantiate_template_function(types::String_t)
        instantiate_template_function(types::IntNum_t)
        instantiate_template_function(types::FloatNum_t)
        instantiate_template_function(types::Bool_t)
        instantiate_template_function(types::Null_t)
        instantiate_template_function(types::Object_t)
        instantiate_template_function(types::Array_t)

        #undef instantiate_template_function

    std::string InJson::getType(const std::string &jsonPath) const {
        return _inJsonImpl->getType(jsonPath);
    }

} // namespace liminal_json_io
