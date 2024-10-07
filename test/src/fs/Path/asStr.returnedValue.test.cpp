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
            using FSPathAsStrReturnedValueParam = std::tuple <
                std::string, // string to build path from
                std::string // expected result
            >;

            class FSPathAsStrReturnedValueMethod : public ::testing::TestWithParam<FSPathAsStrReturnedValueParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathAsStrReturnedValueMethod(void) :
                    _instances(::test::fs::Path::Helper::create(std::get<0>(GetParam())))
                    {}
            };

            TEST_P(FSPathAsStrReturnedValueMethod, ReturnsGivenValue) {
                std::string expectedReturnedValue(std::get<1>(GetParam()));

                for (const ::fs::Path &instance : _instances) {
                    EXPECT_EQ(instance.asStr(), expectedReturnedValue);
                }
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenAbsolutePaths,
                FSPathAsStrReturnedValueMethod,
                testing::Values(
                    std::make_tuple("/home/user", "/home/user"),
                    std::make_tuple("/home/user/../user2", "/home/user/../user2"),
                    std::make_tuple("./relative/path", "./relative/path"),
                    std::make_tuple("/home/user/./file.txt", "/home/user/./file.txt"),
                    std::make_tuple("/home/user//file.txt", "/home/user/file.txt"),
                    std::make_tuple("/home/user/dir/", "/home/user/dir"),
                    std::make_tuple("/home/user/dir/../file.txt", "/home/user/dir/../file.txt"),
                    std::make_tuple("/home/user/dir/./file.txt", "/home/user/dir/./file.txt"),
                    std::make_tuple("/home/user/dir//file.txt", "/home/user/dir/file.txt"),
                    std::make_tuple("/home/user/dir/../../file.txt", "/home/user/dir/../../file.txt"),
                    std::make_tuple("/home/user/dir/subdir/../../../../../../../../../../../../file.txt", "/home/user/dir/subdir/../../../../../../../../../../../../file.txt"),
                    std::make_tuple("/home/user/dir/subdir/../../../../../../../../../../../../file.txt", "/home/user/dir/subdir/../../../../../../../../../../../../file.txt"),
                    // Special characters
                    std::make_tuple("/home/user with spaces/file.txt", "/home/user with spaces/file.txt"),
                    std::make_tuple("/home/user@domain/file.txt", "/home/user@domain/file.txt"),
                    std::make_tuple("/home/user#file.txt", "/home/user#file.txt"),
                    std::make_tuple("/home/user$file.txt", "/home/user$file.txt"),
                    std::make_tuple("/home/user%file.txt", "/home/user%file.txt"),
                    std::make_tuple("/home/user^file.txt", "/home/user^file.txt"),
                    std::make_tuple("/home/user&file.txt", "/home/user&file.txt"),
                    std::make_tuple("/home/user*file.txt", "/home/user*file.txt"),
                    std::make_tuple("/home/user(file.txt", "/home/user(file.txt"),
                    std::make_tuple("/home/user)file.txt", "/home/user)file.txt"),
                    std::make_tuple("/home/user+file.txt", "/home/user+file.txt"),
                    std::make_tuple("/home/user,file.txt", "/home/user,file.txt"),
                    std::make_tuple("/home/user;file.txt", "/home/user;file.txt"),
                    std::make_tuple("/home/user=file.txt", "/home/user=file.txt"),
                    std::make_tuple("/home/user'file.txt", "/home/user'file.txt"),
                    std::make_tuple("/home/user\"file.txt", "/home/user\"file.txt"),
                    std::make_tuple("/home/user`file.txt", "/home/user`file.txt"),
                    std::make_tuple("/home/user~file.txt", "/home/user~file.txt"),
                    std::make_tuple("/home/user!file.txt", "/home/user!file.txt"),
                    std::make_tuple("/home/user{file.txt", "/home/user{file.txt"),
                    std::make_tuple("/home/user}file.txt", "/home/user}file.txt"),
                    std::make_tuple("/home/user[file.txt", "/home/user[file.txt"),
                    std::make_tuple("/home/user]file.txt", "/home/user]file.txt"),
                    std::make_tuple("/home/user|file.txt", "/home/user|file.txt"),
                    std::make_tuple("/home/user\\file.txt", "/home/user\\file.txt"),
                    std::make_tuple("/home/user/file.txt", "/home/user/file.txt"),
                    std::make_tuple("/home/user/file.txt", "/home/user/file.txt"),
                    // Unicode characters
                    std::make_tuple("/home/user/文件.txt", "/home/user/文件.txt"),
                    std::make_tuple("/home/user/файл.txt", "/home/user/файл.txt"),
                    std::make_tuple("/home/user/ملف.txt", "/home/user/ملف.txt"),
                    std::make_tuple("/home/user/ファイル.txt", "/home/user/ファイル.txt"),
                    std::make_tuple("/home/user/파일.txt", "/home/user/파일.txt")
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenRelativePaths,
                FSPathAsStrReturnedValueMethod,
                testing::Values(
                    std::make_tuple("relative/path", "relative/path"),
                    std::make_tuple("./relative/path", "./relative/path"),
                    std::make_tuple("../relative/path", "../relative/path"),
                    std::make_tuple("relative/./path", "relative/./path"),
                    std::make_tuple("relative//path", "relative/path"),
                    std::make_tuple("relative/path/..", "relative/path/.."),
                    std::make_tuple("relative/path/../file.txt", "relative/path/../file.txt"),
                    std::make_tuple("relative/path/./file.txt", "relative/path/./file.txt"),
                    std::make_tuple("relative/path//file.txt", "relative/path/file.txt"),
                    std::make_tuple("relative/path/../../file.txt", "relative/path/../../file.txt"),
                    // Special characters
                    std::make_tuple("relative/path with spaces/file.txt", "relative/path with spaces/file.txt"),
                    std::make_tuple("relative/user@domain/file.txt", "relative/user@domain/file.txt"),
                    std::make_tuple("relative/user#file.txt", "relative/user#file.txt"),
                    std::make_tuple("relative/user$file.txt", "relative/user$file.txt"),
                    std::make_tuple("relative/user%file.txt", "relative/user%file.txt"),
                    std::make_tuple("relative/user^file.txt", "relative/user^file.txt"),
                    std::make_tuple("relative/user&file.txt", "relative/user&file.txt"),
                    std::make_tuple("relative/user*file.txt", "relative/user*file.txt"),
                    std::make_tuple("relative/user(file.txt", "relative/user(file.txt"),
                    std::make_tuple("relative/user)file.txt", "relative/user)file.txt"),
                    std::make_tuple("relative/user+file.txt", "relative/user+file.txt"),
                    std::make_tuple("relative/user,file.txt", "relative/user,file.txt"),
                    std::make_tuple("relative/user;file.txt", "relative/user;file.txt"),
                    std::make_tuple("relative/user=file.txt", "relative/user=file.txt"),
                    std::make_tuple("relative/user'file.txt", "relative/user'file.txt"),
                    std::make_tuple("relative/user\"file.txt", "relative/user\"file.txt"),
                    std::make_tuple("relative/user`file.txt", "relative/user`file.txt"),
                    std::make_tuple("relative/user~file.txt", "relative/user~file.txt"),
                    std::make_tuple("relative/user!file.txt", "relative/user!file.txt"),
                    std::make_tuple("relative/user{file.txt", "relative/user{file.txt"),
                    std::make_tuple("relative/user}file.txt", "relative/user}file.txt"),
                    std::make_tuple("relative/user[file.txt", "relative/user[file.txt"),
                    std::make_tuple("relative/user]file.txt", "relative/user]file.txt"),
                    std::make_tuple("relative/user|file.txt", "relative/user|file.txt"),
                    std::make_tuple("relative/user\\file.txt", "relative/user\\file.txt"),
                    std::make_tuple("relative/user/file.txt", "relative/user/file.txt"),
                    std::make_tuple("relative/user/file.txt", "relative/user/file.txt"),
                    // Unicode characters
                    std::make_tuple("relative/user/文件.txt", "relative/user/文件.txt"),
                    std::make_tuple("relative/user/файл.txt", "relative/user/файл.txt"),
                    std::make_tuple("relative/user/ملف.txt", "relative/user/ملف.txt"),
                    std::make_tuple("relative/user/ファイル.txt", "relative/user/ファイル.txt"),
                    std::make_tuple("relative/user/파일.txt", "relative/user/파일.txt")
                )
            );

        } // namespace Path
    } // namespace fs
} //namespace test