/**
 * @file pathSyntax.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-25
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _LIMINAL_LIB_FS__PRIVATE__SYNTAX_HPP_
#define _LIMINAL_LIB_FS__PRIVATE__SYNTAX_HPP_

#include <array>

namespace fs {
    namespace _private {

        namespace _syntax {
            constexpr char      PATH_SEPARATOR  = '/';
            constexpr std::array<char, 10> FORBIDEN_CHARS = {'/'}; //TODO : check exactly forbidden cars of both OS and update tests and improve tests. For example, '*' and may be forbidden only fgor first or last char
        } // namespace _syntax
        
    } // namespace _private
    
    
} // namespace fs


#endif // _LIMINAL_LIB_FS__PRIVATE__SYNTAX_HPP_