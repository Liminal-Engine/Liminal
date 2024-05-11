/**
 * @file insert.entry.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-04
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

#include <iostream>

namespace test {
    namespace fs {
        namespace Path {

            using FSPathInsertEntryParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                ::fs::Entry, // add entry ...
                ::fs::Status // expected return status
            >;
            class FSPathInsertEntry : public ::testing::TestWithParam<FSPathInsertEntryParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathInsertEntry(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathInsertEntry, ReturnGivenStatus) {
                ::fs::Entry entry = std::get<1>(GetParam());
                ::fs::Status status = std::get<2>(GetParam());

                for (::fs::Path &instance : _instances) {
                    EXPECT_EQ(instance.insert(entry), status);
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusOk,
                FSPathInsertEntry,
                testing::Values(
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/sym_link"), ::fs::Status::OK),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/!@#$%^&*().!@#$%^&*()"), ::fs::Status::OK),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/json/valid/basic.json"), ::fs::Status::OK),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/json/invalid/missingClosing.json"), ::fs::Status::OK),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/"), ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/sym_link"), ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/!@#$%^&*().!@#$%^&*()"), ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/json/valid/basic.json"), ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/json/invalid/missingClosing.json"), ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/"), ::fs::Status::OK),
                    std::make_tuple("/tmp", Helper::getEntryFromPath("../../tests/assets/"), ::fs::Status::OK),

                    std::make_tuple("/tmp", Helper::getEntryFromPath("etc"), ::fs::Status::OK),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), ::fs::Status::OK),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), ::fs::Status::OK),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("aaa"), ::fs::Status::OK),
                    std::make_tuple("/tmp_oojopjop99---/bbb", Helper::getEntryFromPath("Проекты"), ::fs::Status::OK),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("documents"), ::fs::Status::OK),
                    std::make_tuple("/var/log", Helper::getEntryFromPath("syslog"), ::fs::Status::OK),
                    std::make_tuple("/usr/local", Helper::getEntryFromPath("bin"), ::fs::Status::OK),
                    std::make_tuple("/etc", Helper::getEntryFromPath("passwd"), ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("root"), ::fs::Status::OK),
                    std::make_tuple("/opt/software", Helper::getEntryFromPath("config"), ::fs::Status::OK),
                    std::make_tuple("/usr/share", Helper::getEntryFromPath("locale"), ::fs::Status::OK),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("kernel"), ::fs::Status::OK),
                    std::make_tuple("/srv/http", Helper::getEntryFromPath("public_html"), ::fs::Status::OK),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("Downloads"), ::fs::Status::OK),
                    std::make_tuple("/var/www", Helper::getEntryFromPath("html"), ::fs::Status::OK),
                    std::make_tuple("/usr/lib", Helper::getEntryFromPath("python3.8"), ::fs::Status::OK),
                    std::make_tuple("/etc/systemd", Helper::getEntryFromPath("system"), ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("etc"), ::fs::Status::OK),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("subdir"), ::fs::Status::OK),
                    std::make_tuple("usrlocal", Helper::getEntryFromPath("include"), ::fs::Status::OK),
                    std::make_tuple("/etc", Helper::getEntryFromPath("hosts"), ::fs::Status::OK),
                    std::make_tuple("/var/log", Helper::getEntryFromPath("messages"), ::fs::Status::OK),
                    std::make_tuple("/usr/share", Helper::getEntryFromPath("fonts"), ::fs::Status::OK),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("module1"), ::fs::Status::OK),
                    std::make_tuple("/srv/http", Helper::getEntryFromPath("index.html"), ::fs::Status::OK),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("Pict          ures"), ::fs::Status::OK),
                    std::make_tuple("/var/www", Helper::getEntryFromPath("index.php"), ::fs::Status::OK),
                    std::make_tuple("/usr/lib",  Helper::getEntryFromPath("lib1"), ::fs::Status::OK),
                    std::make_tuple("/etc/systemd", Helper::getEntryFromPath("service1"), ::fs::Status::OK),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("subdir2"), ::fs::Status::OK),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("subdir2"), ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath(".entry1"), ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath(".entry2"), ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("entry3"), ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("..entry4"), ::fs::Status::OK),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", Helper::getEntryFromPath("entry5"), ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("entry9"), ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("entry10"), ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("entry11"), ::fs::Status::OK),
                    std::make_tuple("./var/log", Helper::getEntryFromPath("messages"), ::fs::Status::OK),
                    std::make_tuple("./../usr/share", Helper::getEntryFromPath("...ezrrete        rtert-----reteezrz.errte"), ::fs::Status::OK),
                    std::make_tuple("./../usr/share", Helper::getEntryFromPath("...ezrrete        rtert-----reteezrz.errte"), ::fs::Status::OK),
                    std::make_tuple("../lib/modules", Helper::getEntryFromPath("module1"), ::fs::Status::OK),
                    std::make_tuple("../lib/modules", Helper::getEntryFromPath("...aaa.bbb.c.d.e.s       .f.e.q.z.er."), ::fs::Status::OK),
                    std::make_tuple("srv/http", Helper::getEntryFromPath("index.html"), ::fs::Status::OK),
                    std::make_tuple("home/user", Helper::getEntryFromPath("Pictures"), ::fs::Status::OK),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("kernel"), ::fs::Status::OK)
                )
            );

        } // namespace Path
    } // namespace fs
} // namespace test
