#include "path/path.hpp"

#include <filesystem>

namespace liminal_fs {
    namespace path {

        Status get_path_status(const path_t &path) {
            Status tmp_status = NOK;
            bool tmp_res = false;

            if ((tmp_status = path_exists(tmp_res, path)) != OK) {
                return tmp_status;
            }
            if (tmp_res == false) {
                return PATH_NO_TARGET;
            }
            return OK;
        }

        Status get_file_name(std::string &res, const path_t &path) {
            Status tmp_status = NOK;
            if ((tmp_status = get_path_status(path)) != OK) {
                return tmp_status;
            }
            res = std::filesystem::path(path).filename().string();
            return OK;
        }

        Status get_file_extension(std::string &res, const path_t &path) {
            Status tmp_status = NOK;
            if ((tmp_status = get_path_status(path)) != OK) {
                return tmp_status;
            }
            res = std::filesystem::path(path).extension().string();
            return OK;
        }

        Status get_absolute_path(std::string &res, const path_t &relative_path) {
            Status tmp_status = NOK;
            if ((tmp_status = get_path_status(relative_path)) != OK) {
                return tmp_status;
            }
            res = std::filesystem::absolute(std::filesystem::path(relative_path)).string();
            return OK;
        }

        Status path_exists(bool &res, const path_t &path) {
            bool temp_res = false;
            if (str_is_path(temp_res, path) != OK) {
                return STR_IS_NOT_A_PATH;
            }
            res = std::filesystem::exists(std::filesystem::path(path));
            return OK;
        }

        Status str_is_path(bool &res, const path_t &path) {
            try {
                std::filesystem::path check(path);
                res = true;
            } catch (const std::exception &e) {
                res = false;
            }
            return OK;
        }

    } // namespace path
} // namespace liminal_fs
