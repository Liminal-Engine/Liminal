/**
 * @file _JsonBase.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-26
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_JsonBase.hpp"
#include "_private/_syntax.hpp"
#include "_private/_lexing/_types.hpp"
#include "_private/_lexing/_lexing.hpp"
#include "_private/_parsing/_parsing.hpp"
#include "_private/_error/_Errors.hpp"

#include "fs/InFile.hpp"
#include "logger/logger.hpp"

#include <iostream>
#include <stdexcept>

namespace jsonio {
    namespace _private {

        // Public :
        Status _JsonBase::parse(const fs::Path &path) {
            try {
                _lexing::_types::_Tokens_t tokens = _lexing::_processLexing(path);
                std::size_t index{0};
                this->_rootValue = _parsing::_processParsing(tokens.at(0), tokens, index);
                return Status::OK;
            } catch (const error::Base &e) {
                e.log();
                if (dynamic_cast<const _private::_error::_Parsing*>(&e)) return Status::E_PARSING; //TODO : create a ERROR_IS_OF_TYPE marcro instead ?
                if (dynamic_cast<const _private::_error::_Type*>(&e)) return Status::E_TYPE;
                if (dynamic_cast<const _private::_error::_Key*>(&e)) return Status::E_KEY;
                if (dynamic_cast<const _private::_error::_Index*>(&e)) return Status::E_INDEX;
                if (dynamic_cast<const _private::_error::_File*>(&e)) return Status::E_FILE;
                if (dynamic_cast<const _private::_error::_NotLoaded*>(&e)) return Status::E_NOT_LOADED;
            } catch (...) {
                return Status::E_NOK;
            }
            return Status::E_NOK;
        }

    } // namespace _private
} // namespace jsonio
