/**
 * @file includes.returnedValue.test.cpp
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

        using ParseOPStringincludesParam = std::tuple<
            std::string, // input str
            std::variant<char, std::vector<char>, std::string, std::vector<std::string>>, // content to find
            bool // expected result
        >;
        class ParseOPStringincludesFunc : public ::testing::TestWithParam<ParseOPStringincludesParam> {

        };

        TEST_P(ParseOPStringincludesFunc, ReturnsGivenValue) {
            auto param = GetParam();
            auto result = std::visit([&](auto&& arg) {
                return ::parseop::includes(std::get<0>(param), arg);
            }, std::get<1>(param));
            EXPECT_EQ(result, std::get<2>(param));
        };

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousValues,
            ParseOPStringincludesFunc,
            ::testing::Values(
                std::make_tuple("aaa", "a", true),
                std::make_tuple("aaa", 'a', true),
                std::make_tuple("", "", true), // empty string includes empty string
                std::make_tuple("", 'a', false), // empty string does not contain 'a'
                std::make_tuple("aaa", "aa", true), // "aaa" includes "aa"
                std::make_tuple("aaa", "aaa", true), // "aaa" includes "aaa"
                std::make_tuple("aaa", "aaaa", false), // "aaa" does not contain "aaaa"
                std::make_tuple("aaa", "aaaa", false), // "aaa" does not contain "aaaa"
                std::make_tuple("aaa", 'a', true), // "aaa" includes 'a'
                std::make_tuple("aaa", 'b', false), // "aaa" does not contain 'b'
                std::make_tuple("1234567890", "123", true), // "1234567890" includes "123"
                std::make_tuple("1234567890", std::vector<std::string>{"1", "5"}, true), // "1234567890" includes "123"
                std::make_tuple("1234567890", std::vector<char>{'1', '5'}, true), // "1234567890" includes "123"
                std::make_tuple("1234567890", "789", true), // "1234567890" includes "789"
                std::make_tuple("1234567890", "012", false), // "1234567890" does not contain "012"
                std::make_tuple("abcdefghijklmnopqrstuvwxyz", "xyz", true), // "abcdefghijklmnopqrstuvwxyz" includes "xyz"
                std::make_tuple("abcdefghijklmnopqrstuvwxyz", "abc", true), // "abcdefghijklmnopqrstuvwxyz" includes "abc"
                std::make_tuple("abcdefghijklmnopqrstuvwxyz", "xyzabc", false), // "abcdefghijklmnopqrstuvwxyz" does not contain "xyzabc"
                std::make_tuple("abcdefghijklmnopqrstuvwxyz", 'a', true), // "abcdefghijklmnopqrstuvwxyz" includes 'a'
                std::make_tuple("abcdefghijklmnopqrstuvwxyz", 'z', true), // "abcdefghijklmnopqrstuvwxyz" includes 'z'
                std::make_tuple("abcdefghijklmnopqrstuvwxyz", std::vector<char>{'1', '8'}, false), // "abcdefghijklmnopqrstuvwxyz" includes 'z'
                std::make_tuple("abcdefghijklmnopqrstuvwxyz", std::vector<std::string>{"Hello", "-abc"}, false), // "abcdefghijklmnopqrstuvwxyz" includes 'z'
                std::make_tuple("abcdefghijklmnopqrstuvwxyz", 'A', false), // "abcdefghijklmnopqrstuvwxyz" does not contain 'A'
                std::make_tuple("abcdefghijklmnopqrstuvwxyz", 'Z', false), // "abcdefghijklmnopqrstuvwxyz" does not contain 'Z'
                std::make_tuple("abcdefghijklmnopqrstuvwxyZ", 'Z', true), // "abcdefghijklmnopqrstuvwxyz" does not contain 'Z'
                std::make_tuple(" ", ' ', true),
                std::make_tuple("hello world", " ", true)
            )
        );

    } // namespace parseop
} // namespace test
