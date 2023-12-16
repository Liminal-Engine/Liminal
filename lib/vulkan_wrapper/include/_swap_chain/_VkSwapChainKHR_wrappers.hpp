/**
 * @file _VkSwapChainKHR_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__VKSWAPCHAINKHR_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__VKSWAPCHAINKHR_WRAPPERS_HPP_

#include "_swap_chain/_Supports.hpp"
#include "_queue/_QueueFamilies.hpp"

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace vulkan_wrapper {
    namespace _swap_chain {

        /**
         * @brief Load a Vulkan swap chain
         * 
         * @param logical_device (const VkDevice &) The related Vulkan logical device
         * @param surface (const VkSurfaceKHR &) The related surface
         * @param swap_chain_supports (const _Supports &) The related swap chain supports
         * @param queue_families (const _queue::_QueueFamilies &) The related queue families
         * @param swap_chain_image_format (const VkSurfaceFormatKHR &) The swap chain image format (must be known before creating the swap chain)
         * @param swap_chain_image_extent (const VkExtent2D &) The swap chain image extent (must be known before create the swap chain)
         * @return The created swap chain (VkSwapchainKHR )
         */
        VkSwapchainKHR _load(
            const VkDevice &logical_device,
            const VkSurfaceKHR &surface,
            const _Supports &swap_chain_supports,
            const _queue::_QueueFamilies &queue_families,
            const VkSurfaceFormatKHR &swap_chain_image_format,
            const VkExtent2D &swap_chain_image_extent
        );

        /**
         * @brief Destroy a Vulkan swap chain
         * 
         * @param logical_device (const VkDevice &) The related logical device
         * @param swap_chain (const VkSwapchainKHR &) The swap chain to destroy
         * @param p_allocator (VkAllocationCallbacks *) (default = nullptr) The Vulkan custom allocator
         */
        void _destroy(
            const VkDevice &logical_device,
            const VkSwapchainKHR &swap_chain,
            VkAllocationCallbacks *p_allocator = nullptr
        );
        
    } // namespace _swap_chain
} // vulkan_wrapper

#endif // LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__VKSWAPCHAINKHR_WRAPPERS_HPP_