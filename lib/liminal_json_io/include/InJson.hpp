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
#include "types/types.hpp"
#include "_private/_is_in_variant.hpp"

#include "string.hpp"


#include <string>
#include <optional>
#include <stdexcept>

namespace liminal_json_io {

    class InJson : public _private::_JSON {

        public:
            
            template <typename T>
            requires _private::_is_in_variant_v<T, types::Any_t>
            std::optional<T> get(const std::string &jsonPath = "") const {
                _private::_JsonValue jsonValue{__getJsonValueFromPath(jsonPath)};
                if constexpr (!std::is_same_v<T, types::Object_t> && !std::is_same_v<T, types::Array_t>) {
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

            std::string getType(const std::string &jsonPath = "") const;

        private:
            _private::_JsonValue __getJsonValueFromPath(const std::string &jsonPath) const;
            static _private::_JsonValue __getObjectValue(const _private::_JsonValue &objectAsJsonValue, const std::string &key);
            static _private::_JsonValue __getArrayValue(const _private::_JsonValue &arrayAsJsonValue, const std::string &indexAsString);
    };

} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO_INJSON_HPP_