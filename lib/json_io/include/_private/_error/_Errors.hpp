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

#ifndef LIMINAL_LIB_JSON_IO_INCLUDE__PRIVATE__ERROR__ERRORS_HPP
#define LIMINAL_LIB_JSON_IO_INCLUDE__PRIVATE__ERROR__ERRORS_HPP

#include <error/error.hpp>
#include <logger/logger.hpp>

#include <string>




namespace json_io {
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
} // namespace json_io


#endif // LIMINAL_LIB_JSON_IO_INCLUDE__PRIVATE__ERRORS_HPP