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

    constexpr Unit DEFAULT_UNIT = Unit::SECOND;

} // namespace time_



#endif // LIMINAL_LIB_TIME_INCLUDE_PUBLIC_TIME_UNITS_HPP_