/**
 * @file insert.entry.pos.test.cpp
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

namespace test {
    namespace fs {
        namespace Path {
            using FSPathInsertEntryAtPosParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                ::fs::Entry, // add entry ...
                std::size_t, // at given pos
                ::fs::Status // expected return status
            >;
            class FSPathInsertEntryAtPos : public ::testing::TestWithParam<FSPathInsertEntryAtPosParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathInsertEntryAtPos(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathInsertEntryAtPos, ReturnGivenStatus) {
                ::fs::Entry entry = std::get<1>(GetParam());
                std::size_t pos = std::get<2>(GetParam());
                ::fs::Status status = std::get<3>(GetParam());

                for (::fs::Path &instance : _instances)
                    EXPECT_EQ(instance.insert(entry, pos), status);
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusOk,
                FSPathInsertEntryAtPos,
                testing::Values(
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/sym_link"), 1, ::fs::Status::OK),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/!@#$%^&*().!@#$%^&*()"), 1, ::fs::Status::OK),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/json/valid/basic.json"), 1, ::fs::Status::OK),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/json/invalid/missiingClosing.json"), 1, ::fs::Status::OK),
                    std::make_tuple("../../tests/assets", Helper::getEntryFromPath("../../tests/assets/"), 1, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/sym_link"), 0, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/!@#$%^&*().!@#$%^&*()"), 0, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/json/valid/basic.json"), 0, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/json/invalid/missiingClosing.json"), 0, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("../../tests/assets/"), 0, ::fs::Status::OK),
                    std::make_tuple("/tmp", Helper::getEntryFromPath("../../tests/assets/"), 1, ::fs::Status::OK),
                    std::make_tuple("/tmp", Helper::getEntryFromPath("etc"), 0, ::fs::Status::OK),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), 1, ::fs::Status::OK),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), 2, ::fs::Status::OK),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), 0, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("aaa"), 0, ::fs::Status::OK),
                    std::make_tuple("/tmp_oojopjop99---/bbb", Helper::getEntryFromPath("Проекты"), 2, ::fs::Status::OK),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("documents"), 1, ::fs::Status::OK),
                    std::make_tuple("/var/log", Helper::getEntryFromPath("syslog"), 1, ::fs::Status::OK),
                    std::make_tuple("/usr/local", Helper::getEntryFromPath("bin"), 2, ::fs::Status::OK),
                    std::make_tuple("/etc", Helper::getEntryFromPath("passwd"), 1, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("root"), 0, ::fs::Status::OK),
                    std::make_tuple("/opt/software", Helper::getEntryFromPath("config"), 1, ::fs::Status::OK),
                    std::make_tuple("/usr/share", Helper::getEntryFromPath("locale"), 1, ::fs::Status::OK),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("kernel"), 2, ::fs::Status::OK),
                    std::make_tuple("/srv/http", Helper::getEntryFromPath("public_html"), 2, ::fs::Status::OK),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("Downloads"), 2, ::fs::Status::OK),
                    std::make_tuple("/var/www", Helper::getEntryFromPath("html"), 1, ::fs::Status::OK),
                    std::make_tuple("/usr/lib", Helper::getEntryFromPath("python3.8"), 2, ::fs::Status::OK),
                    std::make_tuple("/etc/systemd", Helper::getEntryFromPath("system"), 1, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("etc"), 0, ::fs::Status::OK),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("subdir"), 2, ::fs::Status::OK),
                    std::make_tuple("usrlocal", Helper::getEntryFromPath("include"), 1, ::fs::Status::OK),
                    std::make_tuple("/etc", Helper::getEntryFromPath("hosts"), 1, ::fs::Status::OK),
                    std::make_tuple("/var/log", Helper::getEntryFromPath("messages"), 2, ::fs::Status::OK),
                    std::make_tuple("/usr/share", Helper::getEntryFromPath("fonts"), 1, ::fs::Status::OK),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("module1"), 2, ::fs::Status::OK),
                    std::make_tuple("/srv/http", Helper::getEntryFromPath("index.html"), 2, ::fs::Status::OK),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("Pict          ures"), 2, ::fs::Status::OK),
                    std::make_tuple("/var/www", Helper::getEntryFromPath("index.php"), 2, ::fs::Status::OK),
                    std::make_tuple("/usr/lib",  Helper::getEntryFromPath("lib1"), 1, ::fs::Status::OK),
                    std::make_tuple("/etc/systemd", Helper::getEntryFromPath("service1"), 2, ::fs::Status::OK),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("subdir2"), 2, ::fs::Status::OK),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("subdir2"), 1, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath(".entry1"), 0, ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath(".entry2"), 1, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("entry3"), 0, ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("..entry4"), 2, ::fs::Status::OK),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", Helper::getEntryFromPath("entry5"), 5, ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("entry9"), 3, ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("entry10"), 2, ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("entry11"), 0, ::fs::Status::OK),
                    std::make_tuple("./var/log", Helper::getEntryFromPath("messages"), 0, ::fs::Status::OK),
                    std::make_tuple("./../usr/share", Helper::getEntryFromPath("...ezrrete        rtert-----reteezrz.errte"), 2, ::fs::Status::OK),
                    std::make_tuple("./../usr/share", Helper::getEntryFromPath("...ezrrete        rtert-----reteezrz.errte"), 1, ::fs::Status::OK),
                    std::make_tuple("../lib/modules", Helper::getEntryFromPath("module1"), 0, ::fs::Status::OK),
                    std::make_tuple("../lib/modules", Helper::getEntryFromPath("...aaa.bbb.c.d.e.s       .f.e.q.z.er."), 0, ::fs::Status::OK),
                    std::make_tuple("srv/http", Helper::getEntryFromPath("index.html"), 1, ::fs::Status::OK),
                    std::make_tuple("home/user", Helper::getEntryFromPath("Pictures"), 2, ::fs::Status::OK),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("kernel"), 1, ::fs::Status::OK)
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusInvalidIndex,
                FSPathInsertEntryAtPos,
                testing::Values(
                    std::make_tuple("/tmp", Helper::getEntryFromPath("etc"), 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), 6, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/share", Helper::getEntryFromPath("locale"), 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("aaa"), 1, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/tmp_oojopjop99---/bbb", Helper::getEntryFromPath("Проекты"), 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("documents"), 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/var/log", Helper::getEntryFromPath("syslog"), 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/local", Helper::getEntryFromPath("bin"), 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/etc", Helper::getEntryFromPath("passwd"), 3, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/opt/software", Helper::getEntryFromPath("config"), 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/share", Helper::getEntryFromPath("locale"), 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("kernel"), 202, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/srv/http", Helper::getEntryFromPath("public_html"), 1000, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("Downloads"), 40, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/var/www", Helper::getEntryFromPath("html"), 105, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/lib", Helper::getEntryFromPath("python3.8"), 55, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/etc/systemd", Helper::getEntryFromPath("system"), 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("subdir"), 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/local", Helper::getEntryFromPath("include"), 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/etc", Helper::getEntryFromPath("hosts"), 3, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/var/log", Helper::getEntryFromPath("messages"), 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/share", Helper::getEntryFromPath("fonts"), 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("module1"), 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/srv/http", Helper::getEntryFromPath("index.html"), 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("Pict          ures"), 120, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/var/www", Helper::getEntryFromPath("index.php"), 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/lib", Helper::getEntryFromPath("lib1"), 20, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/etc/systemd", Helper::getEntryFromPath("service1"), 50, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("subdir2"), 20, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("subdir2"), 20, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath(".entry1"), 40, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath(".entry2"), 78, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("entry3"), 2, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("..entry4"), 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", Helper::getEntryFromPath("entry5"), 12, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("path/to/directory", Helper::getEntryFromPath("entry9"), 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("entry10"), 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath("entry11"), 6, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("./var/log", Helper::getEntryFromPath("messages"), 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("./../usr/share", Helper::getEntryFromPath("...ezrrete        rtert-----reteezrz.errte"), 6, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("../lib/modules", Helper::getEntryFromPath("module1"), 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("../lib/modules", Helper::getEntryFromPath("...aaa.bbb.c.d.e.s   )    .f.e.q.z.er."), 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("srv/http", Helper::getEntryFromPath("index.html"), 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("home/user", Helper::getEntryFromPath("Pictures"), 4, ::fs::Status::E_PATH_INVALID_INDEX)
                )
            );
        } // namespace Path
    } // namespace fs
} // namespace test 