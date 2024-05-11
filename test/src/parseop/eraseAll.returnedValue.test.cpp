/**
 * @file eraseAll.returnedValue.test.cpp
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

        using ParseOPStringEraseAllParam = std::tuple<
            std::string, // input string
            std::variant<std::vector<std::string>, std::string>, // substrings to erase
            std::string // expected result
        >;
        class ParseOPStringEraseAllFunc : public ::testing::TestWithParam<ParseOPStringEraseAllParam> {

        };

        TEST_P(ParseOPStringEraseAllFunc, ReturnsGivenValue) {
            auto param = GetParam();
            auto result = std::visit([&](auto&& arg) {
                return ::parseop::eraseAll(std::get<0>(param), arg);
            }, std::get<1>(param));
            EXPECT_EQ(result, std::get<2>(param));
        };

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousParams,
            ParseOPStringEraseAllFunc,
            ::testing::Values(
                std::make_tuple("abc", "c", "ab"),
                std::make_tuple("Hello, world!", "o", "Hell, wrld!"),
                std::make_tuple("Hello, world!", " ", "Hello,world!"),
                std::make_tuple("Hello, world!", "world", "Hello, !"),
                std::make_tuple("Hello, world!", "Hello", ", world!"),
                std::make_tuple("Hello, world!", std::vector<std::string>{"o", " ", "!"}, "Hell,wrld"),
                std::make_tuple("Hello, world!", std::vector<std::string>{"Hello", "world"}, ", !"),
                std::make_tuple("", "", ""),
                std::make_tuple("", "a", ""),
                std::make_tuple("a", "", "a"),
                std::make_tuple("abc", "", "abc"),
                std::make_tuple("a", "a", ""),
                std::make_tuple("abc", "abc", ""),
                std::make_tuple("aaa", "a", ""),
                std::make_tuple("aaabaaa", std::vector<std::string>{"", "b"}, "aaaaaa"),
                std::make_tuple("aaabaaa", std::vector<std::string>{""}, "aaabaaa"),
                std::make_tuple("", std::vector<std::string>{"", "", "", ""}, ""),
                std::make_tuple("abcabc", std::vector<std::string>{"a", "b"}, "cc"),
                std::make_tuple("abc", "d", "abc"),
                std::make_tuple("abc", std::vector<std::string>{"d", "e"}, "abc"),
                std::make_tuple("ababab", "aba", "bab"),
                std::make_tuple("abcabc", "abc", ""),
                std::make_tuple("abcabcabc", std::vector<std::string>{"abc"}, ""),
                std::make_tuple("abcabcabc", std::vector<std::string>{"a", "b", "c"}, ""),
                std::make_tuple("abcabcabc", std::vector<std::string>{"ab", "bc"}, "ccc"),
                std::make_tuple("abcabcabc", std::vector<std::string>{"de", "fg"}, "abcabcabc"),
                std::make_tuple("abcabcabc", std::vector<std::string>{"ab", "de"}, "ccc"),
                std::make_tuple("abcabcabc", std::vector<std::string>{"abc", "bc"}, ""),
                std::make_tuple("abcabcabc", std::vector<std::string>{"abc", "a"}, "")
            )
        );

    } // namespace parseop
} // namespace test
