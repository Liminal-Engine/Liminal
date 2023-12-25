#include "_private/_JSON.hpp"
#include "constants.hpp"

#include "InFile.hpp"

#include <stdexcept>

#include <iostream>

namespace liminal_json_io {
    namespace _private {

        _JSON::_JSON(const std::string &path) :
        _path(path)
        {

        }

        void _JSON::parse(void) {
            const _lexing::_tokens_t tokens = _lexing::_processLexing(this->__getFileContent(this->_path));
            std::cout << "Tokens = " << std::endl;
            for (const auto &token : tokens) {
                std::cout << "Token type = " << token->getType() << std::endl;
            }
        }

        // Private :
        std::string _JSON::__getFileContent(const std::string &path) {
            std::string extension{""};

            if (liminal_fs::path::get_file_extension(extension, path) != liminal_fs::Status::OK) {
                throw std::runtime_error("Failed to load JSON file : " + path);
            }
            std::cout << extension << std::endl;
            if (extension != std::string(std::string(".") + std::string(constants::JSON_FILE_EXTENSION))) {
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