/**
 * @file equalityComparisonOperator.test.cpp
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

            using FSPathEqualityComparisonOperatorParam = std::tuple<
                std::string, // left path
                std::string, // right path
                bool // expected retunred value
            >;
            class FSPathEqualityComparisonOperator : public ::testing::TestWithParam<FSPathEqualityComparisonOperatorParam> {
                protected:
                    std::vector<::fs::Path> _leftInstances;
                    std::vector<::fs::Path> _rightInstances;

                    FSPathEqualityComparisonOperator(void) :
                    _leftInstances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))},
                    _rightInstances{::test::fs::Path::Helper::create(std::get<1>(GetParam()))}
                    {}
            };

            TEST_P(FSPathEqualityComparisonOperator, GivesExpectingPath) {                
                for (const ::fs::Path &leftInstance : _leftInstances) {                                        
                    for (const ::fs::Path &rightInstance : _rightInstances) {                                        
                        EXPECT_EQ(leftInstance == rightInstance, std::get<2>(GetParam()));
                    }
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingEquality,
                FSPathEqualityComparisonOperator,
                testing::Values(
                    std::make_tuple("/tmp_fs", "/tmp_fs", true),
                    std::make_tuple("/aaa/bbb", "/aaa/bbb", true),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "/tmp_fs_oojopjop99---/bbb", true),
                    std::make_tuple("/home/user", "/home/user", true),
                    std::make_tuple("/var/log", "/var/log", true),
                    std::make_tuple("/usr/local", "/usr/local", true),
                    std::make_tuple("/etc", "/etc", true),
                    std::make_tuple("/tmp_fs/complex-dir-name", "/tmp_fs/complex-dir-name", true),
                    std::make_tuple("/tmp_fs/complex-dir-name", "/tmp_fs/complex-dir-name/subdir////..////../complex-dir-name////.///.//////../complex-dir-name///////.////", true),
                    std::make_tuple("/path/to/directory", "/path/to/directory", true),
                    std::make_tuple("path/to/directory", "path/to/directory", true),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "/p/a/t/h/to/d/i/r/e/ctory", true),
                    std::make_tuple("./var/log", "./var/log", true),
                    std::make_tuple("./var/log", "var/log", true),
                    std::make_tuple("./var/log", "var/log/.", true),
                    std::make_tuple("./var/log", "var/log/", true),
                    std::make_tuple("./var/log", "var/log/../log", true),
                    std::make_tuple("./../usr/share", "./../usr/share", true),
                    std::make_tuple("../lib/modules", "./parent/../../lib/modules", true),
                    std::make_tuple("/lib/modules", "/lib/modules", true),
                    std::make_tuple("/lib/modules", "/lib/modules/", true),
                    std::make_tuple("/lib/modules", "/lib/modules/././.", true),
                    std::make_tuple("/lib/modules", "/lib/modules/././../modules", true),
                    std::make_tuple("/new/path/with/special/characters/!@#$%^&*()", "/new/path/with/special/characters/!@#$%^&*()", true),
                    std::make_tuple("/another/path/with/space in name", "/another/path/with/space in name", true),
                    std::make_tuple("/path/with/tab\tin name", "/path/with/tab\tin name", true),
                    std::make_tuple("/path/with/newline\nin name", "/path/with/newline\nin name", true),
                    std::make_tuple("/path/with/very/long/name/that/keeps/going/on/and/on/and/on/and/on/and/on/and/on/and/on", "/path/with/very/long/name/that/keeps/going/on/and/on/and/on/and/on/and/on/and/on/and/on", true),
                    std::make_tuple("/path/with/../relative/../components", "/path/with/../relative/../components", true),
                    std::make_tuple("/path/with/./current/./directory/./components", "/path/with/./current/./directory/./components", true),
                    std::make_tuple("/path/with/mixed/./../components", "/path/with/mixed/./../components", true),
                    std::make_tuple("/path/with/trailing/slash/", "/path/with/trailing/slash/", true),
                    std::make_tuple("/path/with/multiple////slashes", "/path/with/multiple////slashes", true),
                    std::make_tuple("/path/with/escaped\\ spaces", "/path/with/escaped\\ spaces", true),
                    std::make_tuple("/path/with/escaped\\t tabs", "/path/with/escaped\\t tabs", true),
                    std::make_tuple("/path/with/escaped\\n newlines", "/path/with/escaped\\n newlines", true),
                    std::make_tuple("/path/with/escaped\\\\ backslashes", "/path/with/escaped\\\\ backslashes", true),
                    std::make_tuple("/path/with/escaped\\\" quotes", "/path/with/escaped\\\" quotes", true),
                    std::make_tuple("/path/with/escaped\\' single quotes", "/path/with/escaped\\' single quotes", true),
                    std::make_tuple("/path/with/escaped\\` backticks", "/path/with/escaped\\` backticks", true),
                    std::make_tuple("/path/with/escaped\\; semicolons", "/path/with/escaped\\; semicolons", true),
                    std::make_tuple("/path/with/escaped\\: colons", "/path/with/escaped\\: colons", true),
                    std::make_tuple("/path/with/escaped\\, commas", "/path/with/escaped\\, commas", true),
                    std::make_tuple("/path/with/escaped\\! exclamations", "/path/with/escaped\\! exclamations", true),
                    std::make_tuple("/path/with/escaped\\@ at signs", "/path/with/escaped\\@ at signs", true),
                    std::make_tuple("/path/with/escaped\\# hashes", "/path/with/escaped\\# hashes", true),
                    std::make_tuple("/path/with/escaped\\$ dollars", "/path/with/escaped\\$ dollars", true),
                    std::make_tuple("/path/with/escaped\\% percentages", "/path/with/escaped\\% percentages", true),
                    std::make_tuple("/path/with/escaped\\^ carets", "/path/with/escaped\\^ carets", true),
                    std::make_tuple("/path/with/escaped\\& ampersands", "/path/with/escaped\\& ampersands", true),
                    std::make_tuple("/path/with/escaped\\* asterisks", "/path/with/escaped\\* asterisks", true),
                    std::make_tuple("/path/with/escaped\\( parentheses", "/path/with/escaped\\( parentheses", true),
                    std::make_tuple("/path/with/escaped\\) parentheses", "/path/with/escaped\\) parentheses", true),
                    std::make_tuple("/path/with/escaped\\- hyphens", "/path/with/escaped\\- hyphens", true),
                    std::make_tuple("/path/with/escaped\\_ underscores", "/path/with/escaped\\_ underscores", true),
                    std::make_tuple("/path/with/escaped\\= equals", "/path/with/escaped\\= equals", true),
                    std::make_tuple("/path/with/escaped\\+ pluses", "/path/with/escaped\\+ pluses", true),
                    std::make_tuple("/path/with/escaped\\[ brackets", "/path/with/escaped\\[ brackets", true),
                    std::make_tuple("/path/with/escaped\\] brackets", "/path/with/escaped\\] brackets", true),
                    std::make_tuple("/path/with/escaped\\{ braces", "/path/with/escaped\\{ braces", true),
                    std::make_tuple("/path/with/escaped\\} braces", "/path/with/escaped\\} braces", true),
                    std::make_tuple("/path/with/escaped\\| pipes", "/path/with/escaped\\| pipes", true),
                    std::make_tuple("/path/with/escaped\\\\ backslashes", "/path/with/escaped\\\\ backslashes", true),
                    std::make_tuple("/path/with/escaped\\< less than", "/path/with/escaped\\< less than", true),
                    std::make_tuple("/path/with/escaped\\> greater than", "/path/with/escaped\\> greater than", true),
                    std::make_tuple("/path/with/escaped\\? question marks", "/path/with/escaped\\? question marks", true),
                    std::make_tuple("/path/with/escaped\\~ tildes", "/path/with/escaped\\~ tildes", true)
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingInequality,
                FSPathEqualityComparisonOperator,
                testing::Values(
                    std::make_tuple("/tmp_fs", "/tmp_fs_different", false),
                    std::make_tuple("/aaa/bbb", "/aaa/ccc", false),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "/tmp_fs_oojopjop99---/ccc", false),
                    std::make_tuple("/home/user", "/home/admin", false),
                    std::make_tuple("/var/log", "/var/logs", false),
                    std::make_tuple("/usr/local", "/usr/global", false),
                    std::make_tuple("/etc", "/etc/config", false),
                    std::make_tuple("/tmp_fs/complex-dir-name", "/tmp_fs/simple-dir-name", false),
                    std::make_tuple("/path/to/directory", "/path/to/another_directory", false),
                    std::make_tuple("path/to/directory", "path/to/another_directory", false),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "/p/a/t/h/to/d/i/r/e/ctory2", false),
                    std::make_tuple("./var/log", "./var/logs", false),
                    std::make_tuple("./var/log", "var/logs", false),
                    std::make_tuple("./var/log", "var/logs/./.", false),
                    std::make_tuple("./var/log", "var/log/../logs", false),
                    std::make_tuple("./../usr/share", "./../usr/local", false),
                    std::make_tuple("../lib/modules", "./parent/../../lib/kernel", false),
                    std::make_tuple("/lib/modules", "/lib/kernel", false),
                    std::make_tuple("/lib/modules", "/lib/modules/extra", false),
                    std::make_tuple("/lib/modules", "/lib/modules/././..", false),
                    std::make_tuple("/new/path/with/special/characters/!@#$%^&*()", "/new/path/with/special/characters/!@#$%^&*()_different", false),
                    std::make_tuple("/another/path/with/space in name", "/another/path/with/space in name different", false),
                    std::make_tuple("/path/with/tab\tin name", "/path/with/tab\tin name different", false),
                    std::make_tuple("/path/with/newline\nin name", "/path/with/newline\nin name different", false),
                    std::make_tuple("/path/with/very/long/name/that/keeps/going/on/and/on/and/on/and/on/and/on/and/on/and/on", "/path/with/very/long/name/that/keeps/going/on/and/on/and/on/and/on/and/on/and/on/and/on_different", false),
                    std::make_tuple("/path/with/../relative/../components", "/path/with/../relative/../different_components", false),
                    std::make_tuple("/path/with/./current/./directory/./components", "/path/with/./current/./directory/./different_components", false),
                    std::make_tuple("/path/with/mixed/./../components", "/path/with/mixed/./../different_components", false),
                    std::make_tuple("/path/with/trailing/slash/", "/path/with/trailing/slash/different", false),
                    std::make_tuple("/path/with/multiple////slashes", "/path/with/multiple////slashes/different", false),
                    std::make_tuple("/path/with/escaped\\ spaces", "/path/with/escaped\\ spaces different", false),
                    std::make_tuple("/path/with/escaped\\t tabs", "/path/with/escaped\\t tabs different", false),
                    std::make_tuple("/path/with/escaped\\n newlines", "/path/with/escaped\\n newlines different", false),
                    std::make_tuple("/path/with/escaped\\\\ backslashes", "/path/with/escaped\\\\ backslashes different", false),
                    std::make_tuple("/path/with/escaped\\\" quotes", "/path/with/escaped\\\" quotes different", false),
                    std::make_tuple("/path/with/escaped\\' single quotes", "/path/with/escaped\\' single quotes different", false),
                    std::make_tuple("/path/with/escaped\\` backticks", "/path/with/escaped\\` backticks different", false),
                    std::make_tuple("/path/with/escaped\\; semicolons", "/path/with/escaped\\; semicolons different", false),
                    std::make_tuple("/path/with/escaped\\: colons", "/path/with/escaped\\: colons different", false),
                    std::make_tuple("/path/with/escaped\\, commas", "/path/with/escaped\\, commas different", false),
                    std::make_tuple("/path/with/escaped\\! exclamations", "/path/with/escaped\\! exclamations different", false),
                    std::make_tuple("/path/with/escaped\\@ at signs", "/path/with/escaped\\@ at signs different", false),
                    std::make_tuple("/path/with/escaped\\# hashes", "/path/with/escaped\\# hashes different", false),
                    std::make_tuple("/path/with/escaped\\$ dollars", "/path/with/escaped\\$ dollars different", false),
                    std::make_tuple("/path/with/escaped\\% percentages", "/path/with/escaped\\% percentages different", false),
                    std::make_tuple("/path/with/escaped\\^ carets", "/path/with/escaped\\^ carets different", false),
                    std::make_tuple("/path/with/escaped\\& ampersands", "/path/with/escaped\\& ampersands different", false),
                    std::make_tuple("/path/with/escaped\\* asterisks", "/path/with/escaped\\* asterisks different", false),
                    std::make_tuple("/path/with/escaped\\( parentheses", "/path/with/escaped\\( parentheses different", false),
                    std::make_tuple("/path/with/escaped\\) parentheses", "/path/with/escaped\\) parentheses different", false),
                    std::make_tuple("/path/with/escaped\\- hyphens", "/path/with/escaped\\- hyphens different", false),
                    std::make_tuple("/path/with/escaped\\_ underscores", "/path/with/escaped\\_ underscores different", false),
                    std::make_tuple("/path/with/escaped\\= equals", "/path/with/escaped\\= equals different", false),
                    std::make_tuple("/path/with/escaped\\+ pluses", "/path/with/escaped\\+ pluses different", false),
                    std::make_tuple("/path/with/escaped\\[ brackets", "/path/with/escaped\\[ brackets different", false),
                    std::make_tuple("/path/with/escaped\\] brackets", "/path/with/escaped\\] brackets different", false),
                    std::make_tuple("/path/with/escaped\\{ braces", "/path/with/escaped\\{ braces different", false),
                    std::make_tuple("/path/with/escaped\\} braces", "/path/with/escaped\\} braces different", false),
                    std::make_tuple("/path/with/escaped\\| pipes", "/path/with/escaped\\| pipes different", false),
                    std::make_tuple("/path/with/escaped\\\\ backslashes", "/path/with/escaped\\\\ backslashes different", false),
                    std::make_tuple("/path/with/escaped\\< less than", "/path/with/escaped\\< less than different", false),
                    std::make_tuple("/path/with/escaped\\> greater than", "/path/with/escaped\\> greater than different", false),
                    std::make_tuple("/path/with/escaped\\? question marks", "/path/with/escaped\\? question marks different", false),
                    std::make_tuple("/path/with/escaped\\~ tildes", "/path/with/escaped\\~ tildes different", false)
                )
            );

        } // namespace Path
    } // namespace fs
} // namespace test
