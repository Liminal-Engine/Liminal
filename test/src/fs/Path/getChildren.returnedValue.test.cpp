/**
 * @file getChildren.returnedValue.test.cpp
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
            class FSPathGetChildrenReturnedValueMethod : public ::testing::Test {
                protected:
                    std::string _rootPath;
                    void create(void) noexcept {
                        this->_rootPath = "../../test/assets/fsGetChildren" + ::test::fs::Path::Helper::generateUID() + "/";
                        ::test::fs::Path::Helper::createTestFiles(this->_rootPath);
                    }

                    void destroy(void) noexcept {
                        ::test::fs::Path::Helper::deleteTestFiles(this->_rootPath);
                    }

                    void test_eq(
                        const std::string &pathAsString,
                        const std::vector<::fs::Path> &expectedResult
                    ) const noexcept {
                        std::vector<::fs::Path> _instances = ::test::fs::Path::Helper::create(_rootPath + "/" + pathAsString);
                        std::vector<::fs::Path> realExpectedResult{};
                        
                        for (const ::fs::Path &expectedPath : expectedResult) {
                            realExpectedResult.push_back(::fs::Path(_rootPath + "/" + pathAsString + "/" + expectedPath.asStr()));
                        }

                        for (const ::fs::Path &instance : _instances) {
                            EXPECT_EQ(instance.getChildren(), realExpectedResult);
                        }
                    }
            };

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenRealPath1) {
                create();
                test_eq("./", std::vector<::fs::Path>{ ::fs::Path("aaa"), ::fs::Path("root_file") });
                destroy();
            };

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenRealPath2) {
                create();
                test_eq("", std::vector<::fs::Path>{ ::fs::Path("aaa"), ::fs::Path("root_file") });
                destroy();
            };

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenRealPath3) {
                create();
                test_eq("aaa", std::vector<::fs::Path>{ ::fs::Path("bbb") });
                destroy();
            };

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenRealPath4) {
                create();
                test_eq("aaa/bbb", std::vector<::fs::Path>{ ::fs::Path("ccc") });
                destroy();
            };

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenRealPath5) {
                create();
                test_eq("aaa/bbb/ccc", std::vector<::fs::Path>{ ::fs::Path("file") });
                destroy();
            };

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenNonRealPath1) {
                create();
                test_eq("aaa/bbb/ccccccc", std::vector<::fs::Path>{  });
                destroy();
            };

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenNonRealPath2) {
                create();
                test_eq("non/existent/path", std::vector<::fs::Path>{  });
                destroy();
            }

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenNonRealPath3) {
                create();
                test_eq("invalid//path//name", std::vector<::fs::Path>{  });
                destroy();
            }

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenNonRealPath4) {
                create();
                test_eq("path/with/special/characters/!@#$%^&*()", std::vector<::fs::Path>{  });
                destroy();
            }

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenNonRealPath5) {
                create();
                test_eq("another\\invalid\\path", std::vector<::fs::Path>{  });
                destroy();
            }

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenNonRealPath6) {
                create();
                test_eq("yet/another/invalid/path/with/../dots", std::vector<::fs::Path>{  });
                destroy();
            }

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenNonRealPath7) {
                create();
                test_eq("path/with/space in name", std::vector<::fs::Path>{  });
                destroy();
            }

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenNonRealPath8) {
                create();
                test_eq("path/with/tab\tin name", std::vector<::fs::Path>{  });
                destroy();
            }

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenNonRealPath9) {
                create();
                test_eq("path/with/newline\nin name", std::vector<::fs::Path>{  });
                destroy();
            }

            TEST_F(FSPathGetChildrenReturnedValueMethod, WhenGivenNonRealPath10) {
                create();
                test_eq("path/with/very/long/name/that/keeps/going/on/and/on/and/on/and/on/and/on/and/on/and/on", std::vector<::fs::Path>{  });
                destroy();
            }

        } // namespace test
    } // namespace fs
} // namespace test
