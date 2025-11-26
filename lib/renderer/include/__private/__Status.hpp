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
            E_OK,
            E_NOK,
            E_ALREADY_EXISTS,
            E_NO_EXISTS,
            E_NOT_CREATED,
            E_PIPELINE_NOT_FOUND
        };
    } // namespace __private
} // namespace renderer

#endif // __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__STATUS_HPP__
