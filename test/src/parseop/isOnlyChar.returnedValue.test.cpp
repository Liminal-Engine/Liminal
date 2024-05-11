/**
 * @file isOnlyChar.returnedValue.test.cpp
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

        using ParseOPStringIsOnlyCharParam = std::tuple<
            std::string, // input str
            char, // 
            bool // expected result
        >;
        class ParseOPStringIsOnlyCharFunc : public ::testing::TestWithParam<ParseOPStringIsOnlyCharParam> {

        };

        TEST_P(ParseOPStringIsOnlyCharFunc, ReturnsGivenValue) {
            EXPECT_EQ(::parseop::isOnlyChar(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
        };

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousParams,
            ParseOPStringIsOnlyCharFunc,
            ::testing::Values(
                std::make_tuple("aaaaaaaaaaaaaaaaaaaaaaaaaaa", 'a', true),
                std::make_tuple("", 'a', false), // empty string is considered to be composed of any character
                std::make_tuple("a", 'a', true), // single character string is composed of that character
                std::make_tuple("aa", 'a', true), // string with multiple occurrences of the given character
                std::make_tuple("aaa", 'a', true), // string with multiple occurrences of the given character
                std::make_tuple("aaaaa", 'a', true), // string with multiple occurrences of the given character
                std::make_tuple("ab", 'a', false), // string with different character than the given one
                std::make_tuple("abc", 'a', false), // string with different character than the given one
                std::make_tuple("", 'a', false), // string with different character than the given one
                std::make_tuple("abcde", 'a', false), // string with different character than the given one
                std::make_tuple("abcde", 'e', false), // string with different character than the given one
                std::make_tuple("abcde", 'f', false), // string with different character than the given one
                std::make_tuple("12345", '1', false), // string with different character than the given one
                std::make_tuple("12345", '5', false), // string with different character than the given one
                std::make_tuple("12345", '6', false), // string with different character than the given one
                std::make_tuple(" ", ' ', true), // string with only whitespace character
                std::make_tuple("   ", ' ', true), // string with only whitespace characters
                std::make_tuple("\t", '\t', true), // string with only tab character
                std::make_tuple("\t\t\t", '\t', true), // string with only tab characters
                std::make_tuple("\n", '\n', true), // string with only newline character
                std::make_tuple("\n\n\n", '\n', true), // string with only newline characters
                std::make_tuple(" \t\n", ' ', false), // string with different character than the given one
                std::make_tuple(" \t\n", '\t', false), // string with different character than the given one
                std::make_tuple(" \t\n", '\n', false) // string with different character than the given one
            )
        );

    } // namespace parseop
} // namespace test
