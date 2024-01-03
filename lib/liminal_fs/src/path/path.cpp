/**
 * @file path.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "path/path.hpp"
#include "Status.hpp"
#include "FileType.hpp"

#include <filesystem>

namespace liminal_fs {
    namespace path {

        Status get_path_status(const path_t &path) {
            Status tmp_status = Status::NOK;
            bool tmp_res = false;

            if ((tmp_status = path_exists(tmp_res, path)) != Status::OK) {
                return tmp_status;
            }
            if (tmp_res == false) {
                return Status::PATH_NO_TARGET;
            }
            return Status::OK;
        }

        Status get_file_name(std::string &res, const path_t &path) {
            Status tmp_status = Status::NOK;
            if ((tmp_status = get_path_status(path)) != Status::OK) {
                return tmp_status;
            }
            res = std::filesystem::path(path).filename().string();
            return Status::OK;
        }

        Status get_file_extension(std::string &res, const path_t &path) {
            Status tmp_status = Status::NOK;
            if ((tmp_status = get_path_status(path)) != Status::OK) {
                return tmp_status;
            }
            res = std::filesystem::path(path).extension().string();
            return Status::OK;
        }

        Status get_absolute_path(std::string &res, const path_t &relative_path) {
            Status tmp_status = Status::NOK;
            if ((tmp_status = get_path_status(relative_path)) != Status::OK) {
                return tmp_status;
            }
            res = std::filesystem::absolute(std::filesystem::path(relative_path)).string();
            return Status::OK;
        }

        Status path_exists(bool &res, const path_t &path) {
            bool temp_res = false;
            if (str_is_path(temp_res, path) != Status::OK) {
                return Status::STR_IS_NOT_A_PATH;
            }
            res = std::filesystem::exists(std::filesystem::path(path));
            return Status::OK;
        }

        Status str_is_path(bool &res, const path_t &path) {
            try {
                std::filesystem::path check(path);
                res = true;
            } catch (const std::exception &e) {
                res = false;
            }
            return Status::OK;
        }

    } // namespace path
} // namespace liminal_fs
