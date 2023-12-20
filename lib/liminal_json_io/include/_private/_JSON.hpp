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

#include <string>

namespace liminal_json_io {
    namespace _private {

        class _JSON {
            public:
                _JSON(const std::string &path);

                static void parse(void);

            protected:                

            private:
                std::string __load_json_string(const std::string &path);
                const _lexing::_tokens_t _tokens;
                
        };
    } // namespace _private
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__JSON_HPP