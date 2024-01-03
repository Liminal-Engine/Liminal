/**
 * @file _VKRenderPass_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__RENDER_PASS__VKRENDERPASS_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__RENDER_PASS__VKRENDERPASS_WRAPPERS_HPP_

#include <vulkan/vulkan.h>

namespace vulkan_wrapper {
    namespace _render_pass {

        /**
         * @brief Load a render pass
         * 
         * @param logical_device (const VkDevice &) The related Vulkan logical device
         * @param swap_chain_images_format (const VkFormat &) The related swap chain images format
         * @return The created Vulkan render pass (VkRenderPass)
         */
        VkRenderPass _load(const VkDevice &logical_device, const VkFormat &swap_chain_images_format);

        /**
         * @brief Destroy a render pass
         * 
         * @param logical_device [const VkDevice &] The related logical device
         * @param render_pass [const VkRenderPass &] The render pass to destroy
         * @param p_allocator [VkAllocationCallbacks *] Vulkan allocation callbacks 
        */
        void _destroy(
            const VkDevice &logical_device,
            const VkRenderPass &render_pass,
            VkAllocationCallbacks *p_allocator = nullptr
        );

    } // _render_pass
} // vulkan_wrapper


#endif // LIMINAL_LIB_VULKAN_WRAPPER__RENDER_PASS__VKRENDERPASS_WRAPPERS_HPP_