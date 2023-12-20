#include "_private/_JSON.hpp"
#include "constants.hpp"

#include "InFile.hpp"
#include "path/path.hpp"

#include <stdexcept>

namespace liminal_json_io {
    namespace _private {

        _JSON::_JSON(const std::string &path) :
        _tokens{_lexing::_process_lexing(this->__load_json_string(path))}
        {

        }

        // Private :
        std::string _JSON::__load_json_string(const std::string &path) {
            std::string extension{""};

            if (liminal_fs::path::get_file_extension(extension, path) != liminal_fs::Status::OK) {
                throw std::runtime_error("Failed to laod JSON file");
            }
            if (extension != constants::JSON_FILE_EXTENSION) {
                throw std::runtime_error("Erorr : file is not a JSON");
            }
            liminal_fs::InFile jsonFile(path);
            if (jsonFile.open() != liminal_fs::Status::OK) {
                throw std::runtime_error("Failed to open JSON file : " + path);
            }
            if (jsonFile.read() != liminal_fs::Status::OK) {
                throw std::runtime_error("Failed to read JSON file : " + path);
            }
            if (jsonFile.close() != liminal_fs::Status::OK) {
                throw std::runtime_error("Failed to close JSON file : " + path);
            }
            return jsonFile.get_content();
        }

    } // namespace _private
} // liminal_json_io