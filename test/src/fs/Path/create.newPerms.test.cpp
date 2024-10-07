/**
 * @file create.newPerms.test.cpp
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
            using FSPathCreateNewPermsParam = std::tuple<
                std::string, // path to build instances from, if has no value, constructor fs::Path{} will be used
                ::fs::Entry::Type, // type to create
                bool, // create parents
                ::fs::Permission, // permission to give
                std::optional<::fs::Path>, //symbolic link target
                ::fs::Permission // expected existence
            >;

            class FSPathCreateNewPermsMethod : public ::testing::TestWithParam<FSPathCreateNewPermsParam> {
                protected:
                    std::vector<::fs::Path> _instances;

                    FSPathCreateNewPermsMethod(void) :
                    _instances{::test::fs::Path::Helper::create(std::get<0>(GetParam()))}
                    {
                        for (::fs::Path &_instance : _instances) {
                            if (std::get<4>(GetParam()).has_value())
                                _instance.create(std::get<1>(GetParam()), std::get<2>(GetParam()), std::get<3>(GetParam()), std::get<4>(GetParam()).value()), std::get<5>(GetParam());
                            else
                                _instance.create(std::get<1>(GetParam()), std::get<2>(GetParam()), std::get<3>(GetParam())), std::get<5>(GetParam());
                        }
                    }

                    ~FSPathCreateNewPermsMethod()
                    {
                        for (const ::fs::Path &instance : _instances)
                            ::remove(instance.asStr().c_str());
                    }
            };

            TEST_P(FSPathCreateNewPermsMethod, ReturnGivenStatusAndProduceGivenPath) {
                struct stat tmp;
                for (const ::fs::Path &instance : _instances) {
                    EXPECT_EQ(instance.getEntry().getPermissions(), std::get<5>(GetParam()));
                    if (::stat(instance.asStr().c_str(), &tmp) != 0)
                        throw std::runtime_error("This error was thrown inside the test body. Failed to stat path : " + instance.asStr());
                    EXPECT_EQ(instance.getEntry().getPermissions(), ::fs::Permission(tmp.st_mode));
                }
            }

            INSTANTIATE_TEST_SUITE_P(
                WhenGivenVariousPath,
                FSPathCreateNewPermsMethod,
                testing::Values(
                    std::make_tuple("../../test/assets/tmp_fs/create/*", ::fs::Entry::Type::DIRECTORY, false, ::fs::Permission(0777), std::nullopt, ::fs::Permission(0777)),
                    std::make_tuple("../../test/assets/tmp_fs/create/rrr/bbb", ::fs::Entry::Type::DIRECTORY, true, ::fs::Permission(0777), std::nullopt, ::fs::Permission(0777)),
                    std::make_tuple("../../test/assets/tmp_fs/create/eee/87--.c", ::fs::Entry::Type::REGULAR_FILE, true, ::fs::Permission(0777), std::nullopt, ::fs::Permission(0777)),
                    std::make_tuple("../../test/assets/tmp_fs/create/aaa/bbb/ccc", ::fs::Entry::Type::DIRECTORY, true, ::fs::Permission(0777), std::nullopt, ::fs::Permission(0777)),
                    std::make_tuple("../../test/assets/tmp_fs/create/eee/87--.c", ::fs::Entry::Type::REGULAR_FILE, true, ::fs::Permission(0655), std::nullopt, ::fs::Permission(0655)),
                    std::make_tuple("../../test/assets/tmp_fs/create/fff", ::fs::Entry::Type::SYM_LINK, true, ::fs::Permission(0777), std::nullopt, ::fs::Permission(0777)),
                    std::make_tuple("../../test/assets/tmp_fs/create/hhh/bbb/ddd", ::fs::Entry::Type::DIRECTORY, true, ::fs::Permission(0777), std::nullopt, ::fs::Permission(0777)),
                    std::make_tuple("../../test/assets/tmp_fs/create/yyy/87--.cpp", ::fs::Entry::Type::REGULAR_FILE, true, ::fs::Permission(0777), std::nullopt, ::fs::Permission(0777)),
                    std::make_tuple("../../test/assets/tmp_fs/create/jjj___iii.cpp", ::fs::Entry::Type::REGULAR_FILE, true, ::fs::Permission(0777), std::nullopt, ::fs::Permission(0777)),
                    std::make_tuple("../../test/assets/tmp_fs/create//zer", ::fs::Entry::Type::SYM_LINK, false, ::fs::Permission(0777), std::nullopt, ::fs::Permission(0777)),
                    std::make_tuple("../../test/assets/tmp_fs/create/147/87--.c", ::fs::Entry::Type::REGULAR_FILE, true, ::fs::Permission(0555), std::nullopt, ::fs::Permission(0555)),
                    std::make_tuple("../../test/assets/tmp_fs/create/", ::fs::Entry::Type::DIRECTORY, true, ::fs::Permission(0777), std::nullopt, ::fs::Permission(0777)),
                    std::make_tuple("../../test/assets/tmp_fs/0600", ::fs::Entry::Type::REGULAR_FILE, false, ::fs::Permission(0600), std::nullopt, ::fs::Permission(0600))
                )
            );
        } // namespace Path
    } // namespace fs
} // namespace test
