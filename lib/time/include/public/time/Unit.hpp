/**
 * @file units.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_LIB_TIME_INCLUDE_PUBLIC_TIME_UNITS_HPP_
#define LIMINAL_LIB_TIME_INCLUDE_PUBLIC_TIME_UNITS_HPP_

namespace time_ {

    // Forward declarations :
    //*****************
    using Stamp_t = long long int;
    //*****************

    enum class Unit {
        NANO_SECOND,
        MICRO_SECOND,
        MILLI_SECOND,
        SECOND,
        MINUTE,
        HOUR,
        DAY,
        MONTH_DAY,
        WEEK,
        MONTH,
        YEAR
    };

    constexpr Unit DEFAULT_TIME_UNIT        = Unit::SECOND;
    constexpr Stamp_t DEFAULT_YEAR          = 1970;
    constexpr Stamp_t DEFAULT_MONTH         = 1;
    constexpr Stamp_t DEFAULT_MONTH_DAY     = 1;
    constexpr Stamp_t DEFAULT_HOUR          = 0;
    constexpr Stamp_t DEFAULT_MINUTE        = 0;
    constexpr Stamp_t DEFAULT_SECOND        = 0;
    constexpr Stamp_t DEFAULT_MILLI_SECOND  = 0;
    constexpr Stamp_t DEFAULT_MICRO_SECOND  = 0;
    constexpr Stamp_t DEFAULT_NANO_SECOND   = 0;

} // namespace time_



#endif // LIMINAL_LIB_TIME_INCLUDE_PUBLIC_TIME_UNITS_HPP_