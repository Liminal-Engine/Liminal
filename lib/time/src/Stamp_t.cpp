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

    Stamp_t convert(const Stamp_t &stamp, const Unit &inputUnit, const Unit &outputUnit) {
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
        if (inputUnit == outputUnit) return static_cast<Stamp_t>(stamp); // avoid lossing precision if possible
        constexpr Stamp_t factors[] = {
            1LL, // NANO_SECOND
            1000LL, // MICRO_SECOND
            1000000LL, // MILLI_SECOND
            1000000000LL, // SECOND
            60LL * 1000000000LL, // MINUTE
            60LL * 60LL * 1000000000LL, // HOUR
            24LL * 60LL * 60LL * 1000000000LL, // DAY
            24LL * 60LL * 60LL * 1000000000LL, // MONTH_DAY
            7LL * 24LL * 60LL * 60LL * 1000000000LL, // WEEK
            30LL * 24LL * 60LL * 60LL * 1000000000LL, // MONTH
            365LL * 24LL * 60LL * 60LL * 1000000000LL // YEAR
        };
        Stamp_t inputFactor = factors[static_cast<int>(inputUnit)];
        Stamp_t outputFactor = factors[static_cast<int>(outputUnit)];
        Stamp_t result = static_cast<Stamp_t>(stamp) * inputFactor / outputFactor;
        return result;

        Stamp_t seconds = static_cast<Stamp_t>( (stamp) * factors[static_cast<int>(inputUnit)] );
        return static_cast<Stamp_t>( std::round(seconds / factors[static_cast<int>(outputUnit)]) );
    };

} // namespace time_
