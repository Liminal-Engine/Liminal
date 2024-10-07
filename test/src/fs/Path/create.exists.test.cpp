/**
 * @file create.exists.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-20
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
#include <stdio.h>

namespace test {
    namespace fs {
        namespace Path {
            using FSPathCreateTestExistsParam = std::tuple<
                std::string, // path to build instances from, if has no value, constructor fs::Path{} will be used
                ::fs::Entry::Type, // type to create
                bool, // create parents
                ::fs::Permission, // permission to give
                std::optional<::fs::Path>, //symbolic link target
                bool // expected existence
            >;

            class FSPathCreateTestExistsMethod : public ::testing::TestWithParam<FSPathCreateTestExistsParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathCreateTestExistsMethod(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {
                        for (::fs::Path &_instance : _instances) {
                            if (std::get<4>(GetParam()).has_value())
                                _instance.create(std::get<1>(GetParam()), std::get<2>(GetParam()), std::get<3>(GetParam()), std::get<4>(GetParam()).value()), std::get<5>(GetParam());
                            else
                                _instance.create(std::get<1>(GetParam()), std::get<2>(GetParam()), std::get<3>(GetParam())), std::get<5>(GetParam());
                        }
                    }

                    ~FSPathCreateTestExistsMethod()
                    {
                        for (const ::fs::Path &instance : _instances)
                            ::remove(instance.asStr().c_str());
                    }
            };

            TEST_P(FSPathCreateTestExistsMethod, ReturnGivenStatusAndProduceGivenPath) {
                for (const ::fs::Path &instance : _instances)
                    EXPECT_EQ(instance.exists(), std::get<5>(GetParam()));
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenExpectingExistance,
                FSPathCreateTestExistsMethod,
                testing::Values(
                    std::make_tuple("../../test/assets/tmp_fs/create/*", ::fs::Entry::Type::DIRECTORY, false, ::fs::Permission(0777), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/create/aaa/bbb", ::fs::Entry::Type::DIRECTORY, true, ::fs::Permission(0777), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/create/eee/87--.c", ::fs::Entry::Type::REGULAR_FILE, true, ::fs::Permission(0777), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/create/aaa/bbb/ccc", ::fs::Entry::Type::DIRECTORY, true, ::fs::Permission(0777), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/create/fff", ::fs::Entry::Type::SYM_LINK, true, ::fs::Permission(0777), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/create/hhh/bbb/ddd", ::fs::Entry::Type::DIRECTORY, true, ::fs::Permission(0777), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/create/yyy/87--.cpp", ::fs::Entry::Type::REGULAR_FILE, true, ::fs::Permission(0777), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/create/jjj___iii.cpp", ::fs::Entry::Type::REGULAR_FILE, true, ::fs::Permission(0777), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/create//zer", ::fs::Entry::Type::SYM_LINK, false, ::fs::Permission(0777), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/create/147/87--.c", ::fs::Entry::Type::REGULAR_FILE, true, ::fs::Permission(0555), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/create/", ::fs::Entry::Type::DIRECTORY, true, ::fs::Permission(0777), std::nullopt, true),
                    std::make_tuple("../../test/assets/tmp_fs/", ::fs::Entry::Type::REGULAR_FILE, false, ::fs::Permission(0600), std::nullopt, true)
                )
            );

            INSTANTIATE_TEST_SUITE_P(
                WhenNotExpectingExistence,
                FSPathCreateTestExistsMethod,
                testing::Values(
                    std::make_tuple("../../test/assets/tmp_fs/create/88888/kekk/ezrzre", ::fs::Entry::Type::DIRECTORY, false, ::fs::Permission(0777), std::nullopt, false),
                    std::make_tuple("../../test/assets/tmp_fs/../../assets/tmp_fs../tmp_fs//create/oooooooooooooooooooooooo/aa", ::fs::Entry::Type::REGULAR_FILE, false, ::fs::Permission(0600), std::nullopt, false),
                    std::make_tuple("../../test/assets/tmp_fs/create/socket_attempt", ::fs::Entry::Type::SOCKET, true, ::fs::Permission(0777), std::nullopt, false),
                    std::make_tuple("../../test/assets/tmp_fs/../../assets/tmp_fs/../tmp_fs/create/block_device_attempt", ::fs::Entry::Type::BLOCK_DEVICE, false, ::fs::Permission(0666), std::nullopt, false),
                    std::make_tuple("../../test/assets/tmp_fs/../../assets/tmp_fs/../tmp_fs/create/character_device_attempt", ::fs::Entry::Type::CHARACTER_DEVICE, false, ::fs::Permission(0666), std::nullopt, false)
                )
            );
        } // namespace Path
    } // namespace fs
} // namespace test
