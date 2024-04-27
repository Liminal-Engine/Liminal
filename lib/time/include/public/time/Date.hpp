/**
 * @file Date.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-14
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_LIB_TIME_INCLUDE_PUBLIC_TIME_DATE_HPP_
#define LIMINAL_LIB_TIME_INCLUDE_PUBLIC_TIME_DATE_HPP_

#include "Unit.hpp"
#include "Stamp_t.hpp"

#include <cstdint>
#include <string>
#include <climits>
#include <variant>
#include <memory>

namespace time_ {

    class Date {
        public:
            Date(const Stamp_t &stamp, const Unit &unit = DEFAULT_UNIT);
            /**
             * @brief Construct a new Date object
             * 
             * @warning This constructor will not check whether 0 < month <= 12 or 0 < monthDay <= 31. You are responsible of this
             * 
             * @param year 
             * @param month 
             * @param monthDay 
             * @param hour 
             * @param minute 
             * @param second 
             * @param milliSecond 
             * @param microSecond 
             * @param nanoSecond 
             */
            Date(
                const Stamp_t &year = 0,
                const Stamp_t &month = 0,
                const Stamp_t &monthDay = 0,
                const Stamp_t &hour = 0,
                const Stamp_t &minute = 0,
                const Stamp_t &second = 0,
                const Stamp_t &milliSecond = 0,
                const Stamp_t &microSecond = 0,
                const Stamp_t &nanoSecond = 0
            ); // equivalent to Date(void)
            Date(const Date &other);
            ~Date();
            Stamp_t getStamp(const Unit &unit = DEFAULT_UNIT) const;
            Stamp_t extract(const Unit &unit) const;

            /**
             * @brief 
             * 
             * @param format Same as format used bu C standard strftime. In addition :
             * %{ms} for millisecond
             * %{us} for microsecond
             * %{ns} for nanosecond
             * @return std::string 
             */
            std::string toStr(const std::string &format = "%Y-%m-%d %H:%M:%S") const;
            /**
             * TODO s :
             * 
             * test and limit overflows
             * static get boundaries (tuple) : return the max and min possible dates on the current system
             * 
             * // Date operator=(const Date &other);
             * // operator +, ==, *, - >, <
             * 
             * // timeZoneConvert(zone)
             */
            

            static Date now(void);
            
        private:
            class _DateImpl; // TODO : make this a macro ?
            std::unique_ptr<_DateImpl> _impl;
    };
} // namespace time_


#endif // LIMINAL_LIB_TIME_INCLUDE_PUBLIC_TIME_DATE_HPP_