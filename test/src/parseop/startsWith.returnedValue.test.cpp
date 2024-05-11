/**
 * @file startsWith.returnedValue.test.cpp
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

        using ParseOPStartsWithParam = std::tuple<
            std::string, // input string
            std::string, // input target
            bool // expected result
        >;
        class ParseOPStartsWithMethod : public ::testing::TestWithParam<ParseOPStartsWithParam> {

        };

        TEST_P(ParseOPStartsWithMethod, ReturnsGivenValue) {
            EXPECT_EQ(::parseop::startsWith(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
        };

        INSTANTIATE_TEST_SUITE_P(
            WhenGivenVariousParams,
            ParseOPStartsWithMethod,
            ::testing::Values(
                std::make_tuple("aaa", "a", true),
                std::make_tuple("aaa", "b", false),
                std::make_tuple("Hello World", "Hello", true), // starts with the target
                std::make_tuple("Hello World", "World", false), // does not start with the target
                std::make_tuple("Hello", "", true), // empty target
                std::make_tuple("", "Hello", false), // empty input
                std::make_tuple("", "", true), // both input and target are empty
                std::make_tuple("a", "a", true), // input and target are the same
                std::make_tuple("a", "b", false), // input and target are different
                std::make_tuple("abc", "abc", true), // input and target are the same
                std::make_tuple("abc", "abcd", false), // target is longer than input
                std::make_tuple("abcd", "abc", true), // input is longer than target
                std::make_tuple("abcd", "bcd", false), // input does not start with target
                std::make_tuple("abcd", "a", true), // input starts with target
                std::make_tuple("abcd", "d", false), // input does not start with target
                std::make_tuple("aaa", "aaa", true), // input and target are the same
                std::make_tuple("aaa", "aaaa", false), // target is longer than input
                std::make_tuple("aaaa", "aaa", true), // input is longer than target
                std::make_tuple("abcd", "abcde", false), // target is one character longer than input
                std::make_tuple("abcde", "abcd", true), // input is one character longer than target
                std::make_tuple("abcd", "abcd", true), // input and target are the same (longer strings)
                std::make_tuple("abcd", "abc", true), // input does not start with target (longer input)
                std::make_tuple("abcd", "bcd", false), // input does not start with target (longer input)
                std::make_tuple("abcd", "ab", true), // input starts with target (longer input)
                std::make_tuple("abcd", "d", false), // input does not start with target (longer input)
                std::make_tuple("aaaaa", "a", true), // input starts with target (longer input)
                std::make_tuple("a", "aa", false), // target is longer than input (shorter input)
                std::make_tuple("a", "aaa", false), // target is much longer than input (shorter input)
                std::make_tuple("Hello World", "H", true), // starts with a single character target
                std::make_tuple("Hello World", "Hello", true), // target is longer than input
                std::make_tuple("Hello World", "Hello World!", false), // input and target are the same
                std::make_tuple("Hello World!", "!", false), // input ends with the target
                std::make_tuple("Hello World!", "Hello World!!", false), // target is longer than input
                std::make_tuple("Hello World!", "o W", false), // target is in the middle of the input
                std::make_tuple("Hello World!", " World!", false), // target starts in the middle of the input
                std::make_tuple("", "Hello", false), // empty input
                std::make_tuple("Hello", "", true), // empty target
                std::make_tuple("/path/to/file.txt", "/path", true), // starts with the target
                std::make_tuple("../path/to/file.txt", "..", true), // starts with the target
                std::make_tuple("/../path/to/file.txt", "/", true), // starts with the target
                std::make_tuple("/path/to/file.txt", "/file", false), // does not start with the target
                std::make_tuple("/path/to/file.txt", "", true), // empty target
                std::make_tuple("", "/path", false), // empty input
                std::make_tuple("", "", true), // both input and target are empty
                std::make_tuple("/path", "/path", true), // input and target are the same
                std::make_tuple("/path", "/other", false), // input and target are different
                std::make_tuple("/path/to/file.txt", "/path/to/file.txt", true), // input and target are the same
                std::make_tuple("/path/to/file.txt", "/path/to/file.txt/extra", false), // target is longer than input
                std::make_tuple("/path/to/file.txt/extra", "/path/to/file.txt", true), // input is longer than target
                std::make_tuple("/path/to/file.txt", "/file.txt", false), // input does not start with target
                std::make_tuple("/path/to/file.txt", "/path", true), // input starts with target
                std::make_tuple("/path/to/file.txt", ".txt", false) // input does not start with target
            )
        );

    } // namespace parseop
} // namespace test
