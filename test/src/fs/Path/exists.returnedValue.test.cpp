/**
 * @file exists.returnedValue.test.cpp
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
            class FSPathExistsReturnedValueMethod : public ::testing::Test {
                protected:
                    std::string _rootPath;
                    void create(void) noexcept {
                        this->_rootPath = "../../test/assets/fsPathExists" + ::test::fs::Path::Helper::generateUID() + "/";
                        ::test::fs::Path::Helper::createTestFiles(this->_rootPath);
                    }

                    void destroy(void) noexcept {
                        ::test::fs::Path::Helper::deleteTestFiles(this->_rootPath);
                    }

                    void test_eq(
                        const std::string &pathAsString,
                        const bool &expectedResult
                    ) const noexcept {
                        std::vector<::fs::Path> _instances = ::test::fs::Path::Helper::create(_rootPath + "/" + pathAsString);
                        
                        for (const ::fs::Path &instance : _instances) {
                            EXPECT_EQ(instance.exists(), expectedResult);
                        }
                    }
            };

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenRealPath1) {
                create();
                test_eq("./", true);
                destroy();
            };

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenRealPath2) {
                create();
                test_eq("", true);
                destroy();
            };

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenRealPath3) {
                create();
                test_eq("aaa", true);
                destroy();
            };

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenRealPath4) {
                create();
                test_eq("aaa/bbb", true);
                destroy();
            };

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenRealPath5) {
                create();
                test_eq("aaa/bbb/ccc", true);
                destroy();
            };

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenNonRealPath1) {
                create();
                test_eq("aaa/bbb/ccccccc", false);
                destroy();
            };

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenNonRealPath2) {
                create();
                test_eq("non/existent/path", false);
                destroy();
            }

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenNonRealPath3) {
                create();
                test_eq("invalid//path//name", false);
                destroy();
            }

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenNonRealPath4) {
                create();
                test_eq("path/with/special/characters/!@#$%^&*()", false);
                destroy();
            }

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenNonRealPath5) {
                create();
                test_eq("another\\invalid\\path", false);
                destroy();
            }

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenNonRealPath6) {
                create();
                test_eq("yet/another/invalid/path/with/../dots", false);
                destroy();
            }

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenNonRealPath7) {
                create();
                test_eq("path/with/space in name", false);
                destroy();
            }

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenNonRealPath8) {
                create();
                test_eq("path/with/tab\tin name", false);
                destroy();
            }

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenNonRealPath9) {
                create();
                test_eq("path/with/newline\nin name", false);
                destroy();
            }

            TEST_F(FSPathExistsReturnedValueMethod, WhenGivenNonRealPath10) {
                create();
                test_eq("path/with/very/long/name/that/keeps/going/on/and/on/and/on/and/on/and/on/and/on/and/on", false);
                destroy();
            }

        } // namespace test
    } // namespace fs
} // namespace test
