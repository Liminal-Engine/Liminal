/**
 * @file trimBegin.returnedValue.test.cpp
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

        using ParseOPStringTrimBeginParam = std::tuple<
            std::string, // input string
            std::variant<
                char,
                std::vector<char>,
                std::string,
                std::vector<std::string>
            >, // data to trim
            std::string // expected result
        >;
        class ParseOPStringTrimBeginFunc : public ::testing::TestWithParam<ParseOPStringTrimBeginParam> {

        };

        TEST_P(ParseOPStringTrimBeginFunc, ReturnsGivenValue) {
            auto param = GetParam();
            auto result = std::visit([&](auto&& arg) {
                return ::parseop::trimBegin(std::get<0>(param), arg);
            }, std::get<1>(param));
            EXPECT_EQ(result, std::get<2>(param));
        };

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousParams,
            ParseOPStringTrimBeginFunc,
            ::testing::Values(
                std::make_tuple("   leading spaces", ' ', "leading spaces"),
                std::make_tuple("\t\tleading tabs", '\t', "leading tabs"),
                std::make_tuple("\n\nleading newlines", '\n', "leading newlines"),
                std::make_tuple(" \t  mixed   leading whitespace\n  ", std::vector<char>{' ', '\n'}, "\t  mixed   leading whitespace\n  "),
                std::make_tuple("no leading whitespace", ' ', "no leading whitespace"),
                std::make_tuple("", ' ', ""),
                std::make_tuple("abcabcabc", 'a', "bcabcabc"),
                std::make_tuple("abcabcabc", std::vector<char>{'a', 'b'}, "cabcabc"),
                std::make_tuple("abcabcabc", std::string("ab"), "cabcabc"),
                std::make_tuple("abcabcabc", std::vector<std::string>{"ab", "bc"}, "cabcabc"),
                std::make_tuple("1234567890", std::vector<char>{'1', '2', '3'}, "4567890"),
                std::make_tuple("1234567890", std::string("123"), "4567890"),
                std::make_tuple("1234567890", std::vector<std::string>{"12", "34"}, "567890"),
                std::make_tuple("   leading spaces", std::vector<std::string>{"   "}, "leading spaces"),
                std::make_tuple("   leading spaces", std::string("   "), "leading spaces"),
                std::make_tuple("   leading spaces", std::vector<char>{' '}, "leading spaces"),
                std::make_tuple("   leading spaces", ' ', "leading spaces"),
                std::make_tuple("no leading whitespace", ' ', "no leading whitespace"),
                std::make_tuple("", ' ', ""),
                std::make_tuple("", std::vector<char>{' '}, ""),
                std::make_tuple("", std::string(" "), ""),
                std::make_tuple("", std::vector<std::string>{" "}, ""),
                std::make_tuple("aaa", std::vector<std::string>{"a"}, "")
            )
        );

    } // namespace parseop
} // namespace test
