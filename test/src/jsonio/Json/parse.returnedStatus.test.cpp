/**
 * @file parse.returnedStatus.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-09
 * 
 * @copyright Copyright (c) 2024
 * 
*/


// //**********
// // Incudes required for Json internal calls TODO : remove this ?
#include "jsonio/include/_private/_lexing/_types.hpp"
#include "jsonio/include/_private/_lexing/_lexing.hpp"
// //**********

#include "jsonio/Json.hpp"

#include "test/jsonio/Helper.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <variant>
#include <tuple>
#include <type_traits>

#include <sysop/sysop.hpp>


namespace test {
    namespace jsonio {
        namespace Json {

            // // TODO : test if send a non-json file

            // // TODO : test all JsonIO return status


            using JsonIOJsonParseParam = std::pair<
                ::fs::Path, // path of file to parse
                ::jsonio::Status // expected Status
            >;

            class JsonIOJsonParseMethod : public ::testing::TestWithParam<JsonIOJsonParseParam> {

                protected:
                    ::jsonio::Json _instance;

                    JsonIOJsonParseMethod(void) :
                    _instance()
                    {}

            };

            TEST_P(JsonIOJsonParseMethod, ReturnsGivenStatus) {
                EXPECT_EQ(_instance.parse(GetParam().first), GetParam().second);
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenInvalidJsonContent,
                JsonIOJsonParseMethod,
                testing::Values(
                    std::make_pair(::test::jsonio::Helper::INVALID__ARRAY__WRONG_FORMAT, ::jsonio::Status::E_PARSING),

                    std::make_pair(::test::jsonio::Helper::INVALID__BOOL__INCOMPLETE, ::jsonio::Status::E_PARSING),

                    std::make_pair(::test::jsonio::Helper::INVALID__BRACE__MISSING_CLOSING, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID__BRACE__MISSING_OPENING, ::jsonio::Status::E_PARSING),

                    std::make_pair(::test::jsonio::Helper::INVALID__BRACKET__MISING_CLOSING, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID__BRACKET__MISING_OPENING, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID__BRACKET__MISING_OPENING_AT_ROOT, ::jsonio::Status::E_PARSING),

                    std::make_pair(::test::jsonio::Helper::INVALID_COLON__MISSING, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID_COLON__TOO_MANY, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID_COLON__TOO_MANY_IN_SIMPLE_KEY_VALUE_PAIR, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID_COLON__WRONG_CHAR, ::jsonio::Status::E_PARSING),

                    std::make_pair(::test::jsonio::Helper::INVALID__COMMA__MISPLACED, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID__COMMA__MISSING, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID__COMMA__MISSING_IN_ARRAY, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID__COMMA__MISSING_IN_NESTED_ARRAY, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID__COMMA__MISSING_IN_NUM_ARRAY, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID__COMMA__MULTIPLE_MISSING_IN_ARRAY, ::jsonio::Status::E_PARSING),
                    std::make_pair(::test::jsonio::Helper::INVALID__COMMA__TOO_MUCH, ::jsonio::Status::E_PARSING)

                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenValidJsonContent,
                JsonIOJsonParseMethod,
                testing::Values(
                    std::make_pair(::test::jsonio::Helper::VALID__BASIC, ::jsonio::Status::OK),
                    std::make_pair(::test::jsonio::Helper::VALID__EDGE_CASES, ::jsonio::Status::OK),
                    std::make_pair(::test::jsonio::Helper::VALID__NESTED, ::jsonio::Status::OK),
                    std::make_pair(::test::jsonio::Helper::VALID__LARGE, ::jsonio::Status::OK)
                )
            );

        } // namespace Json
    } // namespace jsonio
} // namespace test