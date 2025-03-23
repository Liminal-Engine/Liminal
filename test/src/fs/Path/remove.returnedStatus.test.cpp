/**
 * @file remove.returnedStatus.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-10-06
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
            class FSPathRemoveReturnedStatusMethod : public ::testing::Test {
                protected:
                    std::string _rootPath;
                    void create(void) noexcept {
                        this->_rootPath = "../../test/assets/fsRemoveReturnedStatus" + ::test::Helper::generateUID() + "/";
                        ::test::fs::Path::Helper::createTestFiles(this->_rootPath);
                    }

                    void destroy(void) noexcept {
                        ::test::fs::Path::Helper::deleteTestFiles(this->_rootPath);
                    }

                    void test_eq(
                        const std::string &pathAsString,
                        const bool &recursirve,
                        const ::fs::Status &expectedStatus
                    ) const noexcept {
                        const ::fs::Path instance(this->_rootPath + "/" + pathAsString);

                        EXPECT_EQ(instance.remove(recursirve), expectedStatus);
                    }
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingValue1) {
                create();
                test_eq("root_file", false, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingValue2) {
                create();
                test_eq("aaa/bbb/ccc/file", false, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingValueInRecursive1) {
                create();
                test_eq("root_file", true, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingValueInRecursive2) {
                create();
                test_eq("aaa/bbb/ccc/file", true, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingValueInRecursive3) {
                create();
                test_eq("aaa/bbb/ccc/", true, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingValueInRecursive4) {
                create();
                test_eq("aaa/bbb/", true, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingValueInRecursive5) {
                create();
                test_eq("aaa/", true, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingValueInRecursive6) {
                create();
                test_eq("aaa/", true, ::fs::Status::OK);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingNonEmptyDirectory1) {
                create();
                test_eq("aaa/", false, ::fs::Status::E_REMOVE);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingNonEmptyDirectory2) {
                create();
                test_eq("aaa/bbb", false, ::fs::Status::E_REMOVE);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenExistingNonEmptyDirectory3) {
                create();
                test_eq("aaa/bbb/ccc", false, ::fs::Status::E_REMOVE);
                destroy();
            };


            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenUnexistingValue1) {
                create();
                test_eq("aaa/bbb/ddd", true, ::fs::Status::E_PATH_NO_TARGET);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenUnexistingValue2) {
                create();
                test_eq("/eeeaaa/bbb/ddd", true, ::fs::Status::E_PATH_NO_TARGET);
                destroy();
            };
            
            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenUnexistingValue3) {
                create();
                test_eq("aaaa/bbb/ddd", true, ::fs::Status::E_PATH_NO_TARGET);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenUnexistingValue4) {
                create();
                test_eq("eztret", false, ::fs::Status::E_PATH_NO_TARGET);
                destroy();
            };

            TEST_F(FSPathRemoveReturnedStatusMethod, WhenGivenUnexistingValue5) {
                create();
                test_eq("rooot_file", true, ::fs::Status::E_PATH_NO_TARGET);
                destroy();
            };

        } // namespace test
    } // namespace fs
} // namespace test
