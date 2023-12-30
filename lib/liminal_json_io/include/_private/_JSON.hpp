/**
 * @file _JSON.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSON_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSON_HPP_

#include "Status.hpp"
#include "types.hpp"

#include "string.hpp"

#include <string>
#include <optional>
#include <stdexcept>

namespace liminal_json_io {
    namespace _private {
        
        class _JSON {
            public:
                // _Json(void) = default;
                Status parse(const std::string &path);

                

            protected:
                std::optional<types::JsonValue>  _rootValue;

            private:
                types::JsonValue __getObjectValue(const types::JsonValue &objectAsJsonValue, const std::string &key) const;
                types::JsonValue __getArrayValue(const types::JsonValue &arrayAsJsonValue, const std::string &indexAsString) const;
        };

    } // namespace _private
} // namespace liminal_json_io



#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSON_HPP_