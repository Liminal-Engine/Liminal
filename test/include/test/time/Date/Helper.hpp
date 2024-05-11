/**
 * @file Helper.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_TEST_TIME_DATE_HELPER_HPP_
#define LIMINAL_TEST_TIME_DATE_HELPER_HPP_

#include <time/Date.hpp>

#include <vector>

namespace test {
    namespace time_ {
        namespace Date {

            class Helper {

                public:

                static std::vector<::time_::Date> create(
                    const ::time_::Stamp_t &stamp,
                    const ::time_::Unit &unit = ::time_::DEFAULT_TIME_UNIT
                );
            };

        } // namespace Date
    } // namespace time_
} // namespace test

#endif // LIMINAL_TEST_TIME_DATE_HELPER_HPP_

