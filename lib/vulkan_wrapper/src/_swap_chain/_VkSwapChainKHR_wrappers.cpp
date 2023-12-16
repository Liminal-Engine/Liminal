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

#include "_swap_chain/_VkSwapChainKHR_wrappers.hpp"
#include "_swap_chain/_optimal_settings.hpp"

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
            VkSwapchainCreateInfoKHR createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            createInfo.surface = surface;
            createInfo.minImageCount = nImages;
            createInfo.imageFormat = swap_chain_image_format.format;
            createInfo.imageColorSpace = swap_chain_image_format.colorSpace;
            createInfo.imageExtent = swap_chain_image_extent;
            createInfo.imageArrayLayers = 1; // Nb of layer each image consist of
            createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
            createInfo.preTransform = swap_chain_supports._surfaceCapabilities.currentTransform;
            createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
            createInfo.presentMode = bestPresentationMode;
            createInfo.clipped = VK_TRUE;
            createInfo.oldSwapchain = VK_NULL_HANDLE;

            if (queue_families._graphicsFamily != queue_families._presentFamily) {
                createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT; // Image is owned by one queue families at a time
                createInfo.queueFamilyIndexCount = 2;
            } else {
                createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; // Image can be owned by queue families
                createInfo.queueFamilyIndexCount = 0;
            }
            VkSwapchainKHR res{};
            createInfo.pQueueFamilyIndices = queue_families._toVector().data();
            if (vkCreateSwapchainKHR(logical_device, &createInfo, nullptr, &res) != VK_SUCCESS) {
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
