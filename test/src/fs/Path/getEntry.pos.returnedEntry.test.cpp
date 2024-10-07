/**
 * @file getEntry.pos.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-06
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
#include <limits>

#include <iostream>
#include <cstdint>

namespace test {
    namespace fs {
        namespace Path {

            using FSPathGetEntryPosParam = std::tuple<
                std::optional<std::string>, // original path          
                std::size_t, // wanted pos                      
                ::fs::Entry // expeced entry
            >;

            class FSPathGetEntryPosMethod : public ::testing::TestWithParam<FSPathGetEntryPosParam> {
            protected:
                std::vector<::fs::Path> _instances;

                FSPathGetEntryPosMethod(void) :
                _instances(::test::fs::Path::Helper::create(std::get<0>(GetParam())))
                {}
            };

            TEST_P(FSPathGetEntryPosMethod, ReturnsGivenEntry) {
                std::size_t pos = std::get<1>(GetParam());

                for (const ::fs::Path &instance : _instances) {
                    std::cout << "Actual entry name=" << instance.getEntry(pos).getName() << " expected entry name=" << std::get<2>(GetParam()).getName() << std::endl;
                    EXPECT_EQ(instance.getEntry(pos), std::get<2>(GetParam()));
                }
            };

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenVariousPath,
                FSPathGetEntryPosMethod,
                testing::Values(
                    std::make_tuple("../../tests/assets/sym_link", 4, Helper::getEntryFromPath("../../tests/assets/sym_link/")),
                    std::make_tuple("../../tests/assets/sym_link", 4, Helper::getEntryFromPath("../../tests/assets/sym_link")),
                    std::make_tuple("../../tests/assets/sym_link", 0, Helper::getEntryFromPath("../")),
                    std::make_tuple("../../tests/assets/sym_link", 0, Helper::getEntryFromPath("..")),
                    std::make_tuple("../../tests/assets/sym_link", 1, Helper::getEntryFromPath("../..")),
                    std::make_tuple("../../tests/assets/sym_link", 1, Helper::getEntryFromPath("../../")),
                    std::make_tuple("../../tests/assets/sym_link", 2, Helper::getEntryFromPath("../../tests")),
                    std::make_tuple("../../tests/assets/sym_link", 2, Helper::getEntryFromPath("../../tests/assets/sym_link", 2)),
                    std::make_tuple("../../tests/assets/sym_link", 3, Helper::getEntryFromPath("../../tests/assets")),
                    std::make_tuple("../../tests/assets/sym_link", 45, ::fs::Entry()),
                    std::make_tuple("../../tests/assets/../../tests/assets/!@#$%^&*().!@#$%^&*()", 8, Helper::getEntryFromPath("../../tests/assets/!@#$%^&*().!@#$%^&*()")),
                    std::make_tuple("../../tests/assets/../../tests/assets/!@#$%^&*().!@#$%^&*()", 0, Helper::getEntryFromPath("../")),
                    std::make_tuple("../../tests/assets/../../tests/assets/!@#$%^&*().!@#$%^&*()", 60, ::fs::Entry()),
                    std::make_tuple("../../tests/assets/json/valid/basic.json", 6, Helper::getEntryFromPath("../../tests/assets/json/valid/basic.json")),
                    std::make_tuple("../../tests/assets/json/invalid/missingClosing.json", 6, Helper::getEntryFromPath("../../tests/assets/json/invalid/missingClosing.json")),
                    std::make_tuple("../../tests/assets", 3, Helper::getEntryFromPath("../../tests/assets/")),

                    std::make_tuple("etc", 0, Helper::getEntryFromPath("etc")),
                    std::make_tuple("etc", 1, ::fs::Entry()),
                    std::make_tuple("etc", 1064, ::fs::Entry()),
                    std::make_tuple("etc", std::numeric_limits<std::size_t>::max(), ::fs::Entry()),
                    std::make_tuple("/tmp_fs", 0, Helper::getEntryFromPath("/tmp_fs/")),
                    std::make_tuple("/aaa/bbb", 1, Helper::getEntryFromPath("aaa/bbb")),
                    std::make_tuple("/aaa/bbb", 0, Helper::getEntryFromPath("aaa/bbb/aaa")),
                    std::make_tuple("/aaa/bbb", 10, ::fs::Entry()),
                    std::make_tuple("/aaa/bbb", 10, Helper::getEntryFromPath("aaa/bbb/aaa", 78)),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb/Проекты", 2, Helper::getEntryFromPath("/tmp_fs_oojopjop99---/bbb/Проекты")),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb/Проекты", 2, Helper::getEntryFromPath("../zijerizjrpaokporkezporknnrejnt/Проекты")),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb/Проекты", 2, Helper::getEntryFromPath("./zijerizjrpaokporkezporknnrejnt/Проекты")),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb/Проекты", 0, Helper::getEntryFromPath("./zijerizjrpaokporkezporknnrejnt/tmp_fs_oojopjop99---")),
                    std::make_tuple("/tmp_fs_oojopjop99---/bbb/Проекты", 1, Helper::getEntryFromPath("./././././/////bbb/")),
                    std::make_tuple("python3.8", 0, Helper::getEntryFromPath("python3.8")),
                    std::make_tuple("python3.8", 10, ::fs::Entry()),
                    std::make_tuple("/tmp_fs/complex-dir-name", 1, Helper::getEntryFromPath("/tmp_fs/complex-dir-name")),
                    std::make_tuple(".entry1", 0, Helper::getEntryFromPath(".entry1")),
                    std::make_tuple("/path/to/directory/..entry4", 2, Helper::getEntryFromPath("/path/to/directory/..entry4", 2)),
                    std::make_tuple("/path/to/directory/..entry4", 3, Helper::getEntryFromPath("/path/to/directory/..entry4", 3)),
                    std::make_tuple("/path/to/directory/..entry4", 3, Helper::getEntryFromPath("..entry4", 0)),
                    std::make_tuple("./var/log", 0, Helper::getEntryFromPath("./var/log", 0)),
                    std::make_tuple("./var/log", 0, Helper::getEntryFromPath(".")),
                    std::make_tuple("./var/log", 1, Helper::getEntryFromPath("./var", 1)),
                    std::make_tuple("./var/log", 1, Helper::getEntryFromPath("./var/log", 1)),
                    std::make_tuple("./../usr/share", 0, Helper::getEntryFromPath("./../usr/share", 0)),
                    std::make_tuple("./../usr/share", 3, Helper::getEntryFromPath("./../usr/share", 3)),
                    std::make_tuple("./../usr/share/...ezrrete        rtert-----reteezrz.errte", 0, Helper::getEntryFromPath("./../usr/share/...ezrrete        rtert-----reteezrz.errte", 0)),
                    std::make_tuple("../lib/modules", 0, Helper::getEntryFromPath("..")),
                    std::make_tuple("../lib/modules", 0, Helper::getEntryFromPath("..", 0)),
                    std::make_tuple("../lib/modules", 0, Helper::getEntryFromPath("../lib/modules", 0)),
                    std::make_tuple("../lib/modules", 1, Helper::getEntryFromPath("../lib/modules", 1)),
                    std::make_tuple("../lib/modules", 2, Helper::getEntryFromPath("../lib/modules", 2)),
                    std::make_tuple("index.html", 0, Helper::getEntryFromPath("index.html")),
                    std::make_tuple("", 0, ::fs::Entry()),
                    std::make_tuple(std::nullopt, 0, ::fs::Entry()),
                    std::make_tuple("", 100, ::fs::Entry()),
                    std::make_tuple(std::nullopt, 1000, ::fs::Entry()),
                    std::make_tuple("", 70, ::fs::Entry()),
                    std::make_tuple(std::nullopt, 70, ::fs::Entry())
                )
            );

        } // namespace Path
    } // namespace fs
} // namespace test
