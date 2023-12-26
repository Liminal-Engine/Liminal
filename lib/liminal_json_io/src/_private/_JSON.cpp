#include "_private/_JSON.hpp"
#include "constants.hpp"
#include "types.hpp"

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
            _lexing::_tokens_t tokens = _lexing::_processLexing(this->__getFileContent(this->_path));
            // Once we have the list of tokens, the goal of the parsing is to separate each "key"/"value" pairs and wheter they are objects and/or arrays
            this->__processParsing(tokens, true);
        }

        // Private :
        _lexing::_tokens_t _JSON::__processParsing(_lexing::_tokens_t &tokens, const bool &isRoot) {
            
            auto currentToken = _lexing::getStringToken(tokens.at(1))->getValue();
            std::cout << currentToken << std::endl;
            exit(0);
            // if (isRoot and currentToken->getType() == types::TOKEN and currentToken->get().getValue())


            return _lexing::_tokens_t();
        }

        _lexing::_tokens_t __parseObject(_lexing::_tokens_t &tokens) {
            (void)tokens;
            return _lexing::_tokens_t();
        }

        _lexing::_tokens_t __parseArray(_lexing::_tokens_t &tokens) {
            (void)tokens;
            return _lexing::_tokens_t();
        }

        std::string _JSON::__getFileContent(const std::string &path) {
            std::string extension{""};

            if (liminal_fs::path::get_file_extension(extension, path) != liminal_fs::Status::OK) {
                throw std::runtime_error("Failed to load JSON file : " + path);
            }
            std::cout << extension << std::endl;
            if (extension != std::string(std::string(".") + std::string(constants::JSON_FILE_EXTENSION))) {
                throw std::runtime_error("Error : file is not a JSON");
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