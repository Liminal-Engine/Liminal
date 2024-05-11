/**
 * @file clean.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-05
 * 
 * @copyright Copyright (c) 2024
 * 
 * 
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
            using FSPathCleanReturnedStatusParam = std::tuple<
                std::string, // path to build instances from, if has no value, constructor fs::Path{} will be used
                ::fs::Status // expected return status
            >;

            class FSPathCleanReturnedStatusMethod : public ::testing::TestWithParam<FSPathCleanReturnedStatusParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathCleanReturnedStatusMethod(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {
                    }
            };

            TEST_P(FSPathCleanReturnedStatusMethod, ReturnGivenStatusAndProduceGivenPath) {
                for (::fs::Path &_instance : _instances)
                    EXPECT_EQ(_instance.clean(), std::get<1>(GetParam()));
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenInstanciatingVariousTypeOfPath,
                FSPathCleanReturnedStatusMethod,
                testing::Values(
                    std::make_tuple("/tmp/../usr", ::fs::Status::OK),
                    std::make_tuple("/tmp/../././usr", ::fs::Status::OK),
                    std::make_tuple("../././usr", ::fs::Status::OK),
                    std::make_tuple("/usr/aaa/bbb/.././ccc/../../ddd", ::fs::Status::OK),
                    std::make_tuple("../usr/aaa/bbb/.././../.././ccc", ::fs::Status::OK),
                    std::make_tuple("../usr/aaa/bbb/ooo/ddd", ::fs::Status::OK),
                    std::make_tuple("/", ::fs::Status::OK),
                    std::make_tuple("////////////////////////////////////////////////", ::fs::Status::OK),
                    std::make_tuple("", ::fs::Status::OK),
                    std::make_tuple("/path/with spaces", ::fs::Status::OK),
                    std::make_tuple("/very/long/path/" + std::string(PATH_MAX, 'a'), ::fs::Status::OK),
                    std::make_tuple("/path//with/multiple///slashes", ::fs::Status::OK),
                    std::make_tuple("./relative/path", ::fs::Status::OK),
                    std::make_tuple("/absolute/path/with/./relative/part", ::fs::Status::OK),
                    std::make_tuple("/nonexistent/path", ::fs::Status::OK),
                    std::make_tuple("/path/without/permissions", ::fs::Status::OK),
                    std::make_tuple("/absolute/path/with/../relative/part", ::fs::Status::OK),
                    std::make_tuple("/path/with/symlink", ::fs::Status::OK),
                    std::make_tuple("/usr/../../../../../", ::fs::Status::OK),
                    std::make_tuple("/usr/./../.././././../../../", ::fs::Status::OK),
                    std::make_tuple("usr/../../../../../../../", ::fs::Status::OK),
                    std::make_tuple("usr/./../.././././../../../../../", ::fs::Status::OK),
                    std::make_tuple("/usr/local/bin/../lib", ::fs::Status::OK),
                    std::make_tuple("/usr/local/bin/../../bin", ::fs::Status::OK),
                    std::make_tuple("//usr///local/////bin//../lib", ::fs::Status::OK),
                    std::make_tuple("///usr/local////bin/////../../bin", ::fs::Status::OK),
                    std::make_tuple("/usr/\x10/local/bin", ::fs::Status::OK), // Unprintable character
                    std::make_tuple("/usr/local/\xFF/bin", ::fs::Status::OK), // Unprintable character
                    std::make_tuple("/usr/" + std::string(1000, 'a') + "/bin", ::fs::Status::OK),
                    std::make_tuple("/" + std::string(10000, 'a'), ::fs::Status::OK),
                    std::make_tuple("usr/local/bin/../../../file", ::fs::Status::OK),
                    std::make_tuple("usr/local/bin/../../.././file", ::fs::Status::OK),
                    std::make_tuple("usr/local/bin/../../../file/.././", ::fs::Status::OK),
                    std::make_tuple("/UsR/LoCaL/bIn", ::fs::Status::OK),
                    std::make_tuple("/usr/local/bin/", ::fs::Status::OK),
                    std::make_tuple("/usr/local/bin/./././", ::fs::Status::OK),
                    std::make_tuple("/usr/local/bin/../../", ::fs::Status::OK),
                    std::make_tuple("/usr/local/bin/../../../..", ::fs::Status::OK),
                    std::make_tuple("\\usr\\local\\bin", ::fs::Status::OK),
                    std::make_tuple("\\usr\\local\\bin\\.\\..\\lib", ::fs::Status::OK),
                    std::make_tuple("/usr/local/bin\\file", ::fs::Status::OK),
                    std::make_tuple("/usr/local/漢字/文件.txt", ::fs::Status::OK),
                    std::make_tuple("/usr/local/My Documents/My File.txt", ::fs::Status::OK),
                    std::make_tuple("", ::fs::Status::OK),
                    std::make_tuple("//////", ::fs::Status::OK),
                    std::make_tuple(".", ::fs::Status::OK),
                    std::make_tuple("..", ::fs::Status::OK),
                    std::make_tuple("........", ::fs::Status::OK),
                    std::make_tuple("/u", ::fs::Status::OK),
                    std::make_tuple("////usr/local/bin", ::fs::Status::OK),
                    std::make_tuple("/usr/local/bin/////", ::fs::Status::OK),
                    std::make_tuple("////usr/local/bin/////", ::fs::Status::OK)
                )
            );
        } // namespace Path
    } // namespace fs
} // namespace test
