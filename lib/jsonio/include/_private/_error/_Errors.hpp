/**
 * @file Errors.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-04
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef _LIMINAL_LIB_JSONIO__PRIVATE__ERROR__ERRORS_HPP_
#define _LIMINAL_LIB_JSONIO__PRIVATE__ERROR__ERRORS_HPP_

#include <error/error.hpp>
#include <logger/logger.hpp>

#include <string>




namespace jsonio {
    namespace _private {
        namespace _error {

            DEFINE_ERROR_CLASS(_Parsing);
            DEFINE_ERROR_CLASS(_Type);
            DEFINE_ERROR_CLASS(_Key);
            DEFINE_ERROR_CLASS(_Index);
            DEFINE_ERROR_CLASS(_File);
            DEFINE_ERROR_CLASS(_NotLoaded);

        } // namespace _error
    } // namespace _private 
} // namespace jsonio


#endif // LIMINAL_LIB_jsonio_INCLUDE__PRIVATE__ERRORS_HPP