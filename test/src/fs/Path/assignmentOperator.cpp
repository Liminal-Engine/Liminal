/**
 * @file operator=.test.cpp
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

            using FSPathAssignmentOperatorParam = std::tuple<
                std::string, // left path
                std::string // expectede returned value
            >;
            class FSPathAssignmentOperator : public ::testing::TestWithParam<FSPathAssignmentOperatorParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathAssignmentOperator(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathAssignmentOperator, GivesExpectingPath) {
                ::fs::Path res;

                for (::fs::Path &instance : _instances) {                    
                    res = instance;
                    EXPECT_EQ(res, ::fs::Path(std::get<1>(GetParam())));
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenVariousPath,
                FSPathAssignmentOperator,
                testing::Values(
                    std::make_tuple("/tmp_fs", "/tmp_fs"),
                    std::make_tuple("/aaa/bbb", "/aaa/bbb"),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "/tmp_fs_oojopjop99---/bbb"),
                    std::make_tuple("/home/user", "/home/user"),
                    std::make_tuple("/var/log", "/var/log"),
                    std::make_tuple("/usr/local", "/usr/local"),
                    std::make_tuple("/etc", "/etc"),
                    std::make_tuple("/tmp_fs/complex-dir-name", "/tmp_fs/complex-dir-name"),
                    std::make_tuple("/tmp_fs/complex-dir-name", "/tmp_fs/complex-dir-name/subdir////..////../complex-dir-name////.///.//////../complex-dir-name///////.////"),
                    std::make_tuple("/path/to/directory", "/path/to/directory"),
                    std::make_tuple("path/to/directory", "path/to/directory"),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "/p/a/t/h/to/d/i/r/e/ctory"),
                    std::make_tuple("./var/log", "./var/log"),
                    std::make_tuple("./var/log", "var/log"),
                    std::make_tuple("./var/log", "var/log/."),
                    std::make_tuple("./var/log", "var/log/"),
                    std::make_tuple("./var/log", "var/log/../log"),
                    std::make_tuple("./../usr/share", "./../usr/share"),
                    std::make_tuple("../lib/modules", "./parent/../../lib/modules"),
                    std::make_tuple("/lib/modules", "/lib/modules"),
                    std::make_tuple("/lib/modules", "/lib/modules/"),
                    std::make_tuple("/lib/modules", "/lib/modules/././."),
                    std::make_tuple("/lib/modules", "/lib/modules/././../modules"),
                    std::make_tuple("/new/path/with/special/characters/!@#$%^&*()", "/new/path/with/special/characters/!@#$%^&*()"),
                    std::make_tuple("/another/path/with/space in name", "/another/path/with/space in name"),
                    std::make_tuple("/path/with/tab\tin name", "/path/with/tab\tin name"),
                    std::make_tuple("/path/with/newline\nin name", "/path/with/newline\nin name"),
                    std::make_tuple("/path/with/very/long/name/that/keeps/going/on/and/on/and/on/and/on/and/on/and/on/and/on", "/path/with/very/long/name/that/keeps/going/on/and/on/and/on/and/on/and/on/and/on/and/on"),
                    std::make_tuple("/path/with/../relative/../components", "/path/with/../relative/../components"),
                    std::make_tuple("/path/with/./current/./directory/./components", "/path/with/./current/./directory/./components"),
                    std::make_tuple("/path/with/mixed/./../components", "/path/with/mixed/./../components"),
                    std::make_tuple("/path/with/trailing/slash/", "/path/with/trailing/slash/"),
                    std::make_tuple("/path/with/multiple////slashes", "/path/with/multiple////slashes"),
                    std::make_tuple("/path/with/escaped\\ spaces", "/path/with/escaped\\ spaces"),
                    std::make_tuple("/path/with/escaped\\t tabs", "/path/with/escaped\\t tabs"),
                    std::make_tuple("/path/with/escaped\\n newlines", "/path/with/escaped\\n newlines"),
                    std::make_tuple("/path/with/escaped\\\\ backslashes", "/path/with/escaped\\\\ backslashes"),
                    std::make_tuple("/path/with/escaped\\\" quotes", "/path/with/escaped\\\" quotes"),
                    std::make_tuple("/path/with/escaped\\' single quotes", "/path/with/escaped\\' single quotes"),
                    std::make_tuple("/path/with/escaped\\` backticks", "/path/with/escaped\\` backticks"),
                    std::make_tuple("/path/with/escaped\\; semicolons", "/path/with/escaped\\; semicolons"),
                    std::make_tuple("/path/with/escaped\\: colons", "/path/with/escaped\\: colons"),
                    std::make_tuple("/path/with/escaped\\, commas", "/path/with/escaped\\, commas"),
                    std::make_tuple("/path/with/escaped\\! exclamations", "/path/with/escaped\\! exclamations"),
                    std::make_tuple("/path/with/escaped\\@ at signs", "/path/with/escaped\\@ at signs"),
                    std::make_tuple("/path/with/escaped\\# hashes", "/path/with/escaped\\# hashes"),
                    std::make_tuple("/path/with/escaped\\$ dollars", "/path/with/escaped\\$ dollars"),
                    std::make_tuple("/path/with/escaped\\% percentages", "/path/with/escaped\\% percentages"),
                    std::make_tuple("/path/with/escaped\\^ carets", "/path/with/escaped\\^ carets"),
                    std::make_tuple("/path/with/escaped\\& ampersands", "/path/with/escaped\\& ampersands"),
                    std::make_tuple("/path/with/escaped\\* asterisks", "/path/with/escaped\\* asterisks"),
                    std::make_tuple("/path/with/escaped\\( parentheses", "/path/with/escaped\\( parentheses"),
                    std::make_tuple("/path/with/escaped\\) parentheses", "/path/with/escaped\\) parentheses"),
                    std::make_tuple("/path/with/escaped\\- hyphens", "/path/with/escaped\\- hyphens"),
                    std::make_tuple("/path/with/escaped\\_ underscores", "/path/with/escaped\\_ underscores"),
                    std::make_tuple("/path/with/escaped\\= equals", "/path/with/escaped\\= equals"),
                    std::make_tuple("/path/with/escaped\\+ pluses", "/path/with/escaped\\+ pluses"),
                    std::make_tuple("/path/with/escaped\\[ brackets", "/path/with/escaped\\[ brackets"),
                    std::make_tuple("/path/with/escaped\\] brackets", "/path/with/escaped\\] brackets"),
                    std::make_tuple("/path/with/escaped\\{ braces", "/path/with/escaped\\{ braces"),
                    std::make_tuple("/path/with/escaped\\} braces", "/path/with/escaped\\} braces"),
                    std::make_tuple("/path/with/escaped\\| pipes", "/path/with/escaped\\| pipes"),
                    std::make_tuple("/path/with/escaped\\\\ backslashes", "/path/with/escaped\\\\ backslashes"),
                    std::make_tuple("/path/with/escaped\\< less than", "/path/with/escaped\\< less than"),
                    std::make_tuple("/path/with/escaped\\> greater than", "/path/with/escaped\\> greater than"),
                    std::make_tuple("/path/with/escaped\\? question marks", "/path/with/escaped\\? question marks"),
                    std::make_tuple("/path/with/escaped\\~ tildes", "/path/with/escaped\\~ tildes")
                )
            );

        } // namespace Path
    } // namespace fs
} // namespace test
