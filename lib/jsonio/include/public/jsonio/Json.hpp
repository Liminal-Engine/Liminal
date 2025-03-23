/**
 * @file Json.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "Status.hpp"
#include "types.hpp"
#include "separators.hpp"

#include <fs/Path.hpp>

#include <array>
#include <string>
#include <optional>
#include <memory>

#ifndef _LIMINAL__JSONIO__JSON_HPP_
#define _LIMINAL__JSONIO__JSON_HPP_

namespace jsonio {
    class Json {
        public:
            Json(void);
            ~Json();

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

        private:
            class _JsonImpl;
            std::shared_ptr<_JsonImpl> _impl;
    };
} // namespace jsonio


#endif // _LIMINAL__JSONIO__JSON_HPP_