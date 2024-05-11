/**
 * @file toLongDouble.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-10
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <parseop/parseop.hpp>

#include "test/Helper.hpp"

#include <variant>
#include <tuple>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace test {
    namespace parseop {

        using ParseOPStringToLongDoubleParam = std::tuple<
            std::string, // input str
            long double // expected result
        >;
        class ParseOPStringToLongDoubleFunc : public ::testing::TestWithParam<ParseOPStringToLongDoubleParam> {

        };

        TEST_P(ParseOPStringToLongDoubleFunc, WhenGivenVariousValues) {
            EXPECT_NEAR(::parseop::toLongDouble(std::get<0>(GetParam())), std::get<1>(GetParam()), ::test::Helper::EXPECT_NEAR_ABSOLUTE_ERROR);
        }

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousParams,
            ParseOPStringToLongDoubleFunc,
            ::testing::Values(
                std::make_tuple("0", 0),
                std::make_tuple("00000000000000000000", 0),
                std::make_tuple("0000000000000000000000000", 0),
                std::make_tuple("00000000000000000000000001", 1),
                std::make_tuple("123456789", 123456789),
                std::make_tuple("-123456789", -123456789),
                std::make_tuple("9223372036854775807", 9223372036854775807),
                std::make_tuple("-9223372036854775808", -9223372036854775807 - 1),
                std::make_tuple("0.0", 0.0),
                std::make_tuple("3.14", 3.14),
                std::make_tuple("-1.23", -1.23),
                std::make_tuple("123456789.987654321", 123456789.987654321),
                std::make_tuple("-987654321.123456789", -987654321.123456789),
                std::make_tuple("1.23e4", 1.23e4L),
                std::make_tuple("-1.23e4", -1.23e4L),
                std::make_tuple("1.23e-4", 1.23e-4L),
                std::make_tuple("-1.23e-4", -1.23e-4L)
            )
        );

    } // namespace parseop
} // namespace test
