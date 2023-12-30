/**
 * @file InJson.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO_INJSON_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO_INJSON_HPP_

#include "_private/_JSON.hpp"
#include "_private/_JsonValueTypes.hpp"
#include "_private/_parsing/_types.hpp"
#include "types.hpp"

#include "string.hpp"


#include <string>
#include <optional>
#include <stdexcept>

namespace liminal_json_io {

    class InJson : public _private::_JSON {

        public:
            template <typename T, typename Variant>
            struct is_in_variant;

            template <typename T, typename... Ts>
            struct is_in_variant<T, std::variant<Ts...>> : std::bool_constant<(std::is_same_v<T, Ts> || ...)> {};

            template <typename T, typename V>
            static inline constexpr bool is_in_variant_v = is_in_variant<T, V>::value;

            template <typename T>
            requires is_in_variant_v<T, types::AnyType_t>
            std::optional<T> get(const std::string &jsonPath) const {
                if (this->_rootValue.has_value() == false) {
                    throw std::runtime_error("JSON has not been loaded.");
                }
                std::vector<std::string> tokenizedPath = liminal_parser::string::tokenize(jsonPath, std::vector<std::string>{".", "[", "]"});
                _private::_JsonValue tmpJsonValue{this->_rootValue.value()};


                for (const std::string &key : tokenizedPath) {
                    if (tmpJsonValue.getType() == _private::_JsonValueTypes::_OBJECT) {
                        tmpJsonValue = _private::_JsonValue{this->__getObjectValue(tmpJsonValue, key)};
                    } else if (tmpJsonValue.getType() == _private::_JsonValueTypes::_ARRAY) {
                        tmpJsonValue = _private::_JsonValue{this->__getArrayValue(tmpJsonValue, key)};
                    }
                }
                if constexpr (!std::is_same_v<T, types::Object_t> && !std::is_same_v<T, types::Array_t>) {
                    std::optional<T> res{};
                    _private::_parsing::_types::_AnyType_t resAnyValue = tmpJsonValue.getValue();//TODO : create a tpyes::Simple_types variant and complex types varaint and cast only on simple_types here, not anytypes
                    T *resPtr = std::get_if<T>(&resAnyValue);
                    if (resPtr != nullptr) {
                        res.emplace(*resPtr);
                    }
                    return res;
                }
                if constexpr (std::is_same_v<T, types::Object_t>) return jsonValueToObject(tmpJsonValue);
                if constexpr (std::is_same_v<T, types::Array_t>) return jsonValueToArray(tmpJsonValue);
            }

            static std::optional<types::Object_t> jsonValueToObject(const _private::_JsonValue &objectAsJsonValue);
            static std::optional<types::Array_t> jsonValueToArray(const _private::_JsonValue &arrayAsJsonValue);

        private:
            _private::_JsonValue __getObjectValue(const _private::_JsonValue &objectAsJsonValue, const std::string &key) const;
            _private::_JsonValue __getArrayValue(const _private::_JsonValue &arrayAsJsonValue, const std::string &indexAsString) const;
    };

} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO_INJSON_HPP_