/**
 * @file close.returnedStatus.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
*/


#include <fs/OutFile.hpp>

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
        namespace OutFile {
            using FSOutFileCloseParam = std::tuple<
                ::fs::Path, // path
                bool, // whether to previously open the file
                ::fs::Status //expected status
            >;
            class FSOutFileCloseMethod : public ::testing::TestWithParam<FSOutFileCloseParam> {
                protected:
                    ::fs::OutFile _instance;

                    FSOutFileCloseMethod(void):
                    _instance(::fs::OutFile{std::get<0>(GetParam())})
                    {
                        if (std::get<1>(GetParam())) _instance.open();
                    }
            };

            TEST_P(FSOutFileCloseMethod, ReturnGivenStatus) {
                ::fs::Status expectedStatus = std::get<2>(GetParam());

                EXPECT_EQ(_instance.close(), expectedStatus);
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenVariousPath,
                FSOutFileCloseMethod,
                testing::Values(
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/array/wrongFormat.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/array/wrongFormat.json"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bool/incomplete.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/brace/missingClosing.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/brace/missingOpening.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bracket/missingClosing.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bracket/missingOpening.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bracket/missingOpeningAtRoot.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/missing.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/tooMany.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/tooManyInSimpleKeyValuePair.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/tooManyInSimpleKeyValuePair.json"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/wrongChar.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/misplaced.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/missing.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/missing.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/missingInArray.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/missingInNestedArray.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/missingInNumArray.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/multipleMissingInArray.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/tooMuch.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/valid/basic.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/valid/edgeCases.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/valid/large.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/valid/nested.json"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/_ _ _ _. *"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/_ _ _ _. *"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/________.__"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*()"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*()"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidden"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidden"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/|||empty|||"}, true, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/../../do/not/exists////---/"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/array/wrongFormat.jso"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*("}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidde"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.h"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/________._"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"/abc/def/IDoNotExists/"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/array"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/array/"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bool"}, true, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bool/"}, true, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/brace"}, true, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/brace/"}, true, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bracket"}, true, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bracket/"}, true, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/valid"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"/"}, false, ::fs::Status::E_CLOSE_FILE_NOT_OPEN),
                    std::make_tuple(::fs::Path{"/"}, true, ::fs::Status::E_CLOSE_FILE_NOT_OPEN)
                )
            );
            
        } // namespace OutFile
    } // namespace fs
} // namespace test
