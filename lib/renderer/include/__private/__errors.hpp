/**
 * @file __errors.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-27
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__ERROR_HPP__
#define __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__ERROR_HPP__

#include <logger/logger.hpp>
#include <vulkan/vulkan_raii.hpp>

namespace renderer {
    namespace __private {

        // 2 args: (result, msg)
        #define __LOG_VK_CREATE_ERROR_NO_GPU(result, msg)                          \
            do {                                                                   \
                logger::error << msg                                               \
                              << "\nError: " << vk::to_string(result)             \
                              << std::endl;                                       \
            } while (0);

        // 3 args: (gpu, result, msg)
        #define __LOG_VK_CREATE_ERROR_GPU(gpu, result, msg)                        \
            do {                                                                   \
                logger::error << msg                                               \
                              << "\nGPU: " << (gpu).getName()                      \
                              << "\nError: " << vk::to_string(result)             \
                              << std::endl;                                       \
            } while (0);

        // Select the correct macro depending on the number of arguments
        #define __LOG_VK_CREATE_ERROR_GET_MACRO(_1,_2,_3,NAME,...) NAME

        #define __LOG_VK_CREATE_ERROR(...)                                         \
            __LOG_VK_CREATE_ERROR_GET_MACRO(                                       \
                __VA_ARGS__,                                                       \
                __LOG_VK_CREATE_ERROR_GPU,                                         \
                __LOG_VK_CREATE_ERROR_NO_GPU                                       \
            )(__VA_ARGS__)

    } // namespace __private
} // namespace renderer

#endif // __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__ERROR_HPP__