/**
 * @file time.test.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-20
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_TESTS_TIME_TEST_HPP_
#define LIMINAL_TESTS_TIME_TEST_HPP_

#include <time/Date.hpp>
#include <time/Stamp_t.hpp>
#include <time/Unit.hpp>

#include <vector>

namespace time_test {

        /**
         * @detalis This function is for test purposes only
         * It creates all kind of Date instances from the given Stamp and Unit
         * It also test the time_::Date::extract method even though it is not its purpose and that method
         * should be testes by itself
         * 
         * @return std::vector<time_::Date> 
         */
        std::vector<time_::Date> createInstances(const time_::Stamp_t &stamp, const time_::Unit &unit) {
            std::vector<time_::Date> res{};

            time_::Date stampInstance{stamp, unit};
            res.push_back(stampInstance);
            // res.push_back(
            //     time_::Date{
            //         stampInstance.extract(time_::Unit::YEAR),
            //         stampInstance.extract(time_::Unit::MONTH),
            //         stampInstance.extract(time_::Unit::MONTH_DAY),
            //         stampInstance.extract(time_::Unit::HOUR),
            //         stampInstance.extract(time_::Unit::MINUTE),
            //         stampInstance.extract(time_::Unit::SECOND),
            //         stampInstance.extract(time_::Unit::MILLI_SECOND),
            //         stampInstance.extract(time_::Unit::MICRO_SECOND),
            //         stampInstance.extract(time_::Unit::NANO_SECOND)
            //     }
            // );
            return res;
        }

} // namespace time_test

#endif // LIMINAL_TESTS_TIME_TEST_HPP_

