#include "Status.hpp"
#include "_private/_File.hpp"
#include "path/path.hpp"

#include <iostream>
#include <stdexcept>

namespace liminal_fs {
    namespace _private {
        
        _File::_File(const std::string &path) :
        _name{this->__load_name(path)},
        _registered_path{path},
        _absolute_path{this->__load_abolute_path(path)},
        _extension{this->__load_extension(path)}
        {
        }


        // Private :
        const std::string _File::__load_name(const std::string &path) {
            std::string res{""};

            if (path::get_file_name(res, path) != OK) {
                throw std::runtime_error("Failed to get file name");
            }
            return res;
        }

        const std::string _File::__load_abolute_path(const std::string &path) {
            std::string res{""};

            if (path::get_absolute_path(res, path) != OK) {
                throw std::runtime_error("Failed to get file absolute path");
            }
            return res;
        }

        const std::string __load_extension(const std::string &path) {
            std::string res{""};

            if (path::get_file_extension(res, path) != OK) {
                throw std::runtime_error("Failed to get file absolute path");
            }
            return res;
        }

    }
}