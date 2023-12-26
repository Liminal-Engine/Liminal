/**
 * @file _JSON.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-20
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSON_HPP
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSON_HPP

#include "_lexing/_lexing.hpp"

#include "path/path.hpp"

#include <string>

namespace liminal_json_io {
    namespace _private {

        class _JSON {
            public:
                _JSON(const std::string &path);

                void parse(void);

            protected:
                liminal_fs::path::path_t _path;
                

            private:
                _lexing::_tokens_t __processParsing(_lexing::_tokens_t &tokens, const bool &isRoot = false);
                _lexing::_tokens_t __parseObject(_lexing::_tokens_t &tokens);
                _lexing::_tokens_t __parseArray(_lexing::_tokens_t &tokens);
                std::string __getFileContent(const std::string &path);
                
        };
    } // namespace _private
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSON_HPP