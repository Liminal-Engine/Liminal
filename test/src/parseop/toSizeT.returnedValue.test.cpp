/**
 * @file toSizeT.returnedValue.test.cpp
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

        using ParseOPStringToSizeTParam = std::tuple<
            std::string, // input str
            long double, // accepted error
            size_t // expected result
        >;
        class ParseOPStringToSizeTFunc : public ::testing::TestWithParam<ParseOPStringToSizeTParam> {

        };

        TEST_P(ParseOPStringToSizeTFunc, ReturnsExpectedValue) {
            EXPECT_NEAR(::parseop::toSize_t(std::get<0>(GetParam())), std::get<2>(GetParam()), std::get<1>(GetParam()));
        }

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousParams,
            ParseOPStringToSizeTFunc,
            ::testing::Values(
                std::make_tuple("0", 0, 0),
                std::make_tuple("00000000000000000000", 0, 0),
                std::make_tuple("0000000000000000000000000", 0, 0),
                std::make_tuple("00000000000000000000000001", 0, 1),
                std::make_tuple("123456789", 0, 123456789), 
                std::make_tuple("-123456789", 0, -123456789), // FIXME : shoulToSize_t return negative numbers ?
                std::make_tuple("9223372036854775807", 0, 9223372036854775807),
                std::make_tuple("-9223372036854775808", 0, -9223372036854775807 - 1)
            )
        );
        

    } // namespace parseop
} // namespace test
