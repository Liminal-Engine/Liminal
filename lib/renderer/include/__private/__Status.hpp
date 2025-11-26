/**
 * @file __Status.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-14
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__STATUS_HPP__
#define __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__STATUS_HPP__

namespace renderer {
    namespace __private {
        enum __Status {
            __E_OK,
            __E_NOK,
            __E_ALREADY_EXISTS,
            __E_NO_EXISTS,
            __E_NOT_CREATED,
            __E_PIPELINE_NOT_FOUND
        };
    } // namespace __private
} // namespace renderer

#endif // __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__STATUS_HPP__
