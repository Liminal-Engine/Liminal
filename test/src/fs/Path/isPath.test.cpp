/**
 * @file isPath.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-07
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
            using FSPathIsPathReturnedValueParam = std::tuple <
                std::string, // string to build path from
                bool // expected result
            >;

            class FSPathIsPathReturnedValueMethod : public ::testing::TestWithParam<FSPathIsPathReturnedValueParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathIsPathReturnedValueMethod(void) :
                    _instances(::test::fs::Path::Helper::create(std::get<0>(GetParam())))
                    {}
            };

            TEST_P(FSPathIsPathReturnedValueMethod, ReturnsGivenValue) {
                EXPECT_EQ(::fs::Path::isPath(std::get<0>(GetParam())), std::get<1>(GetParam()));
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenIsPath,
                FSPathIsPathReturnedValueMethod,
                testing::Values(
                    std::make_tuple("/home/user", true),
                    std::make_tuple("C:\\Program Files", true),
                    std::make_tuple("/usr/local/bin", true),
                    std::make_tuple("/tmp", true),
                    std::make_tuple("/var/log", true),
                    std::make_tuple("/etc/hosts", true),
                    std::make_tuple("/home/user/.config", true),
                    std::make_tuple("/home/user/Documents", true),
                    std::make_tuple("/home/user/Downloads", true),
                    std::make_tuple("/home/user/Music", true),
                    std::make_tuple("/home/user/Pictures", true),
                    std::make_tuple("/home/user/Videos", true),
                    std::make_tuple("/home/user/workspace/project", true),
                    std::make_tuple("/home/user/workspace/project/src", true),
                    std::make_tuple("/home/user/workspace/project/build", true),
                    std::make_tuple("not/a/path", true),
                    std::make_tuple("C:Program Files", true),
                    std::make_tuple("home/user", true),
                    std::make_tuple("usr/local/bin", true),
                    std::make_tuple("tmp", true),
                    std::make_tuple("var/log", true),
                    std::make_tuple("etc/hosts", true),
                    std::make_tuple("home/user/.config", true),
                    std::make_tuple("home/user/Documents", true),
                    std::make_tuple("home/user/Downloads", true),
                    std::make_tuple("home/user/Music", true),
                    std::make_tuple("home/user/Pictures", true),
                    std::make_tuple("home/user/Videos", true),
                    std::make_tuple("home/user/workspace/project", true),
                    std::make_tuple("home/user/workspace/project/src", true),
                    std::make_tuple("home/user/workspace/project/build", true),
                    std::make_tuple(" ", true),
                    std::make_tuple("..", true),
                    std::make_tuple(".", true),
                    std::make_tuple("~", true),
                    std::make_tuple("C:\\", true),
                    std::make_tuple("/", true)
                )
            );

                INSTANTIATE_TEST_SUITE_P(
                    WhenIsNotPath,
                    FSPathIsPathReturnedValueMethod,
                    testing::Values(
                        std::make_tuple("", false),
                        std::make_tuple("\0", false),
                        std::make_tuple("\0abc", false)
                    )
                );
        } // namespace Path
    } // namespace fs
} //namespace test