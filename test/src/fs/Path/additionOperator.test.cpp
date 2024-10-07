/**
 * @file additionOperator.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-07
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
#include <filesystem>

namespace test {
    namespace fs {
        namespace Path {

            using FSPathAdditionOperatorParam = std::tuple<
                std::string, // path1
                std::string, // path2
                std::string // expected path
            >;
            class FSPathAdditionOperator : public ::testing::TestWithParam<FSPathAdditionOperatorParam> {
                protected:
                    std::vector<::fs::Path> _leftInstances;
                    std::vector<::fs::Path> _rightInstances;

                    FSPathAdditionOperator(void) :
                    _leftInstances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))},
                    _rightInstances{::test::fs::Path::Helper::create(std::get<1>(GetParam()))}
                    {}
            };

            TEST_P(FSPathAdditionOperator, GivesExpectingPath) {                
                for (const ::fs::Path &leftInstance : _leftInstances) {                                        
                    for (const ::fs::Path &rightInstance : _rightInstances) {                                        
                        EXPECT_EQ(leftInstance + rightInstance, std::get<2>(GetParam()));
                    }
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenVariousPath,
                FSPathAdditionOperator,
                testing::Values(
                    // Absolute path addition
                    std::make_tuple("/home/user", "documents", "/home/user/documents"),
                    std::make_tuple("/var/log", "syslog", "/var/log/syslog"),
                    std::make_tuple("/usr/local", "bin", "/usr/local/bin"),
                    std::make_tuple("/etc", "nginx", "/etc/nginx"),
                    std::make_tuple("/tmp", "tempfile", "/tmp/tempfile"),
                    std::make_tuple("/path/to", ".", "/path/to/."),
                    std::make_tuple("/path/to", "..", "/path/to/.."),
                    std::make_tuple("/path/to", "../another", "/path/to/../another"),
                    std::make_tuple("/path/to", "./another", "/path/to/./another"),
                    std::make_tuple("path/to", ".", "path/to/."),
                    std::make_tuple("path/to", "..", "path/to/.."),
                    std::make_tuple("path/to", "../another", "path/to/../another"),
                    std::make_tuple("path/to", "./another", "path/to/./another"),
                    std::make_tuple("/path/to", "dir/with spaces", "/path/to/dir/with spaces"),
                    std::make_tuple("./path/to", "dir/with spaces", "./path/to/dir/with spaces"),
                    std::make_tuple("/path/to", "dir/with_special-characters!@#", "/path/to/dir/with_special-characters!@#"),
                    std::make_tuple("path/to", "dir/with_special-characters!@#", "path/to/dir/with_special-characters!@#"),
                    std::make_tuple("./path/to", "dir/with_special-characters!@#", "./path/to/dir/with_special-characters!@#"),
                    std::make_tuple("../path/to", "dir/with_special-characters!@#", "../path/to/dir/with_special-characters!@#"),
                    std::make_tuple("/path/to", "dir/with/multiple/levels", "/path/to/dir/with/multiple/levels"),
                    std::make_tuple("path/to", "dir/with/multiple/levels", "path/to/dir/with/multiple/levels"),
                    std::make_tuple("./path/to", "dir/with/multiple/levels", "./path/to/dir/with/multiple/levels"),
                    std::make_tuple("path/to", "dir/with/../parent", "path/to/dir/with/../parent"),
                    std::make_tuple("/path/to", "/dir/with/../parent", "/path/to/dir/with/../parent"),
                    std::make_tuple(".path/to", "/dir/with/./current", ".path/to//dir/with/./current"),
                    std::make_tuple("/path/to/dir", "subdir/../file", "/path/to/dir/subdir/../file"),
                    std::make_tuple("/path/to/dir", "./subdir/./file", "/path/to/dir/./subdir/./file"),
                    std::make_tuple("path/to/dir", "subdir/../file", "path/to/dir/subdir/../file"),
                    std::make_tuple("path/to/dir", "./subdir/./file", "path/to/dir/./subdir/./file"),
                    std::make_tuple("/path/to/dir", "../to/another/dir", "/path/to/dir/../to/another/dir"),
                    std::make_tuple("path/to/dir", "../to/another/dir", "path/to/dir/../to/another/dir"),
                    std::make_tuple("/path/to/dir", "./to/./another/./dir", "/path/to/dir/./to/./another/./dir"),
                    std::make_tuple("path/to/dir", "./to/./another/./dir", "path/to/dir/./to/./another/./dir"),
                    std::make_tuple("/path/to/dir", "subdir/with/../special/./characters", "/path/to/dir/subdir/with/../special/./characters"),
                    std::make_tuple("path/to/dir", "subdir/with/../special/./characters", "path/to/dir/subdir/with/../special/./characters"),
                    std::make_tuple("", "/subdir/with/../special/./characters", "/subdir/with/../special/./characters"),
                    std::make_tuple("path/to/dir", "/subdir/with/../special/./characters", "path/to/dir/subdir/with/../special/./characters")
                )
            );
        } // namespace Path
    } // namespace fs
} // namespace test
