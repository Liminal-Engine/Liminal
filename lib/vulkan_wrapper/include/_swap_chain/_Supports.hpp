/**
 * @file _Supports.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__SUPPORTS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__SUPPORTS_HPP_

#include <vulkan/vulkan.h>
#include <vector>

namespace vulkan_wrapper {
    namespace _swap_chain {

        /**
         * @brief _SwapChainSupports Stores the swap chain supported features
        */
        struct _Supports {
            VkSurfaceCapabilitiesKHR _surfaceCapabilities; ///< Various paremeters about related to the surface such as min/max number of images in the swap chain, min/max width and height of the image
            std::vector<VkSurfaceFormatKHR> _surfaceFormats; ///< Surface formats = pixel format and color space (does'nt include iomage width and height since already in VkSurfaceCapabilitiesKHR)
            std::vector<VkPresentModeKHR> _presentationModes; ///< Represents the mode in which the image are presented in the swap chain (immediate, FIFO, mailbox, etc...) Each mode has its own way of working
        };

        /**
         * @brief Get swap chain supprots for a given physical device
         * 
         * @param physical_device (const VkPhysicalDevice &) The related physical device
         * @param surface (const VkSurfaceKHR &) The related surface
         * @return The found swap chain supports (_Supports)
         */
        _Supports _getSupports(
            const VkPhysicalDevice &physical_device,
            const VkSurfaceKHR &surface
        );

    } // namespace _swap_chain
} // vulkan_wrapper

#endif // LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__SUPPORTS_HPP_