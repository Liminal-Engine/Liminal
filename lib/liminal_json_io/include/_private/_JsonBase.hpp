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

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSONBASE_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSONBASE_

#include "Status.hpp"
#include "_private/_JsonValue.hpp"

#include "liminal_string_extras/string.hpp"

#include <string>
#include <optional>
#include <stdexcept>

namespace liminal_json_io {
    namespace _private {
        
        class _JsonBase {
            public:
                // _Json(void) = default;
                Status parse(const std::string &path);

            protected:
                std::optional<_JsonValue>  _rootValue;

        };

    } // namespace _private
} // namespace liminal_json_io



#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSONBASE_