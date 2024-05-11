/**
 * @file insert.entry.newPath.test.cpp
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
#include <filesystem>
#include <tuple>

#include <iostream>

namespace test {
    namespace fs {
        namespace Path {

            using FSPathInsertEntryNewPathParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                ::fs::Entry, // add entry ...
                ::fs::Path // expected new path
            >;
            class FSPathInsertEntryNewPath : public ::testing::TestWithParam<FSPathInsertEntryNewPathParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathInsertEntryNewPath(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathInsertEntryNewPath, ReturnGivenStatus) {
                ::fs::Entry entry = std::get<1>(GetParam());

                for (::fs::Path &instance : _instances) {
                    instance.insert(entry);
                    EXPECT_EQ(instance, std::get<2>(GetParam()));
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingEquality,
                FSPathInsertEntryNewPath,
                testing::Values(
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/sym_link"), ::fs::Path("../../tests/assets/sym_link")),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/!@#$%^&*().!@#$%^&*()"), ::fs::Path("../../tests/assets/!@#$%^&*().!@#$%^&*()")),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/json/valid/basic.json"), ::fs::Path("../../tests/assets/basic.json")),
                    std::make_tuple("../../tests/assets/json/invalid", Helper::getEntryFromPath("../../tests/assets/json/invalid/missingClosing.json"), ::fs::Path("../../tests/assets/json/invalid/missingClosing.json")),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/"), ::fs::Path("../../tests/assets/assets/.")),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/"), ::fs::Path("../../tests/assets/assets")),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/sym_link"), ::fs::Path("sym_link")),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/!@#$%^&*().!@#$%^&*()"), ::fs::Path("./!@#$%^&*().!@#$%^&*()")),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/json/valid/basic.json"), ::fs::Path("basic.json")),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/json/invalid/missingClosing.json"), ::fs::Path("./missingClosing.json/.")),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/"), ::fs::Path("assets")),
                    std::make_tuple("/tmp", Helper::getEntryFromPath("../../tests/assets/"), ::fs::Path("/tmp/assets")),

                    std::make_tuple("/tmp", Helper::getEntryFromPath("etc"), ::fs::Path("/tmp/etc")),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), ::fs::Path("/aaa/bbb/ccc/")),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("aaa"), ::fs::Path("./aaa")),
                    std::make_tuple("/tmp_oojopjop99---/bbb", Helper::getEntryFromPath("Проекты"), ::fs::Path("/tmp_oojopjop99---/bbb/Проекты")),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("root"), ::fs::Path("./root/../root")),
                    std::make_tuple("/tmp/.complex-dir-name", Helper::getEntryFromPath("subdir"), ::fs::Path("/tmp/.complex-dir-name/subdir/../../.complex-dir-name/subdir")),
                    std::make_tuple("/srv/http", Helper::getEntryFromPath("index.html"), ::fs::Path("/srv/http/index.html/./aaa/./../../.././../srv/http/index.html")),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("Pict          ures"), ::fs::Path("/home/user/Pict          ures")),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath(".entry1"), ::fs::Path("./.entry1")),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("..entry4"), ::fs::Path("/path/to/directory/..entry4")),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", Helper::getEntryFromPath("entry5"), ::fs::Path("/p/a/t/h/to/d/i/r/e/ctory/entry5")),
                    std::make_tuple("./var/log", Helper::getEntryFromPath("messages"), ::fs::Path("./var/log/messages/.")),
                    std::make_tuple("./../usr/share", Helper::getEntryFromPath("...ezrrete        rtert-----reteezrz.errte"), ::fs::Path("./../usr/share/...ezrrete        rtert-----reteezrz.errte")),
                    std::make_tuple("../lib/modules", Helper::getEntryFromPath("...aaa.bbb.c.d.e.s       .f.e.q.z.er."), ::fs::Path("../lib/modules/...aaa.bbb.c.d.e.s       .f.e.q.z.er.")),
                    std::make_tuple("srv/http", Helper::getEntryFromPath("index.html"), ::fs::Path("./srv/http/index.html")),
                    std::make_tuple("srv/http", Helper::getEntryFromPath("index.html"), ::fs::Path("srv/http/index.html")),
                    std::make_tuple("home/user", Helper::getEntryFromPath("Pictures"), ::fs::Path("home/user/Pictures/.")),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("kernel"), ::fs::Path("/lib/modules/kernel/"))
                )
            );

        } // namespace Path
    } // namespace fs
} // namespace test
