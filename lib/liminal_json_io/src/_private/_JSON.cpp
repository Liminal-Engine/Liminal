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

#include "InFile.hpp"

#include <iostream>

namespace liminal_json_io {
    namespace _private {


        // Public :
        Status _JSON::parse(const std::string &path) {
            _lexing::_types::_Tokens_t tokens = _lexing::_processLexing(path);
            std::cout << "TOKENS = " << '\n';
            for (const _lexing::_types::_Token_s &token : tokens) {
                std::cout << "value = " << token.strValue << " type = " << _lexing::_types::_convertTokenTypeToString(token.type) << '\n';
            }
            std::cout << std::endl;
        }


    } // namespace _private
} // namespace liminal_json_io
