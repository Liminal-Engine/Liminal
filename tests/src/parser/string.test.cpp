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


#include <parser/string.hpp>

#include <constants.test.hpp>

#include <variant>
#include <tuple>
#include <gtest/gtest.h>
#include <gmock/gmock.h>


using isPositiveIntegerParam = std::tuple<
    std::string, // input str,
    bool // expected result
>;
class ParserStringisPositiveIntegerFunc : public ::testing::TestWithParam<isPositiveIntegerParam>{

};

TEST_P(ParserStringisPositiveIntegerFunc, ReturnsGivenValue) {
    EXPECT_EQ(parser::string::isPositiveInteger(std::get<0>(GetParam())), std::get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousValues,
    ParserStringisPositiveIntegerFunc,
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
class ParserStringIsBoolFunc : public ::testing::TestWithParam<IsBoolParam>{

};

TEST_P(ParserStringIsBoolFunc, ReturnsGivenValue) {
    EXPECT_EQ(parser::string::isBool(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousValues,
    ParserStringIsBoolFunc,
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

using ParserStringToBoolParam = std::tuple<
    std::string, // input str
    bool, // include_nb
    bool // expected result
>;
class ParserStringToBoolFunc : public ::testing::TestWithParam<ParserStringToBoolParam>{

};

TEST_P(ParserStringToBoolFunc, ReturnsGivenValue) {
    std::string input_str = std::get<0>(GetParam());
    bool include_nb = std::get<1>(GetParam());
    bool expected_res = std::get<2>(GetParam());

    EXPECT_EQ(parser::string::toBool(input_str, include_nb), expected_res);
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousValues,
    ParserStringToBoolFunc,
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

using ParserStringContainsParam = std::tuple<
    std::string, // input str
    std::variant<std::string, char>, // content to find
    bool // expected result
>;
class ParserStringContainsFunc : public ::testing::TestWithParam<ParserStringContainsParam> {

};

TEST_P(ParserStringContainsFunc, ReturnsGivenValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parser::string::contains(std::get<0>(param), arg);
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<2>(param));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousValues,
    ParserStringContainsFunc,
    ::testing::Values(
        std::make_tuple("aaa", "a", true),
        std::make_tuple("aaa", 'a', true),
        std::make_tuple("", "", true), // empty string contains empty string
        std::make_tuple("", 'a', false), // empty string does not contain 'a'
        std::make_tuple("aaa", "aa", true), // "aaa" contains "aa"
        std::make_tuple("aaa", "aaa", true), // "aaa" contains "aaa"
        std::make_tuple("aaa", "aaaa", false), // "aaa" does not contain "aaaa"
        std::make_tuple("aaa", 'a', true), // "aaa" contains 'a'
        std::make_tuple("aaa", 'b', false), // "aaa" does not contain 'b'
        std::make_tuple("1234567890", "123", true), // "1234567890" contains "123"
        std::make_tuple("1234567890", "789", true), // "1234567890" contains "789"
        std::make_tuple("1234567890", "012", false), // "1234567890" does not contain "012"
        std::make_tuple("abcdefghijklmnopqrstuvwxyz", "xyz", true), // "abcdefghijklmnopqrstuvwxyz" contains "xyz"
        std::make_tuple("abcdefghijklmnopqrstuvwxyz", "abc", true), // "abcdefghijklmnopqrstuvwxyz" contains "abc"
        std::make_tuple("abcdefghijklmnopqrstuvwxyz", "xyzabc", false), // "abcdefghijklmnopqrstuvwxyz" does not contain "xyzabc"
        std::make_tuple("abcdefghijklmnopqrstuvwxyz", 'a', true), // "abcdefghijklmnopqrstuvwxyz" contains 'a'
        std::make_tuple("abcdefghijklmnopqrstuvwxyz", 'z', true), // "abcdefghijklmnopqrstuvwxyz" contains 'z'
        std::make_tuple("abcdefghijklmnopqrstuvwxyz", 'A', false), // "abcdefghijklmnopqrstuvwxyz" does not contain 'A'
        std::make_tuple("abcdefghijklmnopqrstuvwxyz", 'Z', false), // "abcdefghijklmnopqrstuvwxyz" does not contain 'Z'
        std::make_tuple("abcdefghijklmnopqrstuvwxyZ", 'Z', true), // "abcdefghijklmnopqrstuvwxyz" does not contain 'Z'
        std::make_tuple(" ", ' ', true),
        std::make_tuple("hello world", " ", true)
    )
);

using ParserStringIsOnlyCharParam = std::tuple<
    std::string, // input str
    char, // 
    bool // expected result
>;
class ParserStringIsOnlyCharFunc : public ::testing::TestWithParam<ParserStringIsOnlyCharParam> {

};

TEST_P(ParserStringIsOnlyCharFunc, ReturnsGivenValue) {
    EXPECT_EQ(parser::string::isOnlyChar(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringIsOnlyCharFunc,
    ::testing::Values(
        std::make_tuple("aaaaaaaaaaaaaaaaaaaaaaaaaaa", 'a', true),
        std::make_tuple("", 'a', true), // empty string is considered to be composed of any character
        std::make_tuple("a", 'a', true), // single character string is composed of that character
        std::make_tuple("aa", 'a', true), // string with multiple occurrences of the given character
        std::make_tuple("aaa", 'a', true), // string with multiple occurrences of the given character
        std::make_tuple("aaaaa", 'a', true), // string with multiple occurrences of the given character
        std::make_tuple("ab", 'a', false), // string with different character than the given one
        std::make_tuple("abc", 'a', false), // string with different character than the given one
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

using ParserStringToIntMaxParam = std::tuple<
    std::string, // input str
    intmax_t // expected result
>;
class ParserStringToIntMaxFunc : public ::testing::TestWithParam<ParserStringToIntMaxParam> {

};

TEST_P(ParserStringToIntMaxFunc, ReturnsExpectedValue) {
    EXPECT_EQ(parser::string::toIntMax(std::get<0>(GetParam())), std::get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringToIntMaxFunc,
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

using ParserStringToLongDoubleParam = std::tuple<
    std::string, // input str
    long double // expected result
>;
class ParserStringToLongDoubleFunc : public ::testing::TestWithParam<ParserStringToLongDoubleParam> {

};

TEST_P(ParserStringToLongDoubleFunc, WhenGivenVariousValues) {
    EXPECT_NEAR(parser::string::toLongDouble(std::get<0>(GetParam())), std::get<1>(GetParam()), constants::EXPECT_NEAR_ABSOLUTE_ERROR);
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringToLongDoubleFunc,
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

using ParserStringToSizeTParam = std::tuple<
    std::string, // input str
    long double, // accepted error
    size_t // expected result
>;
class ParserStringToSizeTFunc : public ::testing::TestWithParam<ParserStringToSizeTParam> {

};

TEST_P(ParserStringToSizeTFunc, ReturnsExpectedValue) {
    EXPECT_NEAR(parser::string::toSize_t(std::get<0>(GetParam())), std::get<2>(GetParam()), std::get<1>(GetParam()));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringToSizeTFunc,
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

using ParserStringGetNOccurencesParam = std::tuple<
    std::string, // input string
    std::variant<char, std::string>, //occurences
    std::size_t // expected result
>;
class ParserStringGetNOccurencesFunc : public ::testing::TestWithParam<ParserStringGetNOccurencesParam> {

};

TEST_P(ParserStringGetNOccurencesFunc, ReturnsExpectedValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parser::string::getNOccurences(std::get<0>(param), arg);
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<2>(param));
}

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringGetNOccurencesFunc,
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

using ParserStringLastIndexOfParam = std::tuple<
    std::string, // input string
    char, // wanted char
    std::size_t // expected result
>;
class ParserStringLastIndexOfFunc : public ::testing::TestWithParam<ParserStringLastIndexOfParam> {

};

TEST_P(ParserStringLastIndexOfFunc, WhenGivenVariousValues) {
    EXPECT_EQ(parser::string::lastIndexOf(std::get<0>(GetParam()), std::get<1>(GetParam())), std::get<2>(GetParam()));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringLastIndexOfFunc,
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

using ParserStringTokenizeParam = std::tuple<
    std::string, // input string
    std::variant< std::vector<std::string>, std::string, char >, // delimiters
    bool, // whether to include delimiter
    std::vector<std::string>
>;
class ParserStringTokenizeFunc : public ::testing::TestWithParam<ParserStringTokenizeParam> {

};

TEST_P(ParserStringTokenizeFunc, ReturnsGivenValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parser::string::tokenize(std::get<0>(param), arg, std::get<2>(param));
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<3>(param));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousValues,
    ParserStringTokenizeFunc,
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


        
using ParserStringEraseAllParam = std::tuple<
    std::string, // input string
    std::variant<std::vector<std::string>, std::string>, // substrings to erase
    std::string // expected result
>;
class ParserStringEraseAllFunc : public ::testing::TestWithParam<ParserStringEraseAllParam> {

};

TEST_P(ParserStringEraseAllFunc, ReturnsGivenValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parser::string::eraseAll(std::get<0>(param), arg);
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<2>(param));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringEraseAllFunc,
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

using ParserStringTrimBeginParam = std::tuple<
    std::string, // input string
    std::variant<
        char,
        std::vector<char>,
        std::string,
        std::vector<std::string>
    >, // data to trim
    std::string // expected result
>;
class ParserStringTrimBeginFunc : public ::testing::TestWithParam<ParserStringTrimBeginParam> {

};

TEST_P(ParserStringTrimBeginFunc, ReturnsGivenValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parser::string::trimBegin(std::get<0>(param), arg);
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<2>(param));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringTrimBeginFunc,
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

using ParserStringTrimEndParam = std::tuple<
    std::string, // input string
    std::variant<
        char,
        std::vector<char>,
        std::string,
        std::vector<std::string>
    >, // data to trim
    std::string // expected result
>;
class ParserStringTrimEndFunc : public ::testing::TestWithParam<ParserStringTrimEndParam> {

};

TEST_P(ParserStringTrimEndFunc, ReturnsGivenValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parser::string::trimEnd(std::get<0>(param), arg);
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<2>(param));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringTrimEndFunc,
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

using ParserStringTrimParam = std::tuple<
    std::string, // input string
    std::variant<
        char,
        std::vector<char>,
        std::string,
        std::vector<std::string>
    >, // data to trim
    std::string // expected result
>;
class ParserStringTrimFunc : public ::testing::TestWithParam<ParserStringTrimParam> {

};

TEST_P(ParserStringTrimFunc, ReturnsGivenValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parser::string::trim(std::get<0>(param), arg);
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<2>(param));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringTrimFunc,
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


using ParserStringJoinParam = std::tuple<
    std::vector<std::string>, // input string vector
    std::variant<char, std::string>, // separator
    std::string // expected result
>;
class ParserStringJoinFunc : public ::testing::TestWithParam<ParserStringJoinParam> {

};

TEST_P(ParserStringJoinFunc, ReturnsGivenValue) {
    auto param = GetParam();
    auto result = std::visit([&](auto&& arg) {
        return parser::string::join(std::get<0>(param), arg);
    }, std::get<1>(param));
    EXPECT_EQ(result, std::get<2>(param));
};

INSTANTIATE_TEST_SUITE_P(
    WhenGivenVariousParams,
    ParserStringJoinFunc,
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

