/**
 * @file isBool.returnedValue.test.cpp
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

        using IsBoolParam = std::tuple<
            std::string, // input string
            bool, // include_nb,
            bool // expected result
        >;
        class ParseOPStringIsBoolFunc : public ::testing::TestWithParam<IsBoolParam>{

        };

        TEST_P(ParseOPStringIsBoolFunc, ReturnsGivenValue) {
            EXPECT_EQ(::parseop::isBool(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
        }

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousValues,
            ParseOPStringIsBoolFunc,
            testing::Values(
                std::make_tuple("false", false, true),
                std::make_tuple("true", false, true),
                std::make_tuple("0", true, true),
                std::make_tuple("1", true, true),
                std::make_tuple("2", true, true),
                std::make_tuple("12", true, true),
                std::make_tuple("84848484847787878", true, true),

                std::make_tuple("/////false", false, false),
                std::make_tuple("/true////", false, false),
                std::make_tuple("0.125", true, false),
                std::make_tuple("45.47", true, false),
                std::make_tuple("", false, false),
                std::make_tuple("", true, false),

                std::make_tuple("0", false, false),
                std::make_tuple("-1", false, false),
                std::make_tuple("-8484651651561561", false, false),
                std::make_tuple("-0.284841", false, false),
                std::make_tuple("0.284841", false, false),
                std::make_tuple("0.284841", false, false),
                std::make_tuple("0.45454284841", false, false),
                std::make_tuple("1008787.45454284841", false, false)

            )
        );

    } // namespace parseop
} // namespace test
