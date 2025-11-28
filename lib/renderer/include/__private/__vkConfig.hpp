/**
 * @file __vkConfig.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-28
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__VK_CONFIG_HPP__
#define __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__VK_CONFIG_HPP__

namespace renderer {
    namespace __private {

        #define VULKAN_HPP_NO_EXCEPTIONS

        #define VULKAN_HPP_ASSERT_ON_RESULT(expr) ((void)0)

    } // namespace __private
} // namespace renderer


#endif // __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__VK_CONFIG_HPP__