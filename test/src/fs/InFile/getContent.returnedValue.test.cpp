/**
 * @file getContent.returnedValue.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "test/fs/InFile/Helper.hpp"

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
            using FSInFileGetContentParam = std::tuple<
                ::fs::Path, // path
                std::string // expected returned content
                
            >;
            class FSInFileGetContentMethod : public ::testing::TestWithParam<FSInFileGetContentParam> {
                protected:
                    ::fs::InFile _instance;

                    FSInFileGetContentMethod(void):
                    _instance{::fs::InFile{std::get<0>(GetParam())}}
                    {
                        _instance.open();
                        _instance.read();
                    }

                    ~FSInFileGetContentMethod() {
                        _instance.close();
                    }
            };

            TEST_P(FSInFileGetContentMethod, ReturnGivenStatus) {
                ::fs::Path inputPath(std::get<0>(GetParam()));
                std::string expectedResult = std::get<1>(GetParam());

                EXPECT_EQ(_instance.getContent(), expectedResult);
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenOpenablePaths,
                FSInFileGetContentMethod,
                testing::Values(
                    std::make_tuple(::fs::Path("../../test/assets/jsonio/invalid/array/wrongFormat.json"), ::test::fs::InFile::Helper::JSON_INVALID_ARRAY_WRONG_FORMAT),
                    std::make_tuple(::fs::Path("../../test/assets/jsonio/invalid/bool/incomplete.json"), ::test::fs::InFile::Helper::JSON_INVALID_BOOL_INCOMPLETE),
                    std::make_tuple(::fs::Path("../../test/assets/jsonio/valid/basic.json"), ::test::fs::InFile::Helper::JSON_VALID_BASIC),
                    std::make_tuple(::fs::Path("../../test/assets/jsonio/valid/edgeCases.json"), ::test::fs::InFile::Helper::JSON_VALID_EDGE_CASES),
                    std::make_tuple(::fs::Path("../../test/assets/jsonio/valid/nested.json"), ::test::fs::InFile::Helper::JSON_VALID_NESTED),
                    std::make_tuple(::fs::Path("../../test/assets/fs/!@#$%^&*().!@#$%^&*()"), ::test::fs::InFile::Helper::SPECIAL_CHARS),
                    std::make_tuple(::fs::Path("../../test/assets/fs/.hidden"), ::test::fs::InFile::Helper::HIDDEN),
                    std::make_tuple(::fs::Path("../../test/assets/fs/|||empty|||"), "")
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenUnopenablePaths,
                FSInFileGetContentMethod,
                testing::Values(
                    std::make_tuple(::fs::Path("-----------../../test/wrongFormat.json"), ""),
                    std::make_tuple(::fs::Path(""), ""),
                    std::make_tuple(::fs::Path("-"), ""),
                    std::make_tuple(::fs::Path(".///.././//./"), ""),
                    std::make_tuple(::fs::Path("/"), "")
                )
            );
        } // namespace InFile
    } // namespace fs
} // namespace test
