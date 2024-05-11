/**
 * @file lastIndexOf.returnedValue.test.cpp
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
       
        using ParseOPStringLastIndexOfParam = std::tuple<
            std::string, // input string
            char, // wanted char
            std::size_t // expected result
        >;
        class ParseOPStringLastIndexOfFunc : public ::testing::TestWithParam<ParseOPStringLastIndexOfParam> {

        };

        TEST_P(ParseOPStringLastIndexOfFunc, WhenGivenVariousValues) {
            EXPECT_EQ(::parseop::lastIndexOf(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
        };

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousParams,
            ParseOPStringLastIndexOfFunc,
            ::testing::Values(
                std::make_tuple("Hello, world!", 'o', 8),
                std::make_tuple("Hello, world!", 'l', 10),
                std::make_tuple("Hello, world!", 'd', 11),
                std::make_tuple("Hello, world!", 'x', std::string::npos),
                std::make_tuple("", 'a', std::string::npos),
                std::make_tuple("abc", 'a', 0),
                std::make_tuple("abc", 'b', 1),
                std::make_tuple("abc", 'c', 2),
                std::make_tuple("abc", 'd', std::string::npos),
                std::make_tuple("abc", '\0', std::string::npos),
                std::make_tuple("aaa", 'a', std::string{"aaa"}.size() - 1)
            )
        );

    } // namespace parseop
} // namespace test
