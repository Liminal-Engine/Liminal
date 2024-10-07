/**
 * @file remove.exists.test.cpp
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
            class FSPathRemoveExistsMethod : public ::testing::Test {
                protected:
                    std::string _rootPath;
                    void create(void) noexcept {
                        this->_rootPath = "../../test/assets/fsRemoveReturnedStatus" + ::test::fs::Path::Helper::generateUID() + "/";
                        ::test::fs::Path::Helper::createTestFiles(this->_rootPath);
                    }

                    void destroy(void) noexcept {
                        ::test::fs::Path::Helper::deleteTestFiles(this->_rootPath);
                    }

                    void test_eq(
                        const std::string &pathAsString,
                        const bool &recursirve,
                        const bool &shouldExists
                    ) const noexcept {
                        const ::fs::Path instance(this->_rootPath + "/" + pathAsString);

                        instance.remove(recursirve);
                        EXPECT_EQ(std::filesystem::exists(instance.asStr()), shouldExists);
                    }
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingValue1) {
                create();
                test_eq("root_file", false, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingValue2) {
                create();
                test_eq("aaa/bbb/ccc/file", false, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingValueInRecursive1) {
                create();
                test_eq("root_file", true, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingValueInRecursive2) {
                create();
                test_eq("aaa/bbb/ccc/file", true, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingValueInRecursive3) {
                create();
                test_eq("aaa/bbb/ccc/", true, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingValueInRecursive4) {
                create();
                test_eq("aaa/bbb/", true, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingValueInRecursive5) {
                create();
                test_eq("aaa/", true, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingValueInRecursive6) {
                create();
                test_eq("aaa/", true, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingNonEmptyDirectory1) {
                create();
                test_eq("aaa/", false, true);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingNonEmptyDirectory2) {
                create();
                test_eq("aaa/bbb", false, true);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenExistingNonEmptyDirectory3) {
                create();
                test_eq("aaa/bbb/ccc", false, true);
                destroy();
            };


            TEST_F(FSPathRemoveExistsMethod, WhenGivenUnexistingValue1) {
                create();
                test_eq("aaa/bbb/ddd", true, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenUnexistingValue2) {
                create();
                test_eq("/eeeaaa/bbb/ddd", true, false);
                destroy();
            };
            
            TEST_F(FSPathRemoveExistsMethod, WhenGivenUnexistingValue3) {
                create();
                test_eq("aaaa/bbb/ddd", true, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenUnexistingValue4) {
                create();
                test_eq("eztret", false, false);
                destroy();
            };

            TEST_F(FSPathRemoveExistsMethod, WhenGivenUnexistingValue5) {
                create();
                test_eq("rooot_file", true, false);
                destroy();
            };

        } // namespace test
    } // namespace fs
} // namespace test
