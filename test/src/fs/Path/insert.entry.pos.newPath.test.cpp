/**
 * @file insert.entry.pos.newPath.test.cpp
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

            using FSPathInsertEntryAtPosNewPathParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                ::fs::Entry, // add string entry ...
                std::size_t, // at given pos
                ::fs::Path // expected newPath
            >;
            class FSPathInsertEntryAtPosNewPath : public ::testing::TestWithParam<FSPathInsertEntryAtPosNewPathParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathInsertEntryAtPosNewPath(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathInsertEntryAtPosNewPath, GivesExpectingPath) {
                ::fs::Entry entry = std::get<1>(GetParam());
                std::size_t pos = std::get<2>(GetParam());

                for (::fs::Path &instance : _instances) {
                    instance.insert(entry, pos);
                    EXPECT_EQ(instance, std::get<3>(GetParam()));
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingEquality,
                FSPathInsertEntryAtPosNewPath,
                testing::Values(
                    std::make_tuple("/tmp", Helper::getEntryFromPath("."), 1, ::fs::Path("/tmp/././././.")),
                    std::make_tuple("/tmp", Helper::getEntryFromPath("etc"), 1, ::fs::Path("/tmp/etc")),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("aaa/ddd/--/89/ccc"), 1, ::fs::Path("/aaa/ccc/./bbb//")),
                    std::make_tuple("/aaa/bbb", Helper::getEntryFromPath("ccc"), 2, ::fs::Path("/aaa/bbb/ccc/./.././ccc/./.")),
                    std::make_tuple("/tmp_oojopjop99---/bbb", Helper::getEntryFromPath("Проекты"), 2, ::fs::Path("/tmp_oojopjop99---/bbb/Проекты/./")),
                    std::make_tuple("/tmp_oojopjop99---/bbb", Helper::getEntryFromPath("Проекты"), 1, ::fs::Path("/tmp_oojopjop99---//Проекты/bbb/./../../../tmp_oojopjop99---/Проекты/bbb/./././")),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("documents"), 2, ::fs::Path("/home/user/documents")),
                    std::make_tuple("/var/log", Helper::getEntryFromPath("./a/b/c/syslog"), 2, ::fs::Path("/var/log/syslog/../syslog")),
                    std::make_tuple("/usr/local", Helper::getEntryFromPath("bin"), 1, ::fs::Path("/usr/bin/local")),
                    std::make_tuple("/etc", Helper::getEntryFromPath("passwd"), 1, ::fs::Path("/etc/passwd/././././../passwd/./")),
                    std::make_tuple("/opt/software", Helper::getEntryFromPath("config"), 2, ::fs::Path("/opt/software/config/././aaa/bbb/../../././")),
                    std::make_tuple("/srv/http", Helper::getEntryFromPath("public.html"), 1, ::fs::Path("/srv/public.html/http/.")),
                    std::make_tuple("/usr/lib", Helper::getEntryFromPath("python3.8"), 2, ::fs::Path("/usr/lib/python3.8")),
                    std::make_tuple("/etc/systemd", Helper::getEntryFromPath("system.cpp"), 2, ::fs::Path("/etc/systemd/system.cpp")),
                    std::make_tuple("/tmp/complex-dir-name", Helper::getEntryFromPath("subdir"), 2, ::fs::Path("/tmp/complex-dir-name/subdir////..////../complex-dir-name/subdir///.///.//////../subdir///////.////")),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("module1"), 1, ::fs::Path("/lib/module1/modules//../module2/aaa/bbb/../../../modules")),
                    std::make_tuple("/srv/http", Helper::getEntryFromPath("index.html"), 2, ::fs::Path("/srv/http/index.html/777/888/../..")),
                    std::make_tuple("/home/user", Helper::getEntryFromPath("Pict          ures"), 2, ::fs::Path("/home/user/Pict          ures/aaa/bbb/ccc////./../../../../Pict          ures")),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("entry3"), 0, ::fs::Path("./entry3")),
                    std::make_tuple(std::nullopt, Helper::getEntryFromPath("d/a/fg/r/entry3"), 0, ::fs::Path("./aaa/.////bbb/../../entry3/././../entry3/.////////")),
                    std::make_tuple("/path/to/directory", Helper::getEntryFromPath(".././../..entry4"), 3, ::fs::Path("/path/to/directory/..entry4/aaa/././bbb/../../../../directory/././//..entry4/././//.")),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", Helper::getEntryFromPath("entry5"),  2, ::fs::Path("/p/a/entry5/t/h/to/d/i/r/e/ctory")),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", Helper::getEntryFromPath("entry5"), 3, ::fs::Path("/p/a/t/h/to/d/i/r/e/ctory/../../../../../../../../../..//p/a/t/entry5/h/to/d/i/r/e/ctory/.//")),
                    std::make_tuple("./var/log", Helper::getEntryFromPath("messages"), 3, ::fs::Path("./var/log/messages/../../../var/log/messages/./////./.")),
                    std::make_tuple("./../usr/share", Helper::getEntryFromPath("...ezrrete        rtert-----reteezrz.errte"), 4, ::fs::Path("./../usr/share/...ezrrete        rtert-----reteezrz.errte")),
                    std::make_tuple("../lib/modules", Helper::getEntryFromPath("...aaa.bbb.c.d.e.s       .f.e.q.z.er."), 3, ::fs::Path("../lib/modules/...aaa.bbb.c.d.e.s       .f.e.q.z.er./.")),
                    std::make_tuple("srv/http", Helper::getEntryFromPath("index.html"), 2, ::fs::Path("./srv/http/index.html///.////.///")),
                    std::make_tuple("home/user", Helper::getEntryFromPath("Pictures"), 0, ::fs::Path("./Pictures/home/user//.")),
                    std::make_tuple("/lib/modules", Helper::getEntryFromPath("/aaa/ccc/bbb/kernel"), 1, ::fs::Path("///lib/kernel/.///modules/"))
                )
            );

        } // namespace Path
    } // namespace fs
} // namespace test
