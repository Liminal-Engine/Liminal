// /**
//  * @file toStr.test.hpp
//  * @author DE VITA Matteo (matteo.devita7@gmail.com)
//  * @brief 
//  * @version 0.1
//  * @date 2024-04-20
//  * 
//  * @copyright Copyright (c) 2024
//  * 
// */

#include <time/Date.hpp>

#include "test/time/Date/Helper.hpp"

#include <tuple>
#include <optional>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


// FIXME : diviser dates en 3 parties :
/**
 * precision -> en ns mais limité à 2038,
 * infinie -> non limitée en maximum ou précision -> mais long à calculé (en utilisant chiffres infinies)
 * normal -> (trouver un meilleur nom ? ou pas donnée de nom) -> limitée à la seconde mais au dela de 2038
 * divisé "date" en 3 namespaces ?
 * et pouvoir construire les unes par rapport aux autres. par exemple : une high precision par rapport à une normale
 * aussi avoir pour chacune une méthode qui noux indique si elle à overflow ou non
 */
namespace test {
    namespace time_ {
        namespace Date {
            
            using TimeDateToStrParams = std::tuple<
                ::time_::Stamp_t, // stamp
                ::time_::Unit,
                std::optional<std::string>, // string format param
                std::string // expected result
            >;

            class TimeDateToStrMethod : public ::testing::TestWithParam<TimeDateToStrParams> {

                protected:
                    std::vector<::time_::Date> _instances;

                    TimeDateToStrMethod(void):
                    _instances{::test::time_::Date::Helper::create(std::get<0>(GetParam()), std::get<1>(GetParam()))}
                    {}

            };

            TEST_P(TimeDateToStrMethod, ReturnsGivenString) {
                if (std::get<2>(GetParam()).has_value())
                    for (const ::time_::Date &date : _instances) EXPECT_EQ(date.toStr(std::get<2>(GetParam()).value()), std::get<3>(GetParam()));
                else for (const ::time_::Date &date : _instances) EXPECT_EQ(date.toStr(), std::get<3>(GetParam()));
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenVariousValues,
                TimeDateToStrMethod,
                testing::Values(
                    std::make_tuple(1713643782, ::time_::Unit::SECOND, std::nullopt, "2024-04-20 20:09:42"),
                    std::make_tuple(1675929224, ::time_::Unit::SECOND, std::nullopt,"2023-02-09 07:53:44"),
                    std::make_tuple(1453826841, ::time_::Unit::SECOND, std::nullopt,"2016-01-26 16:47:21"),
                    std::make_tuple(1809926839000000000, ::time_::Unit::NANO_SECOND, "%Y-%m-%d %H:%M:%S.%{ms}.%{us}.%{ns}","2027-05-10 05:27:19.000.000.000"),
                    std::make_tuple(979353647, ::time_::Unit::SECOND, std::nullopt,"2001-01-13 02:40:47"),
                    std::make_tuple(967507955, ::time_::Unit::SECOND, std::nullopt,"2000-08-29 00:12:35"),
                    std::make_tuple(1497807187, ::time_::Unit::SECOND, std::nullopt,"2017-06-18 17:33:07"),
                    std::make_tuple(1438138569, ::time_::Unit::SECOND, std::nullopt,"2015-07-29 02:56:09"),
                    std::make_tuple(1546308438, ::time_::Unit::SECOND, std::nullopt,"2019-01-01 02:07:18"),
                    std::make_tuple(1810464541, ::time_::Unit::SECOND, std::nullopt,"2027-05-16 10:49:01"),
                    std::make_tuple(1414922587, ::time_::Unit::SECOND, std::nullopt,"2014-11-02 10:03:07"),
                    std::make_tuple(1414922587498, ::time_::Unit::MILLI_SECOND, "%Y-%m-%d %H:%M:%S.%{ms}","2014-11-02 10:03:07.498"),
                    std::make_tuple(1414922587, ::time_::Unit::SECOND, "%m%Y--%d %S%H%M","112014--02 071003"),
                    std::make_tuple(1810712568412365798, ::time_::Unit::NANO_SECOND, "%Y-%m-%d %H:%M:%S.%{ms}.%{us}.%{ns}","2027-05-19 07:42:48.412.365.798"),
                    std::make_tuple(1810712568412, ::time_::Unit::MILLI_SECOND, "%Y-%m-%d %H:%M:%S.%{ms}","2027-05-19 07:42:48.412"),
                    std::make_tuple(1810712568412365798, ::time_::Unit::NANO_SECOND, "%Y%{ms}%m-%d %H:%M:%S..%{us}.%{ns}","202741205-19 07:42:48..365.798"),
                    std::make_tuple(1810712568412365798, ::time_::Unit::NANO_SECOND, "%Y%{ms}%m%{us}%{ns}%d %H:%M:%S....////%{ns}","20274120536579819 07:42:48....////798"),
                    std::make_tuple(1810712568412365798, ::time_::Unit::NANO_SECOND, "%Y%{ms}%m%{us}%{ns}%d %H:%M:%S....//%%//%{ns}","20274120536579819 07:42:48....//%//798"),
                    std::make_tuple(1810712568412365798, ::time_::Unit::NANO_SECOND, "%Y%{ms}%m%{us}%{ns}%d %H:%M:%S....//%%//%%{ns}","20274120536579819 07:42:48....//%//798"),
                    std::make_tuple(1810712568412365798, ::time_::Unit::NANO_SECOND, "%Y%{ms}%m%{us}%%{ns}%d %H:%M:%S....//%%//","20274120536579819 07:42:48....//%//"),
                    std::make_tuple(1810712568412365798, ::time_::Unit::NANO_SECOND, "%Y%{ms}%m%{us}%%{ns}%d %H:%M:%S....//%%//%%{ns}/","20274120536579819 07:42:48....//%//798/"),
                    std::make_tuple(1810712568412365, ::time_::Unit::MICRO_SECOND, "%Y%{ms}%m%{us}%%{ns}%d %H:%M:%S....//%%//","20274120536500019 07:42:48....//%//"),
                    std::make_tuple(1810712568412, ::time_::Unit::MILLI_SECOND, "%Y%{ms}%m%{us}%%{ns}%d %H:%M:%S....//%%//","20274120500000019 07:42:48....//%//"),
                    std::make_tuple(8, ::time_::Unit::NANO_SECOND, "%{ns}", "008"),
                    std::make_tuple(8, ::time_::Unit::MICRO_SECOND, "%{ns}", "000"),
                    std::make_tuple(8, ::time_::Unit::MICRO_SECOND, "%{us}%{ns}", "008000"),
                    std::make_tuple(1, ::time_::Unit::YEAR, "%Y-%m-%d %{ms}.%{us}.%{ns}", "1971-01-01 000.000.000"),
                    std::make_tuple(74, ::time_::Unit::YEAR, "%Y-%m-%d %{ms}.%{us}.%{ns}", "2044-01-01 000.000.000"),
                    std::make_tuple(36, ::time_::Unit::MONTH, "%Y-%m-%d %{ms}.%{us}.%{ns}", "1973-01-01 000.000.000"),
                    std::make_tuple(11, ::time_::Unit::MONTH, "%Y-%m-%d %{ms}.%{us}.%{ns}", "1970-12-01 000.000.000")

                )
            );
        } // namespace Date
    } // namespace time_
} // namespace test

