/**
 * @file asStr.returnedValue.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <fs/Path.hpp>

#include <test/fs/Path/Helper.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <tuple>
#include <vector>

namespace test {
    namespace fs {
        namespace Path {
            using FSPathIsRootReturnedValueParam = std::tuple <
                std::string, // string to build path from
                bool // expected result
            >;

            class FSPathIsRootReturnedValueMethod : public ::testing::TestWithParam<FSPathIsRootReturnedValueParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathIsRootReturnedValueMethod(void) :
                    _instances(::test::fs::Path::Helper::create(std::get<0>(GetParam())))
                    {}
            };

            TEST_P(FSPathIsRootReturnedValueMethod, ReturnsGivenValue) {
                bool expectedReturnedValue(std::get<1>(GetParam()));

                for (const ::fs::Path &instance : _instances) {
                    EXPECT_EQ(instance.isRoot(), expectedReturnedValue);
                }
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenRootPaths,
                FSPathIsRootReturnedValueMethod,
                testing::Values(
                    std::make_tuple("/", true),
                    std::make_tuple("/.", true),
                    std::make_tuple("/..", true),
                    std::make_tuple("/./", true),
                    std::make_tuple("/../", true),
                    std::make_tuple("/././", true),
                    std::make_tuple("/../..", true),
                    std::make_tuple("/.././", true),
                    std::make_tuple("/./../", true),
                    std::make_tuple("/../..", true),
                    std::make_tuple("/./..", true),
                    std::make_tuple("/../.", true),
                    std::make_tuple("/.././", true),
                    std::make_tuple("/./././", true),
                    std::make_tuple("/../../..", true),
                    std::make_tuple("/../../../", true),
                    std::make_tuple("/../.././", true),
                    std::make_tuple("/./../../", true),
                    std::make_tuple("/.././..", true),
                    std::make_tuple("/./.././", true),
                    std::make_tuple("/../././", true),
                    std::make_tuple("//", true),
                    std::make_tuple("///", true),
                    std::make_tuple("////", true),
                    std::make_tuple("/././././", true),
                    std::make_tuple("/.././../.", true),
                    std::make_tuple("/../../../../", true),
                    std::make_tuple("/../../../../../", true),
                    std::make_tuple("/../../../.././", true),
                    std::make_tuple("/./../../../../", true),
                    std::make_tuple("/.././../../", true),
                    std::make_tuple("/./.././../", true),
                    std::make_tuple("/../././../", true),
                    std::make_tuple("/..////././../", true),
                    std::make_tuple("/../././..//////", true),
                    std::make_tuple("/..///../../../..///", true),
                    std::make_tuple("/aaa/fff/dd/..///../../../..///", true),
                    std::make_tuple("/yrtt./..", true),
                    std::make_tuple("/yrtt/..", true),
                    // Unicode characters
                    std::make_tuple("/home/user/文件.txt/../../..", true),
                    std::make_tuple("/home//файл.txt/../..", true),
                    std::make_tuple("//ملف.txt/..", true),
                    std::make_tuple("/home/user/ファイル.txt/../..////../..///..", true),
                    std::make_tuple("///파일/user/파일.txt/../../..", true)
                )
            );

                INSTANTIATE_TEST_SUITE_P(
                    WhenGivenNonRootPaths,
                    FSPathIsRootReturnedValueMethod,
                    testing::Values(
                        std::make_tuple("./home/user", false),
                        std::make_tuple("./home/user/../user2", false),
                        std::make_tuple("./home/user/./file.txt", false),
                        std::make_tuple("user//file.txt", false),
                        std::make_tuple("./home/user/dir/", false),
                        std::make_tuple("./home/user/dir/../file.txt", false),
                        std::make_tuple("home/user/dir/./file.txt", false),
                        std::make_tuple("./home/user/dir//file.txt", false),
                        std::make_tuple("./home/user/dir/../../file.txt", false),
                        std::make_tuple("./home/user/dir/subdir/../../../../../../../../../../../../file.txt", false),
                        // Special characters
                        std::make_tuple("./path with spaces/file.txt", false),
                        std::make_tuple("./user@domain/file.txt", false),
                        std::make_tuple("./user#file.txt", false),
                        std::make_tuple("user$file.txt", false),
                        std::make_tuple("./user%file.txt", false),
                        std::make_tuple("./user^file.txt", false),
                        std::make_tuple("./user&file.txt", false),
                        std::make_tuple("./user*file.txt", false),
                        std::make_tuple("./user(file.txt", false),
                        std::make_tuple("./user)file.txt", false),
                        std::make_tuple("./user+file.txt", false),
                        std::make_tuple("./user,file.txt", false),
                        std::make_tuple("./user;file.txt", false),
                        std::make_tuple("./user=file.txt", false),
                        std::make_tuple("./user'file.txt", false),
                        std::make_tuple("./user\"file.txt", false),
                        std::make_tuple("./user`file.txt", false),
                        std::make_tuple("./user~file.txt", false),
                        std::make_tuple("./user!file.txt", false),
                        std::make_tuple("./user{file.txt", false),
                        std::make_tuple("./user}file.txt", false),
                        std::make_tuple("./user[file.txt", false),
                        std::make_tuple("./user]file.txt", false),
                        std::make_tuple("./user|file.txt", false),
                        std::make_tuple("./user\\file.txt", false),
                        std::make_tuple("./user/file.txt", false),
                        std::make_tuple("./user/file.txt", false),
                        // Unicode characters
                        std::make_tuple("./user/文件.txt", false),
                        std::make_tuple("./user/файл.txt", false),
                        std::make_tuple("./user/ملف.txt", false),
                        std::make_tuple("./user/ファイル.txt", false),
                        std::make_tuple("./user/파일.txt", false),
                        // Combined slashes
                        std::make_tuple("./home//user", false),
                        std::make_tuple("./home///user", false),
                        std::make_tuple("./home////user", false),
                        std::make_tuple("dir//file.txt", false),
                        std::make_tuple("./home/user///file.txt", false),
                        std::make_tuple("./home/user////file.txt", false),
                        std::make_tuple("./home/user/dir//file.txt", false),
                        std::make_tuple("./home/user/dir///file.txt", false),
                        std::make_tuple("./home/user/dir////file.txt", false),
                        std::make_tuple("dir/subdir//file.txt", false),
                        std::make_tuple("./home/user/dir/subdir///file.txt", false),
                        std::make_tuple("./home/user/dir/subdir////file.txt", false),
                        // More diverse relative paths
                        std::make_tuple("project/src/main.cpp", false),
                        std::make_tuple("./project/src/../include/header.h", false),
                        std::make_tuple("docs/./README.md", false),
                        std::make_tuple("build//output.log", false),
                        std::make_tuple("scripts/../bin/run.sh", false),
                        std::make_tuple("assets/images/./logo.png", false),
                        std::make_tuple("temp//cache.dat", false),
                        std::make_tuple("config/./../config.yaml", false),
                        std::make_tuple("lib/../../lib/libexample.so", false),
                        std::make_tuple("test/./unit/test_example.cpp", false),
                            std::make_tuple("/home/user/文件.txt/ملف/../../..", false),
                            std::make_tuple("/home/user/文件/ملف//txt//..", false)

                    )
                );
        } // namespace Path
    } // namespace fs
} //namespace test