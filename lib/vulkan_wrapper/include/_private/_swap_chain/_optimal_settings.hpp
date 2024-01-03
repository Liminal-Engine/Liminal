/**
 * @file _optimal_settings.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIB_VULKAN_WRAPPER__SWAP_CHAIN__OPTIMAL_SETTINGS_HPP_
#define LIB_VULKAN_WRAPPER__SWAP_CHAIN__OPTIMAL_SETTINGS_HPP_

#include "liminal_windowing/WindowWrapper.hpp"

#include <vulkan/vulkan.h>
#include <vector>

namespace vulkan_wrapper {
    namespace _swap_chain {

        /**
         * @brief Get the best possible swap chain presentation modes
         * 
         * @param available_presentation_modes (const std::vector<VkPresentModeKHR> &) - The available presentation modes
         * @return VkPresentModeKHR The best presentation mode found
         */
        VkPresentModeKHR _getBestPresentationMode(const std::vector<VkPresentModeKHR> &available_presentation_modes);

        /**
         * @brief Get the best possible swap chain surface format
         * 
         * @param supported_formats (const std::vector<VkSurfaceFormatKHR> &) The supported formats
         * @return VkSurfaceFormatKHR The best surface format
         */
        VkSurfaceFormatKHR _getBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &supported_formats);

        /**
         * @brief Get the best possible swap chain image extent
         * 
         * @param window (const window_wrapper::WindowWrapper &) -  The related window
         * @param surface_capabilities (const VkSurfaceCapabilitiesKHR &) - The supported surface capabilities
         * @return VkExtent2D The best extent found
         */
        VkExtent2D _getBestExtent(const window_wrapper::WindowWrapper &window, const VkSurfaceCapabilitiesKHR &surface_capabilities);

    } // namespace _swap_chain
} // vulkan_wrapper



#endif // LIB_VULKAN_WRAPPER__SWAP_CHAIN__OPTIMAL_SETTINGS_HPP_