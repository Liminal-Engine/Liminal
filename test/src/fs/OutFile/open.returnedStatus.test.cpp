/**
 * @file open.returnedStaatus.test.cpp
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
            using FSOutFileOpenParam = std::tuple<
                ::fs::Path, // path
                ::fs::Status //expected status
            >;
            class FSOutFileOpenMethod : public ::testing::TestWithParam<FSOutFileOpenParam> {
                protected:
                    ::fs::OutFile _instance;

                    FSOutFileOpenMethod(void):
                    _instance{::fs::OutFile{std::get<0>(GetParam())}}
                    {}

                    ~FSOutFileOpenMethod() {
                        _instance.close();
                    }
            };

            TEST_P(FSOutFileOpenMethod, ReturnGivenStatus) {
                EXPECT_EQ(_instance.open(), std::get<1>(GetParam()));
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenValidFilePaths,
                FSOutFileOpenMethod,
                testing::Values(
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/array/wrongFormat.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets//.//./jsonio/invalid/////array/wrongFormat.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bool/incomplete.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/brace/missingClosing.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/brace/missingOpening.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bracket/missingClosing.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bracket/missingOpening.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bracket/missingOpeningAtRoot.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/missing.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/tooMany.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/tooManyInSimpleKeyValuePair.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/wrongChar.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/misplaced.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/missing.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/missing.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/missingInArray.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/missingInNestedArray.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/missingInNumArray.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/multipleMissingInArray.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/comma/tooMuch.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/valid/basic.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/valid/edgeCases.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/valid/large.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/valid/nested.json"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/_ _ _ _. *"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/________.__"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*()"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"..//////../test/../test/assets/fs/././././!@#$%^&*().!@#$%^&*()"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidden"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/|||empty|||"}, ::fs::Status::OK),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/|||empty|||///////////////"}, ::fs::Status::OK)
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenPathWithNoRealTarget,
                FSOutFileOpenMethod,
                testing::Values(
                    std::make_tuple(::fs::Path{"../../test/../../do/not/exists////---/"}, ::fs::Status::E_PATH_NO_TARGET),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/array/wrongFormat.jso"}, ::fs::Status::E_PATH_NO_TARGET),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/missingInValueStringStringStringStringStringStringObject.json"}, ::fs::Status::E_PATH_NO_TARGET),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/!@#$%^&*().!@#$%^&*("}, ::fs::Status::E_PATH_NO_TARGET),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.hidde"}, ::fs::Status::E_PATH_NO_TARGET),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/.h"}, ::fs::Status::E_PATH_NO_TARGET),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/________._"}, ::fs::Status::E_PATH_NO_TARGET),
                    std::make_tuple(::fs::Path{"/abc/def/IDoNotExists/"}, ::fs::Status::E_PATH_NO_TARGET),
                    std::make_tuple(::fs::Path{"//////////////abc/def/IDoNotExists/"}, ::fs::Status::E_PATH_NO_TARGET)
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenPathOfDirectory,
                FSOutFileOpenMethod,
                testing::Values(
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/array"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/array/"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bool"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bool/"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/brace"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/brace/"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bracket"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/bracket/"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/invalid/colon/"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/jsonio/valid"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"../../test/assets/fs/"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{".////////././././///././../../test/assets/fs/"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"/"}, ::fs::Status::E_PATH_IS_DIR),
                    std::make_tuple(::fs::Path{"/////////////////////////////"}, ::fs::Status::E_PATH_IS_DIR)

                )
            );
        } // namespace OutFile
    } // namespace fs
} // namespace test
