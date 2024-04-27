/**
 * @file convert.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-16
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "Stamp_t.hpp"

#include <cmath>
#include <sstream>
#include <iomanip>

#include <iostream>

namespace time_ {

    long double convert(const Stamp_t &stamp, const Unit &inputUnit, const Unit &outputUnit) {
        // FIXME with new unis + 
        /**
         * use this ? :
         * Human-readable time 	Seconds
1 hour	3600 seconds
1 day	86400 seconds
1 week	604800 seconds
1 month (30.44 days) 	2629743 seconds
1 year (365.24 days) 	 31556926 seconds
from : https://www.epochconverter.com/
         * 
         */
        if (inputUnit == outputUnit) return static_cast<long double>(stamp); // avoid lossing precision if possible
        constexpr double factors[] = {
            1e-9, // NANO_SECOND
            1e-6, // MICRO_SECOND
            1e-3, // MILLIS_ECOND
            1, // SECOND
            60, // MINUTE
            60*60, // HOUR
            60*60*24, // DAY,
            60*60*24, // MONTH_DAY,
            60*60*24*7, // WEEK
            60*60*24*30, // MONTH
            3600*24*365 // YEAR
        };
        if (inputUnit < Unit::SECOND && outputUnit < Unit::SECOND && outputUnit < inputUnit) { // If both Unit are sub second, handle precision lost with ss
            std::stringstream ss;
            ss << stamp << std::string((static_cast<int>(inputUnit) - static_cast<int>(outputUnit)) * 3, '0');
            return std::stold(ss.str());
        }
        long double seconds = static_cast<long double>( (stamp) * factors[static_cast<int>(inputUnit)] );
        return static_cast<long double>( std::round(seconds / factors[static_cast<int>(outputUnit)]) );
    };

} // namespace time_
