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
#include "types.hpp"

#include "InFile.hpp"

#include <iostream>

namespace liminal_json_io {
    namespace _private {

        // Public :
        Status _JSON::parse(const std::string &path) {
            _lexing::_types::_Tokens_t tokens = _lexing::_processLexing(path);
            std::size_t index{0};
            types::JsonValue jsonValue = _parsing::_processParsing(tokens.at(0), tokens, index);
        }

    } // namespace _private
} // namespace liminal_json_io
