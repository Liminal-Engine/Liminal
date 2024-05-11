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
// // Incudes required for InJson internal calls TODO : remove this ?
#include "jsonio/include/_private/_lexing/_types.hpp"
#include "jsonio/include/_private/_lexing/_lexing.hpp"
// //**********

#include "jsonio/InJson.hpp"

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
        namespace InJson {

            // // TODO : test if send a non-json file

            // // TODO : test all JsonIO return status


            using JsonIOInJsonParseParam = std::pair<
                ::fs::Path, // path of file to parse
                ::jsonio::Status // expected Status
            >;

            class JsonIOInJsonParseMethod : public ::testing::TestWithParam<JsonIOInJsonParseParam> {

                protected:
                    ::jsonio::InJson _instance;

                    JsonIOInJsonParseMethod(void) :
                    _instance()
                    {}

            };

            TEST_P(JsonIOInJsonParseMethod, ReturnsGivenStatus) {
                EXPECT_EQ(_instance.parse(GetParam().first), GetParam().second);
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenInvalidJsonContent,
                JsonIOInJsonParseMethod,
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
                JsonIOInJsonParseMethod,
                testing::Values(
                    std::make_pair(::test::jsonio::Helper::VALID__BASIC, ::jsonio::Status::OK),
                    std::make_pair(::test::jsonio::Helper::VALID__EDGE_CASES, ::jsonio::Status::OK),
                    std::make_pair(::test::jsonio::Helper::VALID__NESTED, ::jsonio::Status::OK),
                    std::make_pair(::test::jsonio::Helper::VALID__LARGE, ::jsonio::Status::OK)
                )
            );

            // # FIXME : transform this to status::FILE_NOT_FOUND
            // # FIXME : test all parse return status
            // INSTANTIATE_TEST_SUITE_P(
            //     WhenFilePathDoesNotExist,
            //     JsonIOInJsonParseMethod,
            //     testing::Values(
            //         std::make_pair(::test::jsonio::Helper::INEXISTANT_PATH, ::jsonio::Status::NOK),
            //         std::make_pair(::test::jsonio::Helper::VALID__BASIC + ::test::jsonio::Helper::INEXISTANT_PATH, ::jsonio::Status::NOK),
            //         std::make_pair(::test::jsonio::Helper::MISSING_LETTER_IN_FILE_EXT, ::jsonio::Status::NOK)
            //     )
            // );

        } // namespace InJson
    } // namespace jsonio
} // namespace test