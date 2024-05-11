/**
 * @file getEntry.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-05
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


namespace test {
    namespace fs {
        namespace Path {

            using FSPathGetEntryParam = std::tuple<
                std::optional<std::string>, // original path                                
                ::fs::Entry // expeced entry
            >;

            class FSPathGetEntryMethod : public ::testing::TestWithParam<FSPathGetEntryParam> {
            protected:
                std::vector<::fs::Path> _instances;

                FSPathGetEntryMethod(void) :
                _instances(::test::fs::Path::Helper::create(std::get<0>(GetParam())))
                {}
            };

            TEST_P(FSPathGetEntryMethod, ReturnsGivenEntry) {
                for (const ::fs::Path &instance : _instances)
                    EXPECT_EQ(instance.getEntry(), std::get<1>(GetParam()));
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenVariousPath,
                FSPathGetEntryMethod,
                testing::Values(
                    std::make_tuple("../../tests/assets/../../tests/assets/!@#$%^&*().!@#$%^&*()", Helper::getEntryFromPath("../../tests/assets/!@#$%^&*().!@#$%^&*()")),
                    std::make_tuple("../../tests/assets/json/valid/basic.json", Helper::getEntryFromPath("../../tests/assets/json/valid/basic.json")),
                    std::make_tuple("../../tests/assets/json/invalid/missingClosing.json", Helper::getEntryFromPath("../../tests/assets/json/invalid/missingClosing.json")),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/")),
                    std::make_tuple("../../tests/assets/", Helper::getEntryFromPath("../../tests/assets")),
                    std::make_tuple("../../tests/assets/sym_link", Helper::getEntryFromPath("../../tests/assets/sym_link")),
                    std::make_tuple("../../tests/assets/sym_link", Helper::getEntryFromPath("../../tests/assets/sym_link/")),

                    std::make_tuple("etc", Helper::getEntryFromPath("etc")),
                    std::make_tuple("/tmp", Helper::getEntryFromPath("/tmp")),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("aaa/bbb")),
                    std::make_tuple("ccc", Helper::getEntryFromPath("ccc")),
                    std::make_tuple("aaa", Helper::getEntryFromPath("aaa")),
                    std::make_tuple("/tmp_oojopjop99---/bbb/Проекты", Helper::getEntryFromPath("/tmp_oojopjop99---/bbb/Проекты")),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("/home/user")),
                    std::make_tuple("/var/log", Helper::getEntryFromPath("/var/log")),
                    std::make_tuple("/usr/local", Helper::getEntryFromPath("/usr/local")),
                    std::make_tuple("/etc", Helper::getEntryFromPath("/etc")),
                    std::make_tuple("root", Helper::getEntryFromPath("root")),
                    std::make_tuple("/opt/software", Helper::getEntryFromPath("/opt/software")),
                    std::make_tuple("/usr/share", Helper::getEntryFromPath("/usr/share")),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("/lib/modules")),
                    std::make_tuple("/srv/http", Helper::getEntryFromPath("/srv/http")),
                    std::make_tuple("/var/www", Helper::getEntryFromPath("/var/www")),
                    std::make_tuple("python3.8", Helper::getEntryFromPath("python3.8")),
                    std::make_tuple("/etc/systemd", Helper::getEntryFromPath("/etc/systemd")),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("/tmp/complex-dir-name")),
                    std::make_tuple(".entry1", Helper::getEntryFromPath(".entry1")),
                    std::make_tuple("/path/to/directory/.entry2", Helper::getEntryFromPath("/path/to/directory/.entry2")),
                    std::make_tuple("/path/to/directory/..entry4", Helper::getEntryFromPath("/path/to/directory/..entry4")),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory/entry5", Helper::getEntryFromPath("/p/a/t/h/to/d/i/r/e/ctory/entry5")),
                    std::make_tuple("entry5", Helper::getEntryFromPath("entry5")),
                    std::make_tuple("./var/log", Helper::getEntryFromPath("./var/log")),
                    std::make_tuple("./../usr/share", Helper::getEntryFromPath("./../usr/share")),
                    std::make_tuple("./../usr/share/...ezrrete        rtert-----reteezrz.errte", Helper::getEntryFromPath("./../usr/share/...ezrrete        rtert-----reteezrz.errte")),
                    std::make_tuple("...ezrrete        rtert-----reteezrz.errte", Helper::getEntryFromPath("...ezrrete        rtert-----reteezrz.errte")),
                    std::make_tuple("../lib/modules", Helper::getEntryFromPath("../lib/modules")),
                    std::make_tuple("index.html", Helper::getEntryFromPath("index.html")),
                    std::make_tuple("", ::fs::Entry()),
                    std::make_tuple(std::nullopt, ::fs::Entry())
                )
            );

        } // namespace Path
    } // namespace fs
} // namespace test
