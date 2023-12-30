/**
 * @file _JsonValueTypes.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSONVALUETYPES_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSONVALUETYPES_HPP_

namespace liminal_json_io {
    namespace _private {

        enum class _JsonValueTypes {
            _STRING,
            _INT,
            _FLOAT,
            _BOOL,
            _JSON_NULL,
            _ARRAY,
            _OBJECT
        };

    } // namespace _private
} // namespace liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSONVALUETYPES_HPP_