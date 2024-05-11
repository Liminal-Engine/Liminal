/**
 * @file trimEnd.returnedValue.test.cpp
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

        using ParseOPStringTrimEndParam = std::tuple<
            std::string, // input string
            std::variant<
                char,
                std::vector<char>,
                std::string,
                std::vector<std::string>
            >, // data to trim
            std::string // expected result
        >;
        class ParseOPStringTrimEndFunc : public ::testing::TestWithParam<ParseOPStringTrimEndParam> {

        };

        TEST_P(ParseOPStringTrimEndFunc, ReturnsGivenValue) {
            auto param = GetParam();
            auto result = std::visit([&](auto&& arg) {
                return ::parseop::trimEnd(std::get<0>(param), arg);
            }, std::get<1>(param));
            EXPECT_EQ(result, std::get<2>(param));
        };

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousParams,
            ParseOPStringTrimEndFunc,
            ::testing::Values(
                std::make_tuple("trailing spaces   ", ' ', "trailing spaces"),
                std::make_tuple("trailing tabs\t\t", '\t', "trailing tabs"),
                std::make_tuple("trailing newlines\n\n", '\n', "trailing newlines"),
                std::make_tuple("  mixed trailing whitespace \t  \n", std::vector<char>{' ', '\n'}, "  mixed trailing whitespace \t"),
                std::make_tuple("no trailing whitespace", ' ', "no trailing whitespace"),
                std::make_tuple("", ' ', ""),
                std::make_tuple("abcabcabc", 'c', "abcabcab"),
                std::make_tuple("abcabcabc", std::vector<char>{'b', 'c'}, "abcabca"),
                std::make_tuple("abcabcabc", std::string("bc"), "abcabca"),
                std::make_tuple("abcabcabc", std::vector<std::string>{"ab", "bc"}, "abcabca"),
                std::make_tuple("1234567890", std::vector<char>{'0', '9', '8'}, "1234567"),
                std::make_tuple("1234567890", std::string("890"), "1234567"),
                std::make_tuple("1234567890", std::vector<std::string>{"89", "90"}, "12345678"),
                std::make_tuple("trailing spaces   ", std::vector<std::string>{"   "}, "trailing spaces"),
                std::make_tuple("trailing spaces   ", std::string("   "), "trailing spaces"),
                std::make_tuple("trailing spaces   ", std::vector<char>{' '}, "trailing spaces"),
                std::make_tuple("trailing spaces   ", ' ', "trailing spaces"),
                std::make_tuple("no trailing whitespace", ' ', "no trailing whitespace"),
                std::make_tuple("", ' ', ""),
                std::make_tuple("", std::vector<char>{' '}, ""),
                std::make_tuple("", std::string(" "), ""),
                std::make_tuple("", std::vector<std::string>{" "}, ""),
                std::make_tuple("aaa", std::vector<std::string>{"a"}, "")
            )
        );

    } // namespace parseop
} // namespace test
