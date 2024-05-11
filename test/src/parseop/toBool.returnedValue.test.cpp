/**
 * @file toBool.returnedValue.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <parseop/parseop.hpp>

#include <variant>
#include <tuple>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace test {
    namespace parseop {

        using ParseOPStringToBoolParam = std::tuple<
            std::string, // input str
            bool, // include_nb
            bool // expected result
        >;
        class ParseOPStringToBoolFunc : public ::testing::TestWithParam<ParseOPStringToBoolParam>{

        };

        TEST_P(ParseOPStringToBoolFunc, ReturnsGivenValue) {
            std::string input_str = std::get<0>(GetParam());
            bool include_nb = std::get<1>(GetParam());
            bool expected_res = std::get<2>(GetParam());

            EXPECT_EQ(::parseop::toBool(input_str, include_nb), expected_res);
        };

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousValues,
            ParseOPStringToBoolFunc,
            ::testing::Values(
                std::make_tuple("true", false, true),
                std::make_tuple("111111", true, true),
                std::make_tuple("1", true, true),
                std::make_tuple("2", true, true),
                std::make_tuple("12", true, true),
                std::make_tuple("84848484847787878", true, true),

                std::make_tuple("false", false, false),
                std::make_tuple("0", true, false),

                std::make_tuple("thisIsOfficialyNotABoolean", false, false),
                std::make_tuple("false////", false, false),
                std::make_tuple("////true////", false, false)
            )
        );

    } // namespace parseop
} // namespace test
