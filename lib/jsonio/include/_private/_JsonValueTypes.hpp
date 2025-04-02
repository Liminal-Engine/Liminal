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

#ifndef _LIMINAL_LIB_JSONIO__PRIVATE__JSONVALUETYPES_HPP_
#define _LIMINAL_LIB_JSONIO__PRIVATE__JSONVALUETYPES_HPP_

namespace jsonio {
    namespace _private {

        enum class _JsonValueTypes {
            _STRING,
            _INT,
            _FLOAT,
            _BOOL,
            _JSON_NULL,
            _ARRAY,
            _OBJECT,
            _UNKNOWN
        };

    } // namespace _private
} // namespace jsonio

#endif // _LIMINAL_LIB_JSONIO__PRIVATE__JSONVALUETYPES_HPP_