/**
 * @file write.returnedStatus.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-09
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
#include "jsonio/is_in_variant_v.hpp"
#include "jsonio/types.hpp"

#include "test/jsonio/Helper.hpp"
#include "test/jsonio/OutJson/Helper.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <variant>
#include <tuple>
#include <type_traits>
#include <optional>


namespace test {
    namespace jsonio {
        namespace Json {

            using JsonIOJsonWriteMethodReturnedStatusParams = std::tuple<
                ::fs::Path, //input path,
                bool, // should it parse input path
                ::jsonio::Status
            >;

            class JsonIOJsonWriteMethodReturnedStatus : public ::testing::TestWithParam<JsonIOJsonWriteMethodReturnedStatusParams> {

                protected:
                    ::jsonio::Json _instanceWithoutPath;
                    ::jsonio::Json _instanceWithPath;
                    ::fs::Path _instanceWithoutPathOutputPath;
                    ::fs::Path _instanceWithPathOutputPath;

                    JsonIOJsonWriteMethodReturnedStatus(void) :
                    _instanceWithoutPath(),
                    _instanceWithPath(),
                    _instanceWithoutPathOutputPath(::test::jsonio::OutJson::Helper::generateTmpOutputPath()),
                    _instanceWithPathOutputPath(::test::jsonio::OutJson::Helper::generateTmpOutputPath())
                    {
                        if (std::get<1>(GetParam())) {
                            try { // we copy the output of instanceWithoutPath to avoid modifying the test/assets json file
                                std::filesystem::copy(std::get<0>(GetParam()).asStr(), _instanceWithoutPathOutputPath.asStr());
                            }
                            catch(const std::filesystem::filesystem_error& e) { return; }                            
                            _instanceWithoutPath.parse(_instanceWithoutPathOutputPath);
                            _instanceWithPath.parse(std::get<0>(GetParam()));
                        }                        
                    }

                    ~JsonIOJsonWriteMethodReturnedStatus() {
                        if (std::filesystem::exists(this->_instanceWithoutPathOutputPath.asStr())) {
                            std::filesystem::remove(this->_instanceWithoutPathOutputPath.asStr());
                        }
                        if (std::filesystem::exists(this->_instanceWithPathOutputPath.asStr())) {
                            std::filesystem::remove(this->_instanceWithPathOutputPath.asStr());
                        }
                    }

            };

            TEST_P(JsonIOJsonWriteMethodReturnedStatus, ReturnsGivenStatus) {
                EXPECT_EQ(_instanceWithoutPath.write(true), std::get<2>(GetParam()));
                EXPECT_EQ(_instanceWithPath.write(this->_instanceWithPathOutputPath), std::get<2>(GetParam()));

            };

            INSTANTIATE_TEST_SUITE_P(
                whenExpectingStatusOK,
                JsonIOJsonWriteMethodReturnedStatus,
                testing::Values(
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC, true, ::jsonio::Status::OK),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, true, ::jsonio::Status::OK),
                    std::make_tuple(::test::jsonio::Helper::VALID__LARGE, true, ::jsonio::Status::OK),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, true, ::jsonio::Status::OK)
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                whenExpectingStatusENoRootValue,
                JsonIOJsonWriteMethodReturnedStatus,
                testing::Values(
                    std::make_tuple(::test::jsonio::Helper::VALID__BASIC, false, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::VALID__EDGE_CASES, false, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::VALID__NESTED, false, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::fs::Path("/this/PATH/may/.15447487784/NOT/exists/FILE.json"), true, ::jsonio::Status::E_NO_ROOT_VALUE),                  
                    std::make_tuple(::test::jsonio::Helper::JSONIO__ASSETS__DIR, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__EMPTY, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__ARRAY__WRONG_FORMAT, true, ::jsonio::Status::E_NO_ROOT_VALUE),
        
                    std::make_tuple(::test::jsonio::Helper::INVALID__BOOL__INCOMPLETE, true, ::jsonio::Status::E_NO_ROOT_VALUE),
        
                    std::make_tuple(::test::jsonio::Helper::INVALID__BRACE__MISSING_CLOSING, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__BRACE__MISSING_OPENING, true, ::jsonio::Status::E_NO_ROOT_VALUE),
        
                    std::make_tuple(::test::jsonio::Helper::INVALID__BRACKET__MISING_CLOSING, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__BRACKET__MISING_OPENING, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__BRACKET__MISING_OPENING_AT_ROOT, true, ::jsonio::Status::E_NO_ROOT_VALUE),
        
                    std::make_tuple(::test::jsonio::Helper::INVALID_COLON__MISSING, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID_COLON__TOO_MANY, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID_COLON__TOO_MANY_IN_SIMPLE_KEY_VALUE_PAIR, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID_COLON__WRONG_CHAR, true, ::jsonio::Status::E_NO_ROOT_VALUE),
        
                    std::make_tuple(::test::jsonio::Helper::INVALID__COMMA__MISPLACED, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__COMMA__MISSING, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__COMMA__MISSING_IN_ARRAY, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__COMMA__MISSING_IN_NESTED_ARRAY, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__COMMA__MISSING_IN_NUM_ARRAY, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__COMMA__MULTIPLE_MISSING_IN_ARRAY, true, ::jsonio::Status::E_NO_ROOT_VALUE),
                    std::make_tuple(::test::jsonio::Helper::INVALID__COMMA__TOO_MUCH, true, ::jsonio::Status::E_NO_ROOT_VALUE)
                )
            );

        } // namespace Json
    } // namespace jsonio
} // namespace test