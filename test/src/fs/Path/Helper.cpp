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
#include <filesystem>
#include <fstream>
#include <random>
#include <chrono>
#include <sstream>
#include <iomanip>

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
                return res.asStr();
            }

            void Helper::createTestFiles(const std::string &rootPath) {
                try { // TODO : changer le root dir ici
                    std::filesystem::create_directories(rootPath + "/aaa/bbb/ccc");
                    std::ofstream file1(rootPath + "/aaa/bbb/ccc/file");
                    file1.close();
                    std::ofstream file2(rootPath + "/root_file");
                    file2.close();
                } catch(const std::exception& e) {
                    std::cerr << ::fs::Path(rootPath).getEntry().getPermissions().asUnixFormat() << std::endl;
                    std::cerr << e.what() << '\n';
                }
            }

            void Helper::deleteTestFiles(const std::string &rootPath) {
                std::filesystem::remove_all(rootPath);
            }

            std::string Helper::generateUID() {
                // Get the current time since epoch in nanoseconds
                auto now = std::chrono::system_clock::now();
                auto duration = now.time_since_epoch();
                auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

                // Create a random number generator
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, 999999);

                // Generate a random number
                int random_number = dis(gen);

                // Combine the time and random number to create a UID
                std::stringstream ss;
                ss << std::hex << nanos << std::setw(6) << std::setfill('0') << random_number;

                return ss.str();
            }

        } // namespace Path
    } // namespace fs
} // namespace test
