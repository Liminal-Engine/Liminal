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

#include "Status.hpp"
#include "types.hpp"
#include "is_in_variant_v.hpp"

#include "liminal_string_extras/string.hpp"

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

namespace liminal_json_io {

    class InJson {
        
        public:
            InJson(void);
            ~InJson();

            // Re declaration of _JSON methods :
            Status parse(const std::string &path);

            // Own methods declaration :
            std::string getType(const std::string &jsonPath = "") const;

            template <typename T>
            requires is_in_variant_v<T, types::Any_t>
            std::optional<T> get(const std::string &jsonPath = "") const;
       

        private:
            class _InJsonImpl;
            std::unique_ptr<_InJsonImpl> _inJsonImpl;
    };

} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO_INJSON_HPP_