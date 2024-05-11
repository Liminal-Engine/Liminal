/**
 * @file Date.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-15
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "Date.hpp"

#include <parseop/parseop.hpp>

#include <chrono>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <stdlib.h>


#include <iostream>


#define DATE_BUFFER_SIZE 2048

namespace time_ {

    class Date::_DateImpl {

        private:
            Stamp_t _stamp; // _stamp is ALWAYS in nanoseconds

            tm *__getTm(void) const {
                std::time_t seconds = static_cast<std::time_t>(convert(this->_stamp, Unit::NANO_SECOND, Unit::SECOND));
                return std::gmtime(&seconds);
            }

        public:

            _DateImpl(
                const Stamp_t &year,
                const Stamp_t &month,
                const Stamp_t &monthDay,
                const Stamp_t &hour,
                const Stamp_t &minute,
                const Stamp_t &second,
                const Stamp_t &milliSecond,
                const Stamp_t &microSecond,
                const Stamp_t &nanoSecond
            ) :
            _stamp{
                [&]() -> Stamp_t {
                    char *oldTZ = getenv("TZ");
                    setenv("TZ", "GMT", 1);

                    std::tm timeInfo{};
                    timeInfo.tm_year = year - 1900;
                    timeInfo.tm_mon = month - 1;
                    timeInfo.tm_mday = monthDay;
                    timeInfo.tm_hour = hour;
                    timeInfo.tm_min = minute;
                    timeInfo.tm_sec = second;
                    timeInfo.tm_isdst = -1;

                    Stamp_t res = convert(static_cast<Stamp_t>(std::mktime(&timeInfo)), Unit::SECOND, Unit::NANO_SECOND);
                    res += static_cast<Stamp_t>(convert(milliSecond, Unit::MILLI_SECOND, Unit::NANO_SECOND));
                    res += static_cast<Stamp_t>(convert(microSecond, Unit::MICRO_SECOND, Unit::NANO_SECOND));

                    if (oldTZ) setenv("TZ", oldTZ, 1);
                    else unsetenv("TZ");

                    return res + nanoSecond;
                }()
            }
            {}

            _DateImpl(const time_t &stamp, const Unit &unit):
            _DateImpl(static_cast<Stamp_t>(stamp), unit)
            // _stamp(static_cast<Stamp_t>( convert(static_cast<time_t>(stamp), unit, Unit::NANO_SECOND) + convert(static_cast<time_t>(1), Unit::MONTH, Unit::NANO_SECOND) + convert(static_cast<time_t>(1), Unit::MONTH_DAY, Unit::NANO_SECOND) ))
            {}

            _DateImpl(const Stamp_t &stamp, const Unit &unit):
            _DateImpl(
                (unit == Unit::YEAR ? DEFAULT_YEAR + stamp : DEFAULT_YEAR),
                unit == Unit::MONTH ? DEFAULT_MONTH_DAY + stamp : DEFAULT_MONTH,
                unit == Unit::DAY || unit == Unit::MONTH_DAY ? DEFAULT_MONTH_DAY + stamp : DEFAULT_MONTH_DAY,
                unit == Unit::HOUR ? stamp : DEFAULT_HOUR,
                unit == Unit::MINUTE ? stamp : DEFAULT_MINUTE,
                unit == Unit::SECOND ? stamp : DEFAULT_SECOND,
                unit == Unit::MILLI_SECOND ? stamp : DEFAULT_MILLI_SECOND,
                unit == Unit::MICRO_SECOND ? stamp : DEFAULT_MICRO_SECOND,
                unit == Unit::NANO_SECOND ? stamp : DEFAULT_NANO_SECOND
            )
            // _stamp{
            //     [&]() -> Stamp_t {
            //         char *oldTZ = getenv("TZ");
            //         setenv("TZ", "GMT", 1);

            //         std::tm timeInfo{};
            //         timeInfo.tm_year = (unit == Unit::YEAR ? stamp : 0) + 70;
            //         timeInfo.tm_mon = unit == Unit::MONTH ? stamp : 0;
            //         timeInfo.tm_mday = (unit == Unit::MONTH_DAY || unit == Unit::DAY ? stamp : 0) + 1;
            //         timeInfo.tm_hour = unit == Unit::HOUR ? stamp : 0;
            //         timeInfo.tm_min = unit == Unit::MINUTE ? stamp : 0;
            //         timeInfo.tm_sec = unit == Unit::SECOND ? stamp : 0;
            //         timeInfo.tm_isdst = -1;

            //         Stamp_t res = convert(static_cast<Stamp_t>(std::mktime(&timeInfo)), Unit::SECOND, Unit::NANO_SECOND);

            //         if (oldTZ) setenv("TZ", oldTZ, 1);
            //         else unsetenv("TZ");
            //         return res;
            //     }()
            // }
            {}

            _DateImpl(const Date &date):
            _stamp{date._impl->_stamp}
            {}

            ~_DateImpl() = default;

            bool operator==(const _DateImpl &other) const noexcept {
                return this->_stamp == other._stamp;
            }

            Stamp_t getStamp(const Unit &unit) const { return static_cast<Stamp_t>(convert(this->_stamp, Unit::NANO_SECOND, unit)); }

            Stamp_t extract(const Unit &unit) const {
                std::chrono::nanoseconds chronoStampNs(this->_stamp);
                std::chrono::seconds chronoStampS = std::chrono::duration_cast<std::chrono::seconds>(chronoStampNs);
                std::tm *timeInfo = this->__getTm();
                std::chrono::nanoseconds remainingNs = chronoStampNs - std::chrono::duration_cast<std::chrono::nanoseconds>(chronoStampS);
                std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(remainingNs);
                std::chrono::microseconds us = std::chrono::duration_cast<std::chrono::microseconds>(remainingNs - ms);
                std::chrono::nanoseconds ns = remainingNs - ms - us;

                switch (unit) {
                    case Unit::YEAR:
                        return static_cast<Stamp_t>(timeInfo->tm_year + 1900);
                    case Unit::MONTH:
                        return static_cast<Stamp_t>(timeInfo->tm_mon + 1);
                    case Unit::WEEK:
                        return static_cast<Stamp_t>(std::chrono::duration_cast<std::chrono::weeks>(chronoStampNs).count());
                    case Unit::DAY:
                        return static_cast<Stamp_t>(std::chrono::duration_cast<std::chrono::days>(chronoStampNs).count());
                    case Unit::MONTH_DAY:
                        return static_cast<Stamp_t>(timeInfo->tm_mday);
                    case Unit::HOUR:
                        return static_cast<Stamp_t>(timeInfo->tm_hour);
                    case Unit::MINUTE:
                        return static_cast<Stamp_t>(timeInfo->tm_min);
                    case Unit::SECOND:
                        return static_cast<Stamp_t>(timeInfo->tm_sec);
                    case Unit::MILLI_SECOND:
                        return static_cast<Stamp_t>(ms.count());
                    case Unit::MICRO_SECOND:
                        return static_cast<Stamp_t>(us.count());
                    case Unit::NANO_SECOND:
                        return static_cast<Stamp_t>(ns.count());
                }
                return 0;
            }

            std::string toStr(const std::string &format) const {
                std::string strBuffer = format;
                auto _subSecondToStr = [this](const Unit &unit) -> std::string { // Must always be a sub second unit
                    if (unit >= Unit::SECOND) return "#ERROR";
                    std::ostringstream ss;
                    ss << std::setw(3) << std::setfill('0') << this->extract(unit);
                    return ss.str();
                };

                std::vector<char> vecBuffer(2048);
                strftime(vecBuffer.data(), vecBuffer.size(), strBuffer.c_str(), this->__getTm());
                strBuffer = std::string(vecBuffer.data());
                strBuffer = parseop::replace(strBuffer, "%{ms}", _subSecondToStr(Unit::MILLI_SECOND));
                strBuffer = parseop::replace(strBuffer, "%{us}", _subSecondToStr(Unit::MICRO_SECOND));
                strBuffer = parseop::replace(strBuffer, "%{ns}", _subSecondToStr(Unit::NANO_SECOND));
                return strBuffer;
            }
    };

    Date::Date(const time_t &stamp, const Unit &unit):
    _impl(std::make_unique<Date::_DateImpl>(stamp, unit))
    {}

    Date::Date(const Stamp_t &stamp, const Unit &unit):
    _impl{std::make_unique<Date::_DateImpl>(stamp, unit)}
    {}

    Date::Date(
        const Stamp_t &year,
        const Stamp_t &month,
        const Stamp_t &monthDay,
        const Stamp_t &hour,
        const Stamp_t &minute,
        const Stamp_t &second,
        const Stamp_t &milliSecond,
        const Stamp_t &microSecond,
        const Stamp_t &nanoSecond
    ) :
    _impl{std::make_unique<Date::_DateImpl>(year, month, monthDay, hour, minute, second, milliSecond, microSecond, nanoSecond)}
    {}

    Date::Date(const Date &other):
    _impl{std::make_unique<Date::_DateImpl>(other)}
    {}

    Date::~Date() = default;

    bool Date::operator==(const Date &other) const noexcept { return this->_impl->operator==(*other._impl); }

    Stamp_t Date::getStamp(const Unit &unit) const { return this->_impl->getStamp(unit); }
  
    Stamp_t Date::extract(const Unit &unit) const { return this->_impl->extract(unit); }

    std::string Date::toStr(const std::string &format) const { return this->_impl->toStr(format); }

    Date Date::now(void) {
        return Date{ 
            static_cast<Stamp_t>(
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    std::chrono::high_resolution_clock::now().time_since_epoch()
                ).count()
            ),
            Unit::NANO_SECOND
        };
    }    
    
} // namespace time_

