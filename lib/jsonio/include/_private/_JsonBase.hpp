/**
 * @file _JsonBase.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef _LIMINAL_LIB_JSONIO__PRIVATE__JSONBASE_
#define _LIMINAL_LIB_JSONIO__PRIVATE__JSONBASE_

#include "Status.hpp"
#include "_private/_JsonValue.hpp"
#include "is_in_variant_v.hpp"
#include "types.hpp"
#include "separators.hpp"
#include "_private/_error/_Errors.hpp"

#include <parseop/parseop.hpp>
#include <fs/Path.hpp>

#include <string>
#include <optional>
#include <stdexcept>
#include <memory>
#include <array>


namespace jsonio {
    namespace _private {
        
        class _JsonBase {
            public:
                _JsonBase(void);
                Status parse(const fs::Path &path);

                types::ValueTypes getType(
                    const std::string &jsonPath = "",
                    const std::array<std::string, 3> &separators = JSON_DEFAULT_SEPARATORS
                ) const;

                template <typename T>
                requires is_in_variant_v<T, types::Any_t>
                std::optional<T> get(
                    const std::string &jsonPath = "",
                    const std::array<std::string, 3> &separators = JSON_DEFAULT_SEPARATORS
                ) const;

                template<typename T>
                requires is_in_variant_v<T, types::Any_t>
                Status insert(
                    const std::string &jsonPath = "",
                    const T &value = nullptr,
                    const bool &erase = false,
                    const std::array<std::string, 3> &separators = JSON_DEFAULT_SEPARATORS
                );

                Status write(const bool &erase = false) const;
                Status write(const fs::Path &path, const bool &erase = false) const;

            protected:
            
                std::shared_ptr<_JsonValue> _getJsonValueFromPath(
                    const std::string &jsonPath,
                    const std::array<std::string, 3> &separators
                ) const;
            
            private:
                std::optional<std::shared_ptr<_JsonValue>>  __rootValue;
                fs::Path __filePath;


                template<typename T>
                requires is_in_variant_v<T, types::Any_t>
                Status __insetInNewObjectKey(
                    const std::string &jsonPath,
                    const T &value,
                    const std::array<std::string, 3> &separators
                );

                template<typename T>
                requires is_in_variant_v<T, types::Any_t>            
                Status __insertInNewArrayIndex(
                    const std::string &jsonPath,
                    const T &value,
                    const std::array<std::string, 3> &separators
                );

                Status __writeSimpleTypedValue(const _private::_parsing::_types::_Any_t &value, std::stringstream &ss) const;
                
                Status __writeObject(
                    const std::shared_ptr<_private::_JsonValue> &jsonValue,
                    std::stringstream &ss,
                    std::size_t &depth
                ) const;

                Status __writeArray(
                    const std::shared_ptr<_private::_JsonValue> &jsonValue,
                    std::stringstream &ss,
                    std::size_t &depth
                ) const;

                static std::shared_ptr<_JsonValue> __getObjectValue(const std::shared_ptr<_JsonValue> &objectAsJsonValue, const std::string &key);
                static std::shared_ptr<_JsonValue> __getArrayValue(const std::shared_ptr<_JsonValue> &arrayAsJsonValue, const std::string &indexAsString);

                static Status __writeFileContent(const fs::Path &path, const std::string &str);
        };

    } // namespace _private
} // namespace jsonio



#endif // _LIMINAL_LIB_JSONIO__PRIVATE__JSONBASE_