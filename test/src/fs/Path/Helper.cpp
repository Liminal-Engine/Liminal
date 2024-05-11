/**
 * @file Helper.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-04
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "test/fs/Path/Helper.hpp"

#include <iostream>

namespace test {
    namespace fs {
        namespace Path {

            void Helper::addEntries(
                std::vector<::fs::Path> &instances,
                const std::vector<std::pair<std::variant<std::string, ::fs::Entry>, std::optional<std::size_t>>> &entries
            ) {
                for (::fs::Path &path : instances) {
                    for (const auto &[entry, index] : entries) {
                        std::visit([&](auto&& arg) {
                            if (index.has_value()) path.insert(arg, index.value());
                            else path.insert(arg);
                        }, entry);
                    }
                }
            }

            void Helper::cleanIfNeeded(std::vector<::fs::Path> &instances, const bool &clean) {
                if (clean) for (::fs::Path &path : instances) path.clean();
            }

            std::vector<::fs::Path> Helper::create(const std::optional<std::string> &pathStr) {
                std::vector<::fs::Path> res{};
                if (pathStr.has_value()) {
                    res.push_back(::fs::Path{pathStr.value()});
                    // res.push_back(::fs::Path{res.at(0)});
                    // ::fs::Path tmpPath = res.at(0);
                    // res.push_back(tmpPath);
                } else {
                    res.push_back(::fs::Path{});
                }
                return res;
            }

            ::fs::Entry Helper::getEntryFromPath(const std::string &strPath) {
                return ::fs::Path(strPath).getEntry();
            }

            ::fs::Entry Helper::getEntryFromPath(const std::string &strPath, const std::size_t &pos) {
                return ::fs::Path(strPath).getEntry(pos);
            }

            std::string Helper::createCleanedStrPath(const std::string &strPath) {
                ::fs::Path res(strPath);

                res.clean();
                return res.toStr();
            }

        } // namespace Path
    } // namespace fs
} // namespace test
