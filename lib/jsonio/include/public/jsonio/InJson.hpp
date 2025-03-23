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

#ifndef LIMINAL_LIB_jsonio_INJSON_HPP_
#define LIMINAL_LIB_jsonio_INJSON_HPP_

#include "Status.hpp"
#include "types.hpp"
#include "is_in_variant_v.hpp"
#include"separators.hpp"

#include <parseop/parseop.hpp>
#include "fs/Path.hpp"

#include <string>
#include <optional>
#include <stdexcept>
#include <variant>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <memory>
#include <variant>


namespace jsonio {

    class InJson {
        
        public:
            InJson(void);
            ~InJson();

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
       
        private:
            class _InJsonImpl;
            std::unique_ptr<_InJsonImpl> _inJsonImpl;
    };

} // namespace jsonio


#endif // LIMINAL_LIB_jsonio_INJSON_HPP_