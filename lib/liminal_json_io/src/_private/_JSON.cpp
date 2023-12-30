/**
 * @file _JSON.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_JSON.hpp"
#include "_private/_syntax.hpp"
#include "_private/_lexing/_types.hpp"
#include "_private/_lexing/_lexing.hpp"
#include "_private/_parsing/_parsing.hpp"
#include "types.hpp"//TODO : remove this include ?

#include "InFile.hpp"

#include <iostream>
#include <stdexcept>

namespace liminal_json_io {
    namespace _private {

        // Public :
        Status _JSON::parse(const std::string &path) {
            try {
                _lexing::_types::_Tokens_t tokens = _lexing::_processLexing(path);
                std::size_t index{0};
                this->_rootValue = _parsing::_processParsing(tokens.at(0), tokens, index);
                return Status::OK;
            } catch (...) {
                return Status::PARSING_ERR;
            }

        }

    } // namespace _private
} // namespace liminal_json_io
