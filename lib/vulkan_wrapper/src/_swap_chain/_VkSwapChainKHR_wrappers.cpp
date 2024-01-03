/**
 * @file _VkSwapChainKHR_wrappers.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_swap_chain/_VkSwapChainKHR_wrappers.hpp"
#include "_private/_swap_chain/_optimal_settings.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _swap_chain {

        VkSwapchainKHR _load(
            const VkDevice &logical_device,
            const VkSurfaceKHR &surface,
            const _Supports &swap_chain_supports,
            const _queue::_QueueFamilies &queue_families,
            const VkSurfaceFormatKHR &swap_chain_image_format,
            const VkExtent2D &swap_chain_image_extent
        ) {
            VkPresentModeKHR bestPresentationMode = _getBestPresentationMode(swap_chain_supports._presentationModes);

            // + 1 to avoid wait for the driver to complete internal ops before we can acquire anoter image to render to
            uint32_t nImages = swap_chain_supports._surfaceCapabilities.minImageCount + 1;
            // make sure we do not exceed
            if (swap_chain_supports._surfaceCapabilities.maxImageCount > 0 && nImages > swap_chain_supports._surfaceCapabilities.maxImageCount) {
                nImages = swap_chain_supports._surfaceCapabilities.maxImageCount;
            }
            VkSwapchainCreateInfoKHR create_info{};
            create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            create_info.surface = surface;
            create_info.minImageCount = nImages;
            create_info.imageFormat = swap_chain_image_format.format;
            create_info.imageColorSpace = swap_chain_image_format.colorSpace;
            create_info.imageExtent = swap_chain_image_extent;
            create_info.imageArrayLayers = 1; // Nb of layer each image consist of
            create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
            create_info.preTransform = swap_chain_supports._surfaceCapabilities.currentTransform;
            create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            create_info.presentMode = bestPresentationMode;
            create_info.clipped = VK_TRUE;
            create_info.oldSwapchain = VK_NULL_HANDLE;

            if (queue_families._graphicsFamily != queue_families._presentFamily) {
                create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT; // Image is owned by one queue families at a time
                create_info.queueFamilyIndexCount = 2;
            } else {
                create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // Image can be owned by queue families
                create_info.queueFamilyIndexCount = 0;
            }
            create_info.pQueueFamilyIndices = queue_families._toVector().data();

            VkSwapchainKHR res{};
            if (vkCreateSwapchainKHR(logical_device, &create_info, nullptr, &res) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create swap chain");
            }
            return res;
        }

        void _destroy(
            const VkDevice &logical_device,
            const VkSwapchainKHR &swap_chain,
            VkAllocationCallbacks *p_allocator
        ) {
            vkDestroySwapchainKHR(logical_device, swap_chain, p_allocator);
        }
        
    } // namespace _swap_chain
} // vulkan_wrapper
