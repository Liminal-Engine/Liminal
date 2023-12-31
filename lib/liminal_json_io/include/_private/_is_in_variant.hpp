/**
 * @file _is_in_variant.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-31
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__IS_IN_VARIANT_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__IS_IN_VARIANT_HPP_

namespace liminal_json_io {
    namespace _private {

        template <typename T, typename Variant>
        struct _is_in_variant;

        template <typename T, typename... Ts>
        struct _is_in_variant<T, std::variant<Ts...>> : std::bool_constant<(std::is_same_v<T, Ts> || ...)> {};

        template <typename T, typename V>
        static inline constexpr bool _is_in_variant_v = _is_in_variant<T, V>::value;
        
    } // namespace _private 
    
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__IS_IN_VARIANT_HPP_