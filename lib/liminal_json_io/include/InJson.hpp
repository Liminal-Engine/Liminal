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
                types::JsonValue tmpJsonValue{this->_rootValue.value()};


                for (const std::string &key : tokenizedPath) {
                    if (tmpJsonValue.getType() == types::ValueTypes::OBJECT) {
                        tmpJsonValue = types::JsonValue{this->__getObjectValue(tmpJsonValue, key)};
                    } else if (tmpJsonValue.getType() == types::ValueTypes::ARRAY) {
                        tmpJsonValue = types::JsonValue{this->__getArrayValue(tmpJsonValue, key)};
                    }
                }
                std::optional<T> res{};
                types::AnyType_t resAnyValue = tmpJsonValue.getValue();
                T *resPtr = std::get_if<T>(&resAnyValue);
                if (resPtr != nullptr) {
                    res.emplace(*resPtr);
                }
                return res;
            }

        private:
            types::JsonValue __getObjectValue(const types::JsonValue &objectAsJsonValue, const std::string &key) const;
            types::JsonValue __getArrayValue(const types::JsonValue &arrayAsJsonValue, const std::string &indexAsString) const;

    };

} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO_INJSON_HPP_