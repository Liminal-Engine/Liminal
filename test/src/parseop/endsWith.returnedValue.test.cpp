/**
 * @file endsWith.returnedValue.test.cpp
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

        using ParseOPEndsWithParam = std::tuple<
            std::string, // input string
            std::string, // input target
            bool // expected result
        >;
        class ParseOPEndsWithMethod : public ::testing::TestWithParam<ParseOPEndsWithParam> {

        };

        TEST_P(ParseOPEndsWithMethod, ReturnsGivenValue) {
            EXPECT_EQ(::parseop::endsWith(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
        };

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousParams,
            ParseOPEndsWithMethod,
            ::testing::Values(
                std::make_tuple("aaa", "a", true),
                std::make_tuple("aaa", "b", false),
                std::make_tuple("Hello World", "Hello", false), // starts with the target
                std::make_tuple("Hello World", "World", true), // does not start with the target
                std::make_tuple("Hello", "", true), // empty target
                std::make_tuple("", "Hello", false), // empty input
                std::make_tuple("", "", true), // both input and target are empty
                std::make_tuple("a", "a", true), // input and target are the same
                std::make_tuple("a", "b", false), // input and target are different
                std::make_tuple("abc", "abc", true), // input and target are the same
                std::make_tuple("abc", "abcd", false), // target is longer than input
                std::make_tuple("abcd", "abc", false), // input is longer than target
                std::make_tuple("abcd", "bcd", true), // input does not start with target
                std::make_tuple("abcd", "a", false), // input starts with target
                std::make_tuple("abcd", "d", true), // input does not start with target
                std::make_tuple("aaa", "aaa", true), // input and target are the same
                std::make_tuple("aaa", "aaaa", false), // target is longer than input
                std::make_tuple("aaaa", "aaa", true), // input is longer than target
                std::make_tuple("abcd", "abcde", false), // target is one character longer than input
                std::make_tuple("abcde", "abcd", false), // input is one character longer than target
                std::make_tuple("abcd", "abcd", true), // input and target are the same (longer strings)
                std::make_tuple("abcd", "abc", false), // input does not start with target (longer input)
                std::make_tuple("abcd", "bcd", true), // input does not start with target (longer input)
                std::make_tuple("abcd", "ab", false), // input starts with target (longer input)
                std::make_tuple("abcd", "d", true), // input does not start with target (longer input)
                std::make_tuple("aaaaa", "a", true), // input starts with target (longer input)
                std::make_tuple("a", "aa", false), // target is longer than input (shorter input)
                std::make_tuple("a", "aaa", false), // target is much longer than input (shorter input)
                std::make_tuple("Hello World", "H", false), // starts with a single character target
                std::make_tuple("Hello World", "d", true), // starts with a single character target
                std::make_tuple("Hello World", "Hello", false), // target is longer than input
                std::make_tuple("Hello World", "Hello World!", false), // input and target are the same
                std::make_tuple("Hello World!", "!", true), // input ends with the target
                std::make_tuple("Hello World!", "Hello World!!", false), // target is longer than input
                std::make_tuple("Hello World!", "o W", false), // target is in the middle of the input
                std::make_tuple("Hello World!", " World!", true), // target starts in the middle of the input
                std::make_tuple("", "Hello", false), // empty input
                std::make_tuple("Hello", "", true), // empty target
                std::make_tuple("/path/to/file.txt", ".txt", true), // ends with the target
                std::make_tuple("/path/to/file.txt", "/path", false), // does not end with the target
                std::make_tuple("/path/to/file.txt", "", true), // empty target
                std::make_tuple("", ".txt", false), // empty input
                std::make_tuple("", "", true), // both input and target are empty
                std::make_tuple(".txt", ".txt", true), // input and target are the same
                std::make_tuple(".txt", ".doc", false), // input and target are different
                std::make_tuple("/path/to/file.txt", "/path/to/file.txt", true), // input and target are the same
                std::make_tuple("/path/to/file.txt", "/path/to/file.txt/extra", false), // target is longer than input
                std::make_tuple("/path/to/file.txt/extra", "/file.txt", false), // input is longer than target
                std::make_tuple("/path/to/file.txt", "/file.txt", true), // input does not end with target
                std::make_tuple("/path/to/file.txt", ".txt", true), // input ends with target
                std::make_tuple("/path/to/file.txt", "/path", false) // input does not end with target
            )
        );

    } // namespace parseop
} // namespace test
