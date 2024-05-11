/**
 * @file join.returnedValue.test.cpp
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
                return ::parseop::join(std::get<0>(param), arg);
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

    } // namespace parseop
} // namespace test
