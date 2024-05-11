/**
 * @file getNOccurences.returnedValue.test.cpp
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

        using ParseOPStringGetNOccurencesParam = std::tuple<
            std::string, // input string
            std::variant<char, std::string>, //occurences
            std::size_t // expected result
        >;
        class ParseOPStringGetNOccurencesFunc : public ::testing::TestWithParam<ParseOPStringGetNOccurencesParam> {

        };

        TEST_P(ParseOPStringGetNOccurencesFunc, ReturnsExpectedValue) {
            auto param = GetParam();
            auto result = std::visit([&](auto&& arg) {
                return ::parseop::getNOccurences(std::get<0>(param), arg);
            }, std::get<1>(param));
            EXPECT_EQ(result, std::get<2>(param));
        }

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousParams,
            ParseOPStringGetNOccurencesFunc,
            ::testing::Values(
                std::make_tuple("0000", '0', 4),
                std::make_tuple("0000", "0", 4),
                std::make_tuple("0000", "0000", 1),
                std::make_tuple("0000", "00", 2),
                std::make_tuple("00a00", "00", 2),
                std::make_tuple("0000", '1', 0),
                std::make_tuple("0000", "1", 0),
                std::make_tuple("0000", "0001", 0),
                std::make_tuple("0000", "01", 0),
                std::make_tuple("00a00", "01", 0),
                std::make_tuple("Hello, world!", 'o', 2),
                std::make_tuple("Hello, world!", "o", 2),
                std::make_tuple("Hello, world!", "world", 1),
                std::make_tuple("Hello, world!", "l", 3),
                std::make_tuple("Hello, world!", "Hello, world!", 1),
                std::make_tuple("Hello, world!", " ", 1),
                std::make_tuple("Hello, world!", ",", 1),
                std::make_tuple("Hello, world!", 'x', 0),
                std::make_tuple("Hello, world!", "x", 0),
                std::make_tuple("Hello, world!", "Hello, world! Hello, world!", 0),
                std::make_tuple("Hello, world!", "", 0),
                std::make_tuple("Hello, world!", "world, Hello", 0),
                std::make_tuple("Hello, world!", "  ", 0),
                std::make_tuple("Hello, world!", ",,", 0),
                std::make_tuple("", "", 1),
                std::make_tuple("", 'a', 0),
                std::make_tuple("", "a", 0),
                std::make_tuple("a", "", 0),
                std::make_tuple("abc", "", 0),
                std::make_tuple("a", "a", 1),
                std::make_tuple("abc", "abc", 1),
                std::make_tuple("aaa", "a", 3),
                std::make_tuple("aaa", "aa", 1),
                std::make_tuple("abcabc", "abc", 2),
                std::make_tuple("abcabc", "", 0),
                std::make_tuple("ababab", "ab", 3),
                std::make_tuple("aaa", "aa", 1),
                std::make_tuple("aba", "a", 2),
                std::make_tuple("aba", "", 0)
            )
        );

    } // namespace parseop
} // namespace test
