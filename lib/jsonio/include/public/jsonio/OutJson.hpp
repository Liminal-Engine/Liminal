/**
 * @file OutJson.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-07
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef _LIMINAL_LIB_JSONIO_OUTJSON_HPP_
#define _LIMINAL_LIB_JSONIO_OUTJSON_HPP_

#include "Status.hpp"
#include "is_in_variant_v.hpp"
#include "separators.hpp"
#include "types.hpp"

#include "fs/Path.hpp"

#include <memory>
#include <array>

namespace jsonio {
    class OutJson {
        public:
            OutJson(void);
            ~OutJson(void);

            Status parse(const fs::Path &path);

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
            class _OutJsonImpl;
            std::unique_ptr<_OutJsonImpl> _pImpl;

    };
    
} // namespace jsonio

#endif // _LIMINAL_LIB_JSONIO_OUTJSON_HPP_