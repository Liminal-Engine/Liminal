/**
 * @file clean.newPath.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-05
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <fs/Path.hpp>

#include "test/fs/Path/Helper.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <tuple>
#include <string>
#include <utility>
#include <optional>
#include <filesystem>

namespace test {
    namespace fs {
        namespace Path {
            using FSPathCleanNewPathStrParam = std::tuple<
                std::string, // path to build instances from, if has no value, constructor fs::Path{} will be used
                std::string // expected new path str
            >;

            class FSPathCleanNewPathStrMethod : public ::testing::TestWithParam<FSPathCleanNewPathStrParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathCleanNewPathStrMethod(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {
                    }
            };

            TEST_P(FSPathCleanNewPathStrMethod, EqualGivenStringPath) {
                for (::fs::Path &_instance : _instances) {
                    _instance.clean();
                    EXPECT_EQ(_instance.toStr(), std::get<1>(GetParam()));
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenInstanciatingVariousTypeOfPath,
                FSPathCleanNewPathStrMethod,
                testing::Values(
                    std::make_tuple("/tmp/../usr", "/usr"),
                    std::make_tuple("/tmp/../././usr", "/usr"),
                    std::make_tuple("../././usr", "../usr"),
                    std::make_tuple("/usr/aaa/bbb/.././ccc/../../ddd", "/usr/ddd"),
                    std::make_tuple("../usr/aaa/bbb/.././../.././ccc", "../ccc"),
                    std::make_tuple("../usr/aaa/bbb/ooo/ddd", "../usr/aaa/bbb/ooo/ddd"),
                    std::make_tuple("/", "/"),
                    std::make_tuple("////////////////////////////////////////////////", "/"),
                    std::make_tuple("", ""),
                    std::make_tuple("/path/with spaces", "/path/with spaces"),
                    std::make_tuple("/very/..//long/path/" + std::string(PATH_MAX, 'a'), "/long/path/" + std::string(PATH_MAX, 'a')),
                    std::make_tuple("/path//with/multiple///slashes", "/path/with/multiple/slashes"),
                    std::make_tuple("./relative/path", "relative/path"),
                    std::make_tuple("/absolute/path/with/./relative/part", "/absolute/path/with/relative/part"),
                    std::make_tuple("/nonexistent/path", "/nonexistent/path"),
                    std::make_tuple("/path/without/permissions", "/path/without/permissions"),
                    std::make_tuple("/absolute/path/with/../relative/part", "/absolute/path/relative/part"),
                    std::make_tuple("/path/with/symlink", "/path/with/symlink"),
                    std::make_tuple("/usr/../../../../../", "/"),
                    std::make_tuple("/", "/"),
                    std::make_tuple("/usr/./../.././././../../../", "/"),
                    std::make_tuple("/usr/local/bin/../lib", "/usr/local/lib"),
                    std::make_tuple("//usr///local/////bin//../lib", "/usr/local/lib"),
                    std::make_tuple("/usr/\x10/local/bin", "/usr/\x10/local/bin"), // Unprintable character
                    std::make_tuple("/usr/local/\xFF/bin", "/usr/local/\xFF/bin"), // Unprintable character
                    std::make_tuple("/usr/" + std::string(1000, 'a') + "/bin", "/usr/" + std::string(1000, 'a') + "/bin"),
                    std::make_tuple("usr/local/bin/../../../file", "file"),
                    std::make_tuple("/usr/local/bin/../../.././file", "/file"),
                    std::make_tuple("/UsR/LoCaL/bIn", "/UsR/LoCaL/bIn"),
                    std::make_tuple("/usr/local/bin/../../", "/usr"),
                    std::make_tuple("/usr/local/bin/../../../..", "/"),
                    std::make_tuple("\\usr\\local\\bin", "\\usr\\local\\bin"),
                    std::make_tuple("\\usr\\local\\bin\\.\\..\\lib", "\\usr\\local\\bin\\.\\..\\lib"),
                    std::make_tuple("/usr/local/漢字/文件.txt", "/usr/local/漢字/文件.txt"),
                    std::make_tuple("usr/local/My Documents/My File.txt", "usr/local/My Documents/My File.txt"),
                    std::make_tuple("", ""),
                    std::make_tuple("//////", "/"),
                    std::make_tuple(".", "."),
                    std::make_tuple("..", ".."),
                    std::make_tuple("........", "........"),
                    std::make_tuple("./.......", "......."),
                    std::make_tuple("/u", "/u"),
                    std::make_tuple("////usr/local/bin", "/usr/local/bin"),
                    std::make_tuple("/usr/local/bin/////", "/usr/local/bin"),
                    std::make_tuple("////usr/local/bin/////", "/usr/local/bin")
                )
            );
        } // namespace Path
    } // namespace fs
} // namespace test
