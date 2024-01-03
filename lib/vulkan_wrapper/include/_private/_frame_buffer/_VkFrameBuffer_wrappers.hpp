/**
 * @file _VkFrameBuffer_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__FRAME_BUFFER__VKFRAMEBUFFER_WRAPPER_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__FRAME_BUFFER__VKFRAMEBUFFER_WRAPPER_HPP_

#include <vulkan/vulkan.h>
#include <vector>

namespace vulkan_wrapper {
    namespace _frame_buffer {

        /**
         * @brief Loads an array of Vulkan frame buffers
         * 
         * @param logical_device (const VkDevice &) The related Vulkan instance
         * @param swap_chain_image_views (const std::vector<VkImageView> &) The related Vulkan swap chain image views array
         * @param swap_chain_extent (const VkExtent2D &) The related Vulkan swap chain extent
         * @param render_pass (const VkRenderPass &) The related Vulkan render pass
         * @return The created array of Vulkan frame buffer (std::vector<VkFramebuffer>)
         */
        std::vector<VkFramebuffer> _load(
            const VkDevice &logical_device,
            const std::vector<VkImageView> &swap_chain_image_views,
            const VkExtent2D &swap_chain_extent,
            const VkRenderPass &render_pass
        );

        /**
         * @brief Destroy an array of Vulkan frame buffer
         * 
         * @param logical_device (const VkDevice &) The related Vulkan logical device
         * @param frame_buffers (const std::vector<VkFramebuffer> &) The Vulkan frame buffer to destroy
         * @param pp_allocators  (const VkAllocationCallbacks **) (default = nullptr) A pointer to an array of Vulkan custom allocators
         */
        void _destroy(
            const VkDevice &logical_device,
            const std::vector<VkFramebuffer> &frame_buffers,
            const VkAllocationCallbacks **pp_allocators = nullptr
        );
        
    } // namespace _frame_buffer
} // namespace vulkan_wrapper



#endif // LIMINAL_LIB_VULKAN_WRAPPER__FRAME_BUFFER__VKFRAMEBUFFER_WRAPPER_HPP_