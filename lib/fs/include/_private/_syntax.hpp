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

#ifndef LIMINAL_LIB_FS__PRIVATE__SYNTAX_HPP_
#define LIMINAL_LIB_FS__PRIVATE__SYNTAX_HPP_

namespace fs {
    namespace _private {

        namespace _syntax {
            constexpr char      PATH_SEPARATOR  = '/';
            constexpr char      FORBIDEN_CHARS[]  = "/\\<>:\"|*&~"; //TODO : check exactly forbidden cars of both OS and update tests
            
        } // namespace _syntax
        
    } // namespace _private
    
    
} // namespace fs


#endif // LIMINAL_LIB_FS__PRIVATE__SYNTAX_HPP_