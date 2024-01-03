/**
 * @file _Supports.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_swap_chain/_Supports.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _swap_chain {

        _Supports _getSupports(
            const VkPhysicalDevice &physical_device,
            const VkSurfaceKHR &surface
        ) {
            _Supports res{};
            // 1. Get surface capabilities
            vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physical_device, surface, &res._surfaceCapabilities);
            // 2. Get the available surface formats
            // 2.1 Get the total number of available surface formats first
            uint32_t nFormat = 0;
            vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &nFormat, nullptr);
            if (nFormat == 0)
                throw std::runtime_error("No surface format found for the given device while creating the swap chain");
            // 2.2 Then, create the memory space for the vector of surface formats
            res._surfaceFormats.resize(nFormat);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physical_device, surface, &nFormat, res._surfaceFormats.data());
            // 3. Get the available swap chain presentation mode
            // 3.1 Get the total number of available wap chain presentation mode first
            uint32_t nPresentationMode = 0;
            vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &nPresentationMode, nullptr);
            if (nPresentationMode == 0)
                throw std::runtime_error("No presentation mode for the given device while creating the swap chain");
            // 3.2 Then, create the memory space for the vector of presentation mode
            res._presentationModes.resize(nPresentationMode);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physical_device, surface, &nPresentationMode, res._presentationModes.data());
            return res;
        }

    } // namespace _swap_chain
} // vulkan_wrapper
