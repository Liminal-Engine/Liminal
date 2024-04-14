/**
 * @file _Errors.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-13
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_LIB_FS_INCLUDE__PRIVATE__ERROR__ERRORS_HPP_
#define LIMINAL_LIB_FS_INCLUDE__PRIVATE__ERROR__ERRORS_HPP_

#include <error/error.hpp>

namespace fs {
    namespace _private {
        namespace _error {
            DEFINE_ERROR_CLASS(_CreateParentDirs);
        } // namespace _error
    } // namespace _private
} // namespace fs

#endif // LIMINAL_LIB_FS_INCLUDE__PRIVATE__ERROR__ERRORS_HPP_

