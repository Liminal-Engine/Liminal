/**
 * @file is_in_variant_v.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef _LIMINAL_LIB_JSONIO_IS_IN_VARIANT_V_HPP_
#define _LIMINAL_LIB_JSONIO_IS_IN_VARIANT_V_HPP_

#include <variant>

namespace jsonio {

    template <typename T, typename Variant>
    struct is_in_variant;

    template <typename T, typename... Ts>
    struct is_in_variant<T, std::variant<Ts...>> : std::bool_constant<(std::is_same_v<T, Ts> || ...)> {};

    template <typename T, typename V>
    static inline constexpr bool is_in_variant_v = is_in_variant<T, V>::value;
    
} // namespace jsonio


#endif // _LIMINAL_LIB_JSONIO_IS_IN_VARIANT_V_HPP_