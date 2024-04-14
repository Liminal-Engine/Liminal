/**
 * @file string.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-31
 * 
 * @copyright Copyright (c) 2024
 * 
*/


#include <parseop/parseop.hpp>

#include <constants.test.hpp>

#include <variant>
#include <tuple>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


using isPositiveIntegerParam = std::tuple<
    std::string, // input str,
    bool // expected result
>;
class ParseOPStringIsPositiveIntegerFunc : public ::testing::TestWithParam<isPositiveIntegerParam>{

};

TEST_P(ParseOPStringIsPositiveIntegerFunc, ReturnsGivenValue) {
    EXPECT_EQ(parseop::isPositiveInteger(std::get<0>(GetParam())), std::get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousValues,
    ParseOPStringIsPositiveIntegerFunc,
    ::testing::Values(
        std::make_tuple("1", true),
        std::make_tuple("10", true),
        std::make_tuple("12", true),
        std::make_tuple("2", true),
        std::make_tuple("22222222227777777777777714518748744145418187", true),
        std::make_tuple("0748744145418187", true),
        std::make_tuple("0", true), // yes, 0 is considered to be positive with this func
        std::make_tuple("000000000000000000000000000000000000000000000", true), // yes, 0 is considered to be positive with this func
        std::make_tuple("0000000000000000000000000000000000000000000001", true), // yes, 0 is considered to be positive with this func

        std::make_tuple("-1", false),
        std::make_tuple("-8484651651561561", false),
        std::make_tuple("-0.284841", false),
        std::make_tuple("0.284841", false),
        std::make_tuple("0.284841", false),
        std::make_tuple("0.45454284841", false),
        std::make_tuple("1008787.45454284841", false)

    )
);

using IsBoolParam = std::tuple<
    std::string, // input string
    bool, // include_nb,
    bool // expected result
>;
class ParseOPStringIsBoolFunc : public ::testing::TestWithParam<IsBoolParam>{

};

TEST_P(ParseOPStringIsBoolFunc, ReturnsGivenValue) {
    EXPECT_EQ(parseop::isBool(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
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

using ParseOPStringToBoolParam = std::tuple<
    std::string, // input str
    bool, // include_nb
    bool // expected result
>;
class ParseOPStringToBoolFunc : public ::testing::TestWithParam<ParseOPStringToBoolParam>{

};

TEST_P(ParseOPStringToBoolFunc, ReturnsGivenValue) {
    std::string input_str = std::get<0>(GetParam());
    bool include_nb = std::get<1>(GetParam());
    bool expected_res = std::get<2>(GetParam());

    EXPECT_EQ(parseop::toBool(input_str, include_nb), expected_res);
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousValues,
    ParseOPStringToBoolFunc,
    ::testing::Values(
        std::make_tuple("true", false, true),
        std::make_tuple("111111", true, true),
        std::make_tuple("1", true, true),
        std::make_tuple("2", true, true),
        std::make_tuple("12", true, true),
        std::make_tuple("84848484847787878", true, true),

        std::make_tuple("false", false, false),
        std::make_tuple("0", true, false),

        std::make_tuple("thisIsOfficialyNotABoolean", false, false),
        std::make_tuple("false////", false, false),
        std::make_tuple("////true////", false, false)
    )
);

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
        return parseop::includes(std::get<0>(param), arg);
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

using ParseOPStringIsOnlyCharParam = std::tuple<
    std::string, // input str
    char, // 
    bool // expected result
>;
class ParseOPStringIsOnlyCharFunc : public ::testing::TestWithParam<ParseOPStringIsOnlyCharParam> {

};

TEST_P(ParseOPStringIsOnlyCharFunc, ReturnsGivenValue) {
    EXPECT_EQ(parseop::isOnlyChar(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
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

using ParseOPStringToIntMaxParam = std::tuple<
    std::string, // input str
    intmax_t // expected result
>;
class ParseOPStringToIntMaxFunc : public ::testing::TestWithParam<ParseOPStringToIntMaxParam> {

};

TEST_P(ParseOPStringToIntMaxFunc, ReturnsExpectedValue) {
    EXPECT_EQ(parseop::toIntMax(std::get<0>(GetParam())), std::get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParseOPStringToIntMaxFunc,
    ::testing::Values(
        std::make_tuple("0", 0),
        std::make_tuple("00000000000000000000", 0),
        std::make_tuple("0000000000000000000000000", 0),
        std::make_tuple("00000000000000000000000001", 1),
        std::make_tuple("123456789", 123456789),
        std::make_tuple("-123456789", -123456789),
        std::make_tuple("9223372036854775807", 9223372036854775807),
        std::make_tuple("-9223372036854775808", -9223372036854775807 - 1)
    )
);

using ParseOPStringToLongDoubleParam = std::tuple<
    std::string, // input str
    long double // expected result
>;
class ParseOPStringToLongDoubleFunc : public ::testing::TestWithParam<ParseOPStringToLongDoubleParam> {

};

TEST_P(ParseOPStringToLongDoubleFunc, WhenGivenVariousValues) {
    EXPECT_NEAR(parseop::toLongDouble(std::get<0>(GetParam())), std::get<1>(GetParam()), constants::EXPECT_NEAR_ABSOLUTE_ERROR);
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParseOPStringToLongDoubleFunc,
    ::testing::Values(
        std::make_tuple("0", 0),
        std::make_tuple("00000000000000000000", 0),
        std::make_tuple("0000000000000000000000000", 0),
        std::make_tuple("00000000000000000000000001", 1),
        std::make_tuple("123456789", 123456789),
        std::make_tuple("-123456789", -123456789),
        std::make_tuple("9223372036854775807", 9223372036854775807),
        std::make_tuple("-9223372036854775808", -9223372036854775807 - 1),
        std::make_tuple("0.0", 0.0),
        std::make_tuple("3.14", 3.14),
        std::make_tuple("-1.23", -1.23),
        std::make_tuple("123456789.987654321", 123456789.987654321),
        std::make_tuple("-987654321.123456789", -987654321.123456789),
        std::make_tuple("1.23e4", 1.23e4L),
        std::make_tuple("-1.23e4", -1.23e4L),
        std::make_tuple("1.23e-4", 1.23e-4L),
        std::make_tuple("-1.23e-4", -1.23e-4L)
    )
);

using ParseOPStringToSizeTParam = std::tuple<
    std::string, // input str
    long double, // accepted error
    size_t // expected result
>;
class ParseOPStringToSizeTFunc : public ::testing::TestWithParam<ParseOPStringToSizeTParam> {

};

TEST_P(ParseOPStringToSizeTFunc, ReturnsExpectedValue) {
    EXPECT_NEAR(parseop::toSize_t(std::get<0>(GetParam())), std::get<2>(GetParam()), std::get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParseOPStringToSizeTFunc,
    ::testing::Values(
        std::make_tuple("0", 0, 0),
        std::make_tuple("00000000000000000000", 0, 0),
        std::make_tuple("0000000000000000000000000", 0, 0),
        std::make_tuple("00000000000000000000000001", 0, 1),
        std::make_tuple("123456789", 0, 123456789),
        std::make_tuple("-123456789", 0, -123456789),
        std::make_tuple("9223372036854775807", 0, 9223372036854775807),
        std::make_tuple("-9223372036854775808", 0, -9223372036854775807 - 1)
    )
);

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
        return parseop::getNOccurences(std::get<0>(param), arg);
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

using ParseOPStringLastIndexOfParam = std::tuple<
    std::string, // input string
    char, // wanted char
    std::size_t // expected result
>;
class ParseOPStringLastIndexOfFunc : public ::testing::TestWithParam<ParseOPStringLastIndexOfParam> {

};

TEST_P(ParseOPStringLastIndexOfFunc, WhenGivenVariousValues) {
    EXPECT_EQ(parseop::lastIndexOf(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
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

using ParseOPStringTokenizeParam = std::tuple<
    std::string, // input string
    std::variant< std::vector<std::string>, std::string, char >, // delimiters
    bool, // whether to include delimiter
    std::vector<std::string>
>;
class ParseOPStringTokenizeFunc : public ::testing::TestWithParam<ParseOPStringTokenizeParam> {

};

TEST_P(ParseOPStringTokenizeFunc, ReturnsGivenValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parseop::tokenize(std::get<0>(param), arg, std::get<2>(param));
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<3>(param));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousValues,
    ParseOPStringTokenizeFunc,
    ::testing::Values(
        std::make_tuple("Hello, world!", ',', false, std::vector<std::string>{"Hello", " world!"}),
        std::make_tuple("Hello, world!", ',', true, std::vector<std::string>{"Hello", ",", " world!"}),
        std::make_tuple("Hello, world!", "o", false, std::vector<std::string>{"Hell", ", w", "rld!"}),
        std::make_tuple("Hello, world!", "o", true, std::vector<std::string>{"Hell", "o", ", w", "o", "rld!"}),
        std::make_tuple("Hello, world!", std::vector<std::string>{"o", " "}, false, std::vector<std::string>{"Hell", ",", "w", "rld!"}),
        std::make_tuple("Hello, world!", std::vector<std::string>{"o", " "}, true, std::vector<std::string>{"Hell", "o", ",", " ", "w", "o", "rld!"}),
        std::make_tuple("", ' ', false, std::vector<std::string>{""}),
        std::make_tuple("", ' ', true, std::vector<std::string>{""}),
        std::make_tuple("a", 'a', false, std::vector<std::string>{}),
        std::make_tuple("a", 'a', true, std::vector<std::string>{"a"}),
        std::make_tuple("aaa", 'a', false, std::vector<std::string>{}),
        std::make_tuple("aaa", 'a', true, std::vector<std::string>{"a", "a", "a"}),
        std::make_tuple("abcabc", std::vector<std::string>{"a", "b"}, false, std::vector<std::string>{"c", "c"}),
        std::make_tuple("abcabc", std::vector<std::string>{"a", "b"}, true, std::vector<std::string>{"a", "b", "c", "a", "b", "c"}),
        std::make_tuple("ababab", "aba", false, std::vector<std::string>{"bab"}),
        std::make_tuple("ababab", "aba", true, std::vector<std::string>{"aba", "bab"}),
        std::make_tuple("abcabc", "abc", false, std::vector<std::string>{}),
        std::make_tuple("abcabc", "abc", true, std::vector<std::string>{"abc", "abc"}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"abc"}, false, std::vector<std::string>{}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"abc"}, true, std::vector<std::string>{"abc", "abc", "abc"}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"a", "b", "c"}, false, std::vector<std::string>{}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"a", "b", "c"}, true, std::vector<std::string>{"a", "b", "c", "a", "b", "c", "a", "b", "c"}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"ab", "bc"}, false, std::vector<std::string>{"c", "c", "c"}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"ab", "bc"}, true, std::vector<std::string>{"ab", "c", "ab", "c", "ab", "c"}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"de", "fg"}, false, std::vector<std::string>{"abcabcabc"}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"de", "fg"}, true, std::vector<std::string>{"abcabcabc"}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"ab", "de"}, false, std::vector<std::string>{"c", "c", "c"}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"ab", "de"}, true, std::vector<std::string>{ "ab", "c", "ab", "c", "ab", "c" }),
        std::make_tuple("abcabcabc", std::vector<std::string>{"abc", "bc"}, false, std::vector<std::string>{}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"abc", "bc"}, true, std::vector<std::string>{ "abc", "abc", "abc" }),
        std::make_tuple("abcabcabc", std::vector<std::string>{"abc", "a"}, false, std::vector<std::string>{}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"abc", "a"}, true, std::vector<std::string>{"abc", "abc", "abc"}),
        std::make_tuple("abcabcabc", "abcabcabc", true, std::vector<std::string>{"abcabcabc"}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"abcabcabc"}, true, std::vector<std::string>{"abcabcabc"}),
        std::make_tuple("abcabcabc", "abcabcabc", false, std::vector<std::string>{}),
        std::make_tuple("abcabcabc", std::vector<std::string>{"abcabcabc"}, false, std::vector<std::string>{}),
        std::make_tuple("/home/user/documents", '/', false, std::vector<std::string>{"home", "user", "documents"}),
        std::make_tuple("/home/user/documents", '/', true, std::vector<std::string>{"/", "home", "/", "user", "/", "documents"}),
        std::make_tuple("/home/user/documents", std::vector<std::string>{"/", "user"}, false, std::vector<std::string>{"home", "documents"}),
        std::make_tuple("/home/user/documents", std::vector<std::string>{"/", "user"}, true, std::vector<std::string>{"/", "home", "/", "user", "/", "documents"}),
        std::make_tuple("/home/user/documents", 'o', false, std::vector<std::string>{"/h", "me/user/d", "cuments"}),
        std::make_tuple("/home/user/documents", 'o', true, std::vector<std::string>{"/h", "o", "me/user/d", "o", "cuments"}),
        std::make_tuple("/home/user/documents", std::vector<std::string>{"/", "o"}, false, std::vector<std::string>{"h", "me", "user", "d", "cuments"}),
        std::make_tuple("/home/user/documents", std::vector<std::string>{"/", "o"}, true, std::vector<std::string>{ "/", "h", "o", "me", "/", "user", "/", "d", "o", "cuments"}),
        std::make_tuple("/home/user/documents", std::vector<std::string>{"/h", "u/"}, false, std::vector<std::string>{"ome/user/documents"}),
        std::make_tuple("/home/user/documents", std::vector<std::string>{"/h", "u/"}, true, std::vector<std::string>{ "/h", "ome/user/documents"}),
        std::make_tuple("/home/user/documents", std::vector<std::string>{"/", "me"}, false, std::vector<std::string>{"ho", "user", "docu", "nts" }),
        std::make_tuple("/home/user/documents", std::vector<std::string>{"/", "me"}, true, std::vector<std::string>{ "/", "ho", "me", "/", "user", "/", "docu", "me", "nts"}),
        std::make_tuple("/home/user/documents/important/file.txt", '/', false, std::vector<std::string>{"home", "user", "documents", "important", "file.txt"}),
        std::make_tuple("/home/user/documents/important/file.txt", '/', true, std::vector<std::string>{"/", "home", "/", "user", "/", "documents", "/", "important", "/", "file.txt"}),
        std::make_tuple("/home/user/documents/important/file.txt", std::vector<std::string>{"/", "user"}, false, std::vector<std::string>{ "home", "documents", "important", "file.txt"}),
        std::make_tuple("/home/user/documents/important/file.txt", std::vector<std::string>{"/", "user"}, true, std::vector<std::string>{ "/", "home", "/", "user", "/", "documents", "/", "important", "/", "file.txt"}),
        std::make_tuple("/home/user/documents/important/file.txt", std::vector<std::string>{"/home", "/documents"}, false, std::vector<std::string>{ "/user", "/important/file.txt"}),
        std::make_tuple("/home/user/documents/important/file.txt", std::vector<std::string>{"/home", "/documents"}, true, std::vector<std::string>{ "/home", "/user", "/documents", "/important/file.txt" }),
        std::make_tuple("/home/user/documents/important/file.txt", std::vector<std::string>{"/", "file.txt"}, false, std::vector<std::string>{ "home", "user", "documents", "important" }),
        std::make_tuple("/home/user/documents/important/file.txt", std::vector<std::string>{"/", "file.txt"}, true, std::vector<std::string>{"/", "home", "/", "user", "/", "documents", "/", "important", "/", "file.txt"}),
        std::make_tuple("/", '/', true, std::vector<std::string>{"/"}),
        std::make_tuple("/", '/', false, std::vector<std::string>{}),
        std::make_tuple("/testingPath", "/testingPath", true, std::vector<std::string>{"/testingPath"}),
        std::make_tuple("/testingPath", std::vector<std::string>{"/testingPath"}, true, std::vector<std::string>{"/testingPath"}),
        std::make_tuple("/testingPath", "/testingPath", false, std::vector<std::string>{}),
        std::make_tuple("/testingPath", std::vector<std::string>{"/testingPath"}, false, std::vector<std::string>{}),
        std::make_tuple("store/book<0>/author", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "0", "author"}),
        std::make_tuple("store/book<0>/author", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store","book", "0", "author"}),
        std::make_tuple("store/book<1>/title", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store","book", "1", "title"}),
        std::make_tuple("store/book<2>/price", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store","book", "2", "price"}),
        std::make_tuple("store/book<3>/isbn", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store","book", "3", "isbn"}),
        std::make_tuple("hobbies<3>/nestedHobby", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"hobbies","3", "nestedHobby"}),
        std::make_tuple("store/book<4>/publisher", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "4", "publisher"}),
        std::make_tuple("store/book<5>/year", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "5", "year"}),
        std::make_tuple("store/book<6>/language", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "6", "language"}),
        std::make_tuple("store/book<7>/pages", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "7", "pages"}),
        std::make_tuple("store/book<0>/author<0>/name", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "0", "author", "0", "name"}),
        std::make_tuple("store/book<1>/title<0>/language", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "1", "title", "0", "language"}),
        std::make_tuple("store/book<2>/price<0>/currency", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "2", "price", "0", "currency"}),
        std::make_tuple("store/book<3>/isbn<0>/publisher", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "3", "isbn", "0", "publisher"}),
        std::make_tuple("store/book<4>/publisher<0>/year", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "4", "publisher", "0", "year"}),
        std::make_tuple("store/book<5>/year<0>/language", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "5", "year", "0", "language"}),
        std::make_tuple("store/book<6>/language<0>/pages", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "6", "language", "0", "pages"}),
        std::make_tuple("store/book<7>/pages<0>/author", std::vector<std::string>{"/", "<", ">"}, false, std::vector<std::string>{"store", "book", "7", "pages", "0", "author"})
    )
);


        
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
        return parseop::eraseAll(std::get<0>(param), arg);
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
        return parseop::trimBegin(std::get<0>(param), arg);
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
        return parseop::trimEnd(std::get<0>(param), arg);
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

using ParseOPStringTrimParam = std::tuple<
    std::string, // input string
    std::variant<
        char,
        std::vector<char>,
        std::string,
        std::vector<std::string>
    >, // data to trim
    std::string // expected result
>;
class ParseOPStringTrimFunc : public ::testing::TestWithParam<ParseOPStringTrimParam> {

};

TEST_P(ParseOPStringTrimFunc, ReturnsGivenValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parseop::trim(std::get<0>(param), arg);
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<2>(param));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParseOPStringTrimFunc,
    ::testing::Values(
        std::make_tuple("   trailing spaces   ", ' ', "trailing spaces"),
        std::make_tuple("\t\ttrailing tabs\t\t", '\t', "trailing tabs"),
        std::make_tuple("\n\ntrailing newlines\n\n", '\n', "trailing newlines"),
        std::make_tuple("  \tmixed trailing whitespace \t  \n", std::vector<char>{' ', '\t', '\n'}, "mixed trailing whitespace"),
        std::make_tuple("no trailing whitespace", ' ', "no trailing whitespace"),
        std::make_tuple("", ' ', ""),
        std::make_tuple("cabcabcabc", 'c', "abcabcab"),
        std::make_tuple("bcabcabcabc", std::vector<char>{'b', 'c'}, "abcabca"),
        std::make_tuple("bcabcabcabc", std::string("bc"), "abcabca"),
        std::make_tuple("bcabcabcabc", std::vector<std::string>{"ab", "bc"}, "abcabca"),
        std::make_tuple("0981234567890", std::vector<char>{'0', '9', '8'}, "1234567"),
        std::make_tuple("0981234567890", std::string("890"), "1234567"),
        std::make_tuple("09891234567890", std::vector<std::string>{"89", "90", "09"}, "8912345678"),
        std::make_tuple("   trailing spaces   ", std::vector<std::string>{"   "}, "trailing spaces"),
        std::make_tuple("   trailing spaces   ", std::string("   "), "trailing spaces"),
        std::make_tuple("   trailing spaces   ", std::vector<char>{' '}, "trailing spaces"),
        std::make_tuple("   trailing spaces   ", ' ', "trailing spaces"),
        std::make_tuple("no trailing whitespace", ' ', "no trailing whitespace"),
        std::make_tuple("", ' ', ""),
        std::make_tuple("", std::vector<char>{' '}, ""),
        std::make_tuple("", std::string(" "), ""),
        std::make_tuple("", std::vector<std::string>{" "}, ""),
        std::make_tuple("aaa", std::vector<std::string>{"a"}, "")
    )
);


using ParseOPStringJoinParam = std::tuple<
    std::vector<std::string>, // input string vector
    std::variant<char, std::string>, // separator
    std::string // expected result
>;
class ParseOPStringJoinFunc : public ::testing::TestWithParam<ParseOPStringJoinParam> {

};

TEST_P(ParseOPStringJoinFunc, ReturnsGivenValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parseop::join(std::get<0>(param), arg);
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<2>(param));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParseOPStringJoinFunc,
    ::testing::Values(
        std::make_tuple(std::vector<std::string>{"Hello", "world"}, ' ', "Hello world"),
        std::make_tuple(std::vector<std::string>{"Hello", "world"}, ", ", "Hello, world"),
        std::make_tuple(std::vector<std::string>{"Hello", "world"}, "", "Helloworld"),
        std::make_tuple(std::vector<std::string>{"Hello"}, ' ', "Hello"),
        std::make_tuple(std::vector<std::string>{}, ' ', ""),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string(" "), "Hello world !"),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string(", "), "Hello, world, !"),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string(""), "Helloworld!"),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string("!!!"), "Hello!!!world!!!!"),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string("\n"), "Hello\nworld\n!"),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string("\t"), "Hello\tworld\t!"),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string("123"), "Hello123world123!"),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string("abc"), "Helloabcworldabc!"),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string(" "), "Hello world !"),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string(", "), "Hello, world, !"),
        std::make_tuple(std::vector<std::string>{"Hello", "world", "!"}, std::string(""), "Helloworld!"),
        std::make_tuple(std::vector<std::string>{"Hello", "", "world", "", "!"}, std::string(" "), "Hello  world  !"),
        std::make_tuple(std::vector<std::string>{"", "", ""}, std::string(" "), "  "),
        std::make_tuple(std::vector<std::string>{"", "", ""}, std::string(""), ""),
        std::make_tuple(std::vector<std::string>{"", "", ""}, std::string(","), ",,"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, ' ', "abcabcacbde edcba abcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, ", ", "abcabcacbde, edcba, abcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, "", "abcabcacbdeedcbaabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde"}, ' ', "abcabcacbde"),
        std::make_tuple(std::vector<std::string>{}, ' ', ""),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string(" "), "abcabcacbde edcba abcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string(", "), "abcabcacbde, edcba, abcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string(""), "abcabcacbdeedcbaabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string("123"), "abcabcacbde123edcba123abcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string("abc"), "abcabcacbdeabcedcbaabcabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string("def"), "abcabcacbdedefedcbadefabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string("ghi"), "abcabcacbdeghiedcbaghiabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string("jkl"), "abcabcacbdejkledcbajklabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string("mno"), "abcabcacbdemnoedcbamnoabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string("pqr"), "abcabcacbdepqredcbapqrabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string("stu"), "abcabcacbdestuedcbastuabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string("vwx"), "abcabcacbdevwxedcbavwxabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"abcabcacbde", "edcba", "abcabcacbde"}, std::string("yz"), "abcabcacbdeyzedcbayzabcabcacbde"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, ' ', "123 456 789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, ", ", "123, 456, 789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, "", "123456789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, std::string(" "), "123 456 789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, std::string(", "), "123, 456, 789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, std::string(""), "123456789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, std::string("abc"), "123abc456abc789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, std::string("def"), "123def456def789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, std::string("ghi"), "123ghi456ghi789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, std::string("jkl"), "123jkl456jkl789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, std::string("mno"), "123mno456mno789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, std::string("pqr"), "123pqr456pqr789"),
        std::make_tuple(std::vector<std::string>{"123", "456", "789"}, std::string("stu"), "123stu456stu789")
    )
);



using ParseOPStartsWithParam = std::tuple<
    std::string, // input string
    std::string, // input target
    bool // expected result
>;
class ParseOPStartsWithMethod : public ::testing::TestWithParam<ParseOPStartsWithParam> {

};

TEST_P(ParseOPStartsWithMethod, ReturnsGivenValue) {
    EXPECT_EQ(parseop::startsWith(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
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

using ParseOPEndsWithParam = std::tuple<
    std::string, // input string
    std::string, // input target
    bool // expected result
>;
class ParseOPEndsWithMethod : public ::testing::TestWithParam<ParseOPEndsWithParam> {

};

TEST_P(ParseOPEndsWithMethod, ReturnsGivenValue) {
    EXPECT_EQ(parseop::endsWith(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
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
