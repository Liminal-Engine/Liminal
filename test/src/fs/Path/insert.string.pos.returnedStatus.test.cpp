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

            using FSPathInsertStringAtPosParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                std::string, // add string entry ...
                std::size_t, // at given pos
                ::fs::Status // expected return status
            >;
            class FSPathInsertStringAtPos : public ::testing::TestWithParam<FSPathInsertStringAtPosParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathInsertStringAtPos(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathInsertStringAtPos, ReturnGivenStatus) {
                std::string entry = std::get<1>(GetParam());
                std::size_t pos = std::get<2>(GetParam());
                ::fs::Status status = std::get<3>(GetParam());

                for (::fs::Path &instance : _instances)
                    EXPECT_EQ(instance.insert(entry, pos), status);
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusOk,
                FSPathInsertStringAtPos,
                testing::Values(
                    std::make_tuple("/tmp_fs", ".", 1, ::fs::Status::OK),
                    std::make_tuple("/tmp_fs", "etc", 0, ::fs::Status::OK),
                    std::make_tuple("/aaa/bbb", "ccc", 1, ::fs::Status::OK),
                    std::make_tuple("/aaa/bbb", "ccc", 2, ::fs::Status::OK),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "Проекты", 2, ::fs::Status::OK),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "Проекты", 1, ::fs::Status::OK),
                    std::make_tuple("/home/user", "documents", 0, ::fs::Status::OK),
                    std::make_tuple("/var/log", "syslog", 1, ::fs::Status::OK),
                    std::make_tuple("/usr/local", "bin", 2, ::fs::Status::OK),
                    std::make_tuple("/etc", "passwd", 0, ::fs::Status::OK),
                    std::make_tuple("/opt/software", "config", 1, ::fs::Status::OK),
                    std::make_tuple("/usr/share", "locale", 0, ::fs::Status::OK),
                    std::make_tuple("/lib/modules", "kernel", 2, ::fs::Status::OK),
                    std::make_tuple("/srv/http", "public_html", 1, ::fs::Status::OK),
                    std::make_tuple("/home/user", "Downloads", 0, ::fs::Status::OK),
                    std::make_tuple("/var/www", "html", 1, ::fs::Status::OK),
                    std::make_tuple("/usr/lib", "python3.8", 2, ::fs::Status::OK),
                    std::make_tuple("/etc/systemd", "system", 0, ::fs::Status::OK),
                    std::make_tuple("/tmp_fs/complex-dir-name", "subdir", 1, ::fs::Status::OK),
                    std::make_tuple("usrlocal", "include", 1, ::fs::Status::OK),
                    std::make_tuple("/etc", "hosts", 1, ::fs::Status::OK),
                    std::make_tuple("/var/log", "messages", 2, ::fs::Status::OK),
                    std::make_tuple("/usr/share", "fonts", 0, ::fs::Status::OK),
                    std::make_tuple("/lib/modules", "module1", 1, ::fs::Status::OK),
                    std::make_tuple("/srv/http", "index.html", 1, ::fs::Status::OK),
                    std::make_tuple("/home/user", "Pict          ures", 0, ::fs::Status::OK),
                    std::make_tuple("/var/www", "index.php", 1, ::fs::Status::OK),
                    std::make_tuple("/usr/lib", "lib1", 2, ::fs::Status::OK),
                    std::make_tuple("/etc/systemd", "service1", 0, ::fs::Status::OK),
                    std::make_tuple("/tmp_fs/complex-dir-name", "subdir2", 2, ::fs::Status::OK),
                    std::make_tuple(std::nullopt, "entry3", 0, ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", "..entry4", 1, ::fs::Status::OK),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "entry5", 10, ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", "entry9", 1, ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", "entry10", 2, ::fs::Status::OK),
                    std::make_tuple("/path/to/directory", "entry11", 3, ::fs::Status::OK),
                    std::make_tuple("./var/log", "messages", 2, ::fs::Status::OK),
                    std::make_tuple("./../usr/share", "...ezrrete        rtert-----reteezrz.errte", 2, ::fs::Status::OK),
                    std::make_tuple("../lib/modules", "...aaa.bbb.c.d.e.s       .f.e.q.z.er.", 0, ::fs::Status::OK),
                    std::make_tuple("srv/http", "index.html", 1, ::fs::Status::OK),
                    std::make_tuple("home/user", "Pictures", 0, ::fs::Status::OK),
                    std::make_tuple("/lib/modules", "kernel", 2, ::fs::Status::OK)
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusInvalidEntryName,
                FSPathInsertStringAtPos,
                testing::Values(
                    std::make_tuple("/tmp_fs", "/etc", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs", "et/c", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/aaa/bbb", "/ccc", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME), // this should not work
                    std::make_tuple("/aaa/bbb", "c\\/\\cc", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/aaa/bbb", "/cc\"c", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/aaa/bbb", "cc></c", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "Пр/оекты", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "/Проекты", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/home/user", "doc/umen<>ts", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/var/log", "/s\\y<s>l\"o /  -|g", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/local", "b*/in", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/etc", "pas|sw/*d", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/etc", "/passwd", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/srv/http", "public_htm:l/", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/home/user", "Downlo:/ds", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/var/www", "ht/ml", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/lib", "pyth/on3:8", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/lib", "/python3.8", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/share", "/fonts", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/etc/systemd", "s|y/s/t&em", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs/complex-dir-name", "subdi//r", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("usrlocal", "i:\"/nclude", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/var/log", "/me<>ssages/", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/share", "fo|?*&nts/", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/lib/modules", "mo/////dule1", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/srv/http", "/index:html", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/home/user", "Pictu*/*-**res", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/var/www", "in/dex*php", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/lib/modules", "//kernel", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/lib/modules", "//ker/nel", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/usr/lib", "lib/:1", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/etc/systemd", "ser//vice1", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs/complex-dir-name", "/subdir2", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs/complex-dir-name", "s/ubdir2", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs/complex-dir-name", "//subdir2", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/tmp_fs/complex-dir-name", "//su/bdir2", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple(std::nullopt, "/entry3", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple(std::nullopt, "entr~~~/~~y3", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/path/to/directory", "~.ent/ry4", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", ":ent/ry5", 10, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/path/to/directory", "entr/y|9", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/path/to/directory", "entry|1/0", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/path/to/directory", "en/try|11", 3, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("./var/log", "mess>/>ages", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("./../usr/share", "/...ezrrete        rtert-----reteezrz.errte", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("./../usr/share", "...ezrretertert-----reteezrz.errte/", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("../lib/modules", "/..:.aaa.bbb.c.d.e.s.f.e.q.z.er.", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("srv/http", "/index~html", 1, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("home/user", "Pictu/res&", 0, ::fs::Status::E_PATH_INVALID_ENTRY_NAME),
                    std::make_tuple("/lib/modules", "/kernel", 2, ::fs::Status::E_PATH_INVALID_ENTRY_NAME)

                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingStatusInvalidIndex,
                FSPathInsertStringAtPos,
                testing::Values(
                    std::make_tuple("/tmp_fs", "etc", 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/aaa/bbb", "ccc", 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/aaa/bbb", "ccc", 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/aaa/bbb", "ccc", 6, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/share", "locale", 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple(std::nullopt, "aaa", 1, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb", "Проекты", 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/home/user", "documents", 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/var/log", "syslog", 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/local", "bin", 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/etc", "passwd", 3, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/opt/software", "config", 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/share", "locale", 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/lib/modules", "kernel", 202, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/srv/http", "public_html", 1000, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/home/user", "Downloads", 40, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/var/www", "html", 105, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/lib", "python3.8", 55, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/etc/systemd", "system", 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/tmp_fs/complex-dir-name", "subdir", 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/local", "include", 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/etc", "hosts", 3, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/var/log", "messages", 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/share", "fonts", 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/lib/modules", "module1", 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/srv/http", "index.html", 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/home/user", "Pict          ures", 120, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/var/www", "index.php", 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/usr/lib", "lib1", 20, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/etc/systemd", "service1", 50, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/tmp_fs/complex-dir-name", "subdir2", 20, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/tmp_fs/complex-dir-name", "subdir2", 20, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple(std::nullopt, ".entry1", 40, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/path/to/directory", ".entry2", 78, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple(std::nullopt, "entry3", 2, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/path/to/directory", "..entry4", 10, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "entry5", 12, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("path/to/directory", "entry9", 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/path/to/directory", "entry10", 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("/path/to/directory", "entry11", 6, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("./var/log", "messages", 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("./../usr/share", "...ezrrete        rtert-----reteezrz.errte", 6, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("../lib/modules", "module1", 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("../lib/modules", "...aaa.bbb.c.d.e.s       .f.e.q.z.er.", 5, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("srv/http", "index.html", 4, ::fs::Status::E_PATH_INVALID_INDEX),
                    std::make_tuple("home/user", "Pictures", 4, ::fs::Status::E_PATH_INVALID_INDEX)
                )
            );
        } // namespace Path
    } // namespace fs
} // namespace test
