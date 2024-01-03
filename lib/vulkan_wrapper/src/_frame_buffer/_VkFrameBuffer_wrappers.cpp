#include "_private/_frame_buffer/_VkFrameBuffer_wrappers.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _frame_buffer {

        std::vector<VkFramebuffer> _load(
            const VkDevice &logical_device,
            const std::vector<VkImageView> &swap_chain_image_views,
            const VkExtent2D &swap_chain_extent,
            const VkRenderPass &render_pass
        ) {
            std::vector<VkFramebuffer> res(swap_chain_image_views.size());

            for (size_t i = 0; i < swap_chain_image_views.size(); i++) {
                VkImageView attachments[] = { swap_chain_image_views[i] };
                VkFramebufferCreateInfo create_info{};
                create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
                create_info.renderPass = render_pass;
                //Specify the "VkImageView" objects that should be bound to the respective attachment descriptions in the render pass "pAttachment" array
                create_info.attachmentCount = 1;
                create_info.pAttachments = attachments;
                create_info.width = swap_chain_extent.width;
                create_info.height = swap_chain_extent.height;
                create_info.layers = 1; // Number of layers in the image arrays (in the VkImageView attachments ?)
                if (vkCreateFramebuffer(logical_device, &create_info, nullptr, &res[i]) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create frame buffer");
                }
            }
            return res;
        }

        void _destroy(
            const VkDevice &logical_device,
            const std::vector<VkFramebuffer> &frame_buffers,
            const VkAllocationCallbacks **pp_allocators
        ) {
            if (pp_allocators == nullptr) {
                for (const VkFramebuffer &frame_buffer : frame_buffers) {
                    vkDestroyFramebuffer(logical_device, frame_buffer, nullptr);
                }
            } else {
                const VkAllocationCallbacks **tmpCallback = pp_allocators;
                for (const VkFramebuffer &frame_buffer : frame_buffers) {
                    vkDestroyFramebuffer(logical_device, frame_buffer, *tmpCallback);
                    tmpCallback++;
                }
            }
        }
        
    } // namespace _frame_buffer
} // namespace vulkan_wrapper

