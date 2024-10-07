/**
 * @file insert.test.cpp
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

namespace test {
    namespace fs {
        namespace Path {

            using FSPathInsertStringReturnedStatusParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                std::string, // add string entry ...
                ::fs::Status // expected return status
            >;
            class FSPathInsertStringReturnedStatus : public ::testing::TestWithParam<FSPathInsertStringReturnedStatusParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathInsertStringReturnedStatus(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathInsertStringReturnedStatus, ReturnGivenStatus) {
                std::string entry = std::get<1>(GetParam());
                ::fs::Status status = std::get<2>(GetParam());

                for (::fs::Path &instance : _instances)
                    EXPECT_EQ(instance.insert(entry), status);
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusOk,
                FSPathInsertStringReturnedStatus,
                testing::Values(
                    std::make_tuple("/tmp_fs", ".", ::fs::Status::OK),
                    std::make_tuple("/tmp_fs", "etc", ::fs::Status::OK),
                    std::make_tuple("/aaa/bbb", "ccc", ::fs::Status::OK),
                    std::make_tuple("/aaa/bbb", "ccc", ::fs::Status::OK),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "Проекты", ::fs::Status::OK),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "Проекты", ::fs::Status::OK),
                    std::make_tuple("/home/user", "documents", ::fs::Status::OK),
                    std::make_tuple("/var/log", "syslog", ::fs::Status::OK),
                    std::make_tuple("/usr/local", "bin", ::fs::Status::OK),
                    std::make_tuple("/etc", "passwd", ::fs::Status::OK),
                    std::make_tuple("/opt/software", "config", ::fs::Status::OK),
                    std::make_tuple("/usr/share", "locale", ::fs::Status::OK),
                    std::make_tuple("/lib/modules", "kernel", ::fs::Status::OK),
                    std::make_tuple("/srv/http", "public_html", ::fs::Status::OK),
                    std::make_tuple("/home/user", "Downloads", ::fs::Status::OK),
                    std::make_tuple("/var/www", "html", ::fs::Status::OK),
                    std::make_tuple("/usr/lib", "python3.8", ::fs::Status::OK),
                    std::make_tuple("/etc/systemd", "system", ::fs::Status::OK),
                    std::make_tuple("/tmp_fs/complex-dir-name", "subdir", ::fs::Status::OK),
                    std::make_tuple("usrlocal", "include", ::fs::Status::OK),
                    std::make_tuple("/etc", "hosts", ::fs::Status::OK),
                    std::make_tuple("/var/log", "messages", ::fs::Status::OK),
                    std::make_tuple("/usr/share", "fonts", ::fs::Status::OK),
                    std::make_tuple("/lib/modules", "module1", ::fs::Status::OK),
                    std::make_tuple("/srv/http", "index.html", ::fs::Status::OK),
                    std::make_tuple("/home/user", "Pict          ures", ::fs::Status::OK),
                    std::make_tuple("/var/www", "index.php", ::fs::Status::OK),
                    std::make_tuple("/usr/lib", "lib1", ::fs::Status::OK),
                    std::make_tuple("/etc/systemd", "service1", ::fs::Status::OK),
                    std::make_tuple("/tmp_fs/complex-dir-name", "subdir2", ::fs::Status::OK),
                    std::make_tuple(std::nullopt, "entry3", ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", "..entry4", ::fs::Status::OK),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "entry5", ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", "entry9", ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", "entry10", ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", "entry11", ::fs::Status::OK),
                    std::make_tuple("./var/log", "messages", ::fs::Status::OK),
                    std::make_tuple("./../usr/share", "...ezrrete        rtert-----reteezrz.errte", ::fs::Status::OK),
                    std::make_tuple("../lib/modules", "...aaa.bbb.c.d.e.s       .f.e.q.z.er.", ::fs::Status::OK),
                    std::make_tuple("srv/http", "index.html", ::fs::Status::OK),
                    std::make_tuple("home/user", "Pictures", ::fs::Status::OK),
                    std::make_tuple("/lib/modules", "kernel", ::fs::Status::OK)
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusInvalidEntryName,
                FSPathInsertStringReturnedStatus,
                testing::Values(
                    std::make_tuple("/tmp_fs", "/etc", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs", "et/c", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/aaa/bbb", "/ccc", ::fs::Status::E_PATH_INVALID_ENTRY_NAME), // this should not work
                    std::make_tuple("/aaa/bbb", "c\\/\\cc", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/aaa/bbb", "/cc\"c", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/aaa/bbb", "cc></c", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "Пр/оекты", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "/Проекты", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/home/user", "doc/umen<>ts", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/var/log", "/s\\y<s>l\"o /  -|g", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/local", "b*/in", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/etc", "pas|sw/*d", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/etc", "/passwd", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/srv/http", "public_htm:l/", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/home/user", "Downlo:/ds", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/var/www", "ht/ml", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/lib", "pyth/on3:8", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/lib", "/python3.8", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/share", "/fonts", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/etc/systemd", "s|y/s/t&em", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs/complex-dir-name", "subdi//r", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("usrlocal", "i:\"/nclude", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/var/log", "/me<>ssages/", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/share", "fo|?*&nts/", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/lib/modules", "mo/////dule1", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/srv/http", "/index:html", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/home/user", "Pictu*/*-**res", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/var/www", "in/dex*php", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/lib/modules", "//kernel", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/lib/modules", "//ker/nel", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/lib", "lib/:1", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/etc/systemd", "ser//vice1", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs/complex-dir-name", "/subdir2", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs/complex-dir-name", "s/ubdir2", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs/complex-dir-name", "//subdir2", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs/complex-dir-name", "//su/bdir2", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple(std::nullopt, "/entry3", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple(std::nullopt, "entr~~~/~~y3", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/path/to/directory", "~.ent/ry4", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", ":ent/ry5", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/path/to/directory", "entr/y|9", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/path/to/directory", "entry|1/0", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/path/to/directory", "en/try|11", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("./var/log", "mess>/>ages", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("./../usr/share", "/...ezrrete        rtert-----reteezrz.errte", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("./../usr/share", "...ezrretertert-----reteezrz.errte/", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("../lib/modules", "/..:.aaa.bbb.c.d.e.s.f.e.q.z.er.", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("srv/http", "/index~html", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("home/user", "Pictu/res&", ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/lib/modules", "/kernel", ::fs::Status::E_PATH_INVALID_ENTRY_NAME)
                )
            );
        } // namespace Path
    } // namespace fs
} // namespace test
