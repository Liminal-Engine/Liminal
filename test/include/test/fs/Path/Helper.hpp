/**
 * @file Helper.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-04
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_TEST_FS_PATH_HELPER_HPP_
#define LIMINAL_TEST_FS_PATH_HELPER_HPP_

#include <fs/Path.hpp>

#include <vector>
#include <optional>
#include <utility>
#include <string>

namespace test {
    namespace fs {
        namespace Path {
            class Helper {
                public:
                    static void addEntries(
                        std::vector<::fs::Path> &instances,
                        const std::vector<std::pair<std::variant<std::string, ::fs::Entry>, std::optional<std::size_t>>> &entries
                    );

                    static void cleanIfNeeded(std::vector<::fs::Path> &instances, const bool &clean);

                    static std::vector<::fs::Path> create(const std::optional<std::string> &pathStr);

                    static ::fs::Entry getEntryFromPath(const std::string &strPath);

                    static ::fs::Entry getEntryFromPath(const std::string &strPath, const std::size_t &pos);

                    static std::string createCleanedStrPath(const std::string &strPath);
            };         
        } // namespace Path
    }
} // namespace test


#endif // LIMINAL_TEST_FS_PATH_HELPER_HPP_