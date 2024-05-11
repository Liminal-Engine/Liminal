/**
 * @file Helper.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "test/time/Date/Helper.hpp"

namespace test {
    namespace time_ {
        namespace Date {

            std::vector<::time_::Date> Helper::create(
                const ::time_::Stamp_t &stamp,
                const ::time_::Unit &unit
            ) {
                std::vector<::time_::Date> res{};

                res.push_back(::time_::Date(stamp, unit));
                res.push_back(::time_::Date(static_cast<time_t>(stamp), unit));
                ::time_::Date fromCpyConstructor(res.at(0));
                res.push_back(fromCpyConstructor);
                res.push_back(::time_::Date(
                    res.at(0).extract(::time_::Unit::YEAR),
                    res.at(0).extract(::time_::Unit::MONTH),
                    res.at(0).extract(::time_::Unit::MONTH_DAY),
                    res.at(0).extract(::time_::Unit::HOUR),
                    res.at(0).extract(::time_::Unit::MINUTE),
                    res.at(0).extract(::time_::Unit::SECOND),
                    res.at(0).extract(::time_::Unit::MILLI_SECOND),
                    res.at(0).extract(::time_::Unit::MICRO_SECOND),
                    res.at(0).extract(::time_::Unit::NANO_SECOND)
                ));
                return res;
            }

        } // namespace Date
    } // namespace time_
} // namespace test
