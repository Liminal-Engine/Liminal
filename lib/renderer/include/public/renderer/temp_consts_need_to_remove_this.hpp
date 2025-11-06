/**
 * @file temp_consts_need_to_remove_this.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-05
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__RENDERER_INCLUDE_RENDERER__TEMP_CONSTS_NEED_TO_REMOVE_THIS_HPP__
#define __LIMINAL__RENDERER_INCLUDE_RENDERER__TEMP_CONSTS_NEED_TO_REMOVE_THIS_HPP__

#include <vulkan/vulkan_raii.hpp>

#include <vector>


namespace renderer {

    const std::vector<std::string> REQUIRED_INSTANCE_LAYER_NAMES = {
#ifndef NDEBUG
        "VK_LAYER_KHRONOS_validation"
#else

#endif // NDEBUG
    };

    const std::vector<std::string> REQUIRED_INSTANCE_EXTENSION_NAMES = {
        "VK_KHR_surface",
        "VK_KHR_xcb_surface"
    };

    const std::vector<std::string> REQUIRED_DEVICE_EXTENSION_NAMES = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    const char *APPLICATION_NAME = "Liminal Engine";

    // TODO : read VERSION file instead
    const uint32_t APPLICATION_VERSION = VK_MAKE_VERSION(0, 10 ,10);

    const char *ENGINE_NAME = "Liminal";

    // TODO : this may change if we create apps (such as games) that uses the engine
    const uint32_t ENGINE_VERSION = APPLICATION_VERSION;

    #define MIN_VULKAN_VERSION VK_API_VERSION_1_3
} // namespace renderer


#endif // __LIMINAL__RENDERER_INCLUDE_RENDERER__TEMP_CONSTS_NEED_TO_REMOVE_THIS_HPP__