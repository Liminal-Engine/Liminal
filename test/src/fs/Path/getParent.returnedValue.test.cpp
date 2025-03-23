/**
 * @file getParent.returnedValue.test.cpp
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
#include "test/Helper.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <tuple>
#include <string>
#include <utility>
#include <optional>
#include <filesystem>
#include <stdio.h>
#include <unistd.h>


#include <fstream>
#include <iostream>
#include <time.h>

namespace test {
    namespace fs {
        namespace test {
            class FSPathGetParentReturnedValueMethod : public ::testing::Test {
                protected:
                    std::string _rootPath;
                    void create(void) noexcept {
                        this->_rootPath = "../../test/assets/fsGetParent" + ::test::Helper::generateUID() + "/";
                        ::test::fs::Path::Helper::createTestFiles(this->_rootPath);
                    }

                    void destroy(void) noexcept {
                        ::test::fs::Path::Helper::deleteTestFiles(this->_rootPath);
                    }

                    void test_eq(
                        const std::string &pathAsString,
                        const ::fs::Permission &perms,
                        const bool &recursive,
                        const ::fs::Status &expectedStatus
                    ) const noexcept {
                        std::vector<::fs::Path> _instances = ::test::fs::Path::Helper::create(_rootPath + "/" + pathAsString);

                        for (const ::fs::Path &instance : _instances) {
                            ::usleep(50 * 1000);
                            EXPECT_EQ(instance.updatePermissions(perms, recursive), expectedStatus);
                            ::usleep(50 * 1000);
                            instance.updatePermissions(0777, recursive); // Fix path perms for deletion
                            ::usleep(50 * 1000);
                        }
                    }
            };

            TEST_F(FSPathGetParentReturnedValueMethod, ShouldMatchExpectedValue1) {
                create();
                test_eq("root_file", ::fs::Permission(0677), false, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathGetParentReturnedValueMethod, ShouldMatchExpectedValue1Recursive) {
                create();
                test_eq("root_file", ::fs::Permission(0677), true, ::fs::Status::OK);
                destroy();
            };


            TEST_F(FSPathGetParentReturnedValueMethod, ShouldMatchExpectedValue2) {
                create();
                test_eq("aaa/bbb", ::fs::Permission(0677), false, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathGetParentReturnedValueMethod, ShouldMatchExpectedValue2Recursive) {
                create();
                test_eq("aaa/bbb", ::fs::Permission(0677), true, ::fs::Status::OK);
                destroy();
            };

             TEST_F(FSPathGetParentReturnedValueMethod, ShouldMatchExpectedValue3) {
                create();
                test_eq("aaa", ::fs::Permission(0777), false, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathGetParentReturnedValueMethod, ShouldMatchExpectedValue3Recursive) {
                create();
                test_eq("aaa", ::fs::Permission(0777), true, ::fs::Status::OK);
                destroy();
            };
        } // namespace test
    } // namespace fs
} // namespace test
