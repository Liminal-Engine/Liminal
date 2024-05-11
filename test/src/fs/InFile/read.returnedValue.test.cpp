/**
 * @file read.returnedValue.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */ 


#include <fs/InFile.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <tuple>
#include <string>
#include <unistd.h>
#include <iostream>

#include <unistd.h>

// TODO : test files with wrong permissions

namespace test {
    namespace fs {
        namespace InFile {
            using FSInFileReadParam = std::tuple<
                ::fs::Path, // path
                ::fs::Status //expected status
            >;
            class FSInFileReadMethod : public ::testing::TestWithParam<FSInFileReadParam> {
                protected:
                    ::fs::InFile _instance;

                    FSInFileReadMethod(void):
                    _instance{::fs::InFile{std::get<0>(GetParam())}}
                    {
                        _instance.open();
                    }

                    ~FSInFileReadMethod() {
                        _instance.close();
                    }
            };

            TEST_P(FSInFileReadMethod, ReturnGivenStatus) {
                EXPECT_EQ(_instance.read(), std::get<1>(GetParam()));
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenOpenablePaths,
                FSInFileReadMethod,
                testing::Values(
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array/wrongFormat.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bool/incomplete.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/brace/missingClosing.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/brace/missingOpening.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket/missingClosing.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket/missingOpening.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"././././/////////./../../test/..////test/assets/json/invalid/bracket/missingOpening.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket/missingOpeningAtRoot.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/missing.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/tooMany.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/tooManyInSimpleKeyValuePair.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/wrongChar.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/misplaced.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/missing.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/missing.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/missingInArray.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/missingInNestedArray.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/missingInNumArray.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/multipleMissingInArray.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/comma/tooMuch.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid/basic.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid/edgeCases.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid/large.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid/nested.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/_ _ _ _. *"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/________.__"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*()"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidden"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/|||empty|||"},::fs::Status::OK)
                )
                );

                INSTANTIATE_TEST_SUITE_P(
                WhenGivenUnopenablePaths,
                FSInFileReadMethod,
                testing::Values(
                    std::make_tuple(::fs::Path{"../../test/../../do/not/exists////---/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/../../do/not/exists////---/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array/wrongFormat.jso"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array/wrongFormat.jso"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*("}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*("}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidde"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidde"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.h"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.h"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/________._"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/________._"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"/abc/def/IDoNotExists/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"/abc/def/IDoNotExists/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/array/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bool"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bool"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bool/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bool/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/brace"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/brace"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/brace/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/brace/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/bracket/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/invalid/colon/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/json/valid"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"/"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"/////.//////"}, ::fs::Status::E_READ_FILE_NOT_OPENED),
                    std::make_tuple(::fs::Path{"/////////////"}, ::fs::Status::E_READ_FILE_NOT_OPENED)
                )
                );
        } // namespace InFile
    } // namespace fs
} // namespace test
