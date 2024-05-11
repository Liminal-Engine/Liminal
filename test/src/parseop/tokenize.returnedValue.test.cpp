/**
 * @file tokenize.returnedValue.test.cpp
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
                return ::parseop::tokenize(std::get<0>(param), arg, std::get<2>(param));
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

    } // namespace parseop
} // namespace test
