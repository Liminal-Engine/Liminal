/**
 * @file isPositiveInteger.returnedValue.test.cpp
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
        using isPositiveIntegerParam = std::tuple<
            std::string, // input str,
            bool // expected result
        >;
        class ParseOPStringIsPositiveIntegerFunc : public ::testing::TestWithParam<isPositiveIntegerParam>{

        };

        TEST_P(ParseOPStringIsPositiveIntegerFunc, ReturnsGivenValue) {
            EXPECT_EQ(::parseop::isPositiveInteger(std::get<0>(GetParam())), std::get<1>(GetParam()));
        }

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousValues,
            ParseOPStringIsPositiveIntegerFunc,
            ::testing::Values(
                std::make_tuple("1", true),
                std::make_tuple("10", true),
                std::make_tuple("12", true),
                std::make_tuple("2", true),
                std::make_tuple("22222222227777777777777714518748744145418187", true),
                std::make_tuple("0748744145418187", true),
                std::make_tuple("0", true), // yes, 0 is considered to be positive with this func
                std::make_tuple("000000000000000000000000000000000000000000000", true), // yes, 0 is considered to be positive with this func
                std::make_tuple("0000000000000000000000000000000000000000000001", true), // yes, 0 is considered to be positive with this func

                std::make_tuple("-1", false),
                std::make_tuple("-8484651651561561", false),
                std::make_tuple("-0.284841", false),
                std::make_tuple("0.284841", false),
                std::make_tuple("0.284841", false),
                std::make_tuple("0.45454284841", false),
                std::make_tuple("1008787.45454284841", false)

            )
        );
    } // namespace parseop
} // namespace test
