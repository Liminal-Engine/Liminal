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

            using FSPathInsertStringNewPathParam = std::tuple<
                std::optional<std::string>, // path to build instances from, if has no value, constructor ::fs::Path{} will be used
                std::string, // add string entry ...
                ::fs::Path // expected newPath
            >;
            class FSPathInsertStringNewPath : public ::testing::TestWithParam<FSPathInsertStringNewPathParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathInsertStringNewPath(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {}
            };

            TEST_P(FSPathInsertStringNewPath, GivesExpectingPath) {
                std::string entry = std::get<1>(GetParam());

                for (::fs::Path &instance : _instances) {
                    instance.insert(entry);
                    EXPECT_EQ(instance, std::get<2>(GetParam()));
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingEquality,
                FSPathInsertStringNewPath,
                testing::Values(
                    std::make_tuple("/tmp", ".", ::fs::Path("/tmp/././././.")),
                    std::make_tuple("/tmp", "etc", ::fs::Path("/tmp/etc")),
                    std::make_tuple("/aaa/bbb", "ccc", ::fs::Path("/aaa/bbb/ccc/")),
                    std::make_tuple("/aaa/bbb", "ccc", ::fs::Path("/aaa/bbb/ccc/./.././ccc/./.")),
                    std::make_tuple("/tmp_oojopjop99---/bbb", "Проекты", ::fs::Path("/tmp_oojopjop99---/bbb/Проекты/./")),
                    std::make_tuple("/tmp_oojopjop99---/bbb", "Проекты", ::fs::Path("/tmp_oojopjop99---/bbb/Проекты/./../../../tmp_oojopjop99---/bbb/Проекты/./././")),
                    std::make_tuple("/home/user", "documents", ::fs::Path("/home/user/documents")),
                    std::make_tuple("/var/log", "syslog", ::fs::Path("/var/log/syslog/../syslog")),
                    std::make_tuple("/usr/local", "bin", ::fs::Path("/usr/local/bin")),
                    std::make_tuple("/etc", "passwd", ::fs::Path("/etc/passwd/././././../passwd/./")),
                    std::make_tuple("/opt/software", "config", ::fs::Path("/opt/software/config/././aaa/bbb/../../././")),
                    std::make_tuple("/usr/share", "locale", ::fs::Path("/usr/share/locale/.///./../locale/bbb/././aaa/../../../locale")),
                    std::make_tuple("/lib/modules", "kernel", ::fs::Path("/lib/modules/kernel")),
                    std::make_tuple("/srv/http", "public.html", ::fs::Path("/srv/http/public.html")),
                    std::make_tuple("/home/user", "Downloads", ::fs::Path("/home/user/Downloads")),
                    std::make_tuple("/var/www", "html", ::fs::Path("/var/www/html")),
                    std::make_tuple("/usr/lib", "python3.8", ::fs::Path("/usr/lib/python3.8")),
                    std::make_tuple("/etc/systemd", "system.cpp", ::fs::Path("/etc/systemd/system.cpp")),
                    std::make_tuple("/tmp/complex-dir-name", "subdir", ::fs::Path("/tmp/complex-dir-name/subdir////..////../complex-dir-name/subdir///.///.//////../subdir///////.////")),
                    std::make_tuple("usrlocal", "include", ::fs::Path("usrlocal/include")),
                    std::make_tuple("/etc", "hosts", ::fs::Path("/etc/hosts")),
                    std::make_tuple("/lib/modules", "module1", ::fs::Path("/lib/modules/module1/../module2/aaa/bbb/../../../module1")),
                    std::make_tuple("/srv/http", "index.html", ::fs::Path("/srv/http/index.html/777/888/../..")),
                    std::make_tuple("/home/user", "Pict          ures", ::fs::Path("/home/user/Pict          ures/aaa/bbb/ccc////./../../../../Pict          ures")),
                    std::make_tuple("/var/www", "index.php", ::fs::Path("/var/www/index.php")),
                    std::make_tuple(std::nullopt, "entry3", ::fs::Path("./entry3")),
                    std::make_tuple(std::nullopt, "entry3", ::fs::Path("./aaa/.////bbb/../../entry3/././../entry3/.////////")),
                    std::make_tuple("/path/to/directory", "..entry4", ::fs::Path("/path/to/directory/..entry4/aaa/././bbb/../../../../directory/././//..entry4/././//.")),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "entry5", ::fs::Path("/p/a/t/h/to/d/i/r/e/ctory/entry5")),
                    std::make_tuple("/p/a/t/h/to/d/i/r/e/ctory", "entry5", ::fs::Path("/p/a/t/h/to/d/i/r/e/ctory/../../../../../../../../../..//p/a/t/h/to/d/i/r/e/ctory/entry5/.//../entry5/.///")),
                    std::make_tuple("./var/log", "messages", ::fs::Path("./var/log/messages/../../../var/log/messages/./////./.")),
                    std::make_tuple("./../usr/share", "...ezrrete        rtert-----reteezrz.errte", ::fs::Path("./../usr/share/...ezrrete        rtert-----reteezrz.errte")),
                    std::make_tuple("./../usr/share", "...ezrrete        rtert-----reteezrz.errte", ::fs::Path("./../usr/share/...ezrrete        rtert-----reteezrz.errte/../../share/...ezrrete        rtert-----reteezrz.errte/.")),
                    std::make_tuple("../lib/modules", "...aaa.bbb.c.d.e.s       .f.e.q.z.er.", ::fs::Path("../lib/modules/...aaa.bbb.c.d.e.s       .f.e.q.z.er./.")),
                    std::make_tuple("../lib/modules", "...aaa.bbb.c.d.e.s       .f.e.q.z.er.", ::fs::Path("../lib/modules/...aaa.bbb.c.d.e.s       .f.e.q.z.er././../../../lib/modules/...aaa.bbb.c.d.e.s       .f.e.q.z.er.")),
                    std::make_tuple("srv/http", "index.html", ::fs::Path("./srv/http/index.html///.////.///")),
                    std::make_tuple("home/user", "Pictures", ::fs::Path("./home/user/Pictures/.")),
                    std::make_tuple("/lib/modules", "kernel", ::fs::Path("//lib/modules/kernel"))
                )
            );

        } // namespace Path
    } // namespace fs
} // namespace test
