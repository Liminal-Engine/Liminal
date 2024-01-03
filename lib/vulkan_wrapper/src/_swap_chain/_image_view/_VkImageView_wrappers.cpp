#include "_private/_swap_chain/_image_view/_VkImageView_wrappers.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _swap_chain {
        namespace _image_view {

            std::vector<VkImageView> _load(
                const VkDevice &logical_device,
                const std::vector<VkImage> &swap_chain_images,
                const VkFormat &swap_chain_images_format
            ) {
                std::vector<VkImageView> res(swap_chain_images.size());

                for (size_t i = 0; i < swap_chain_images.size(); i++) {
                    VkImageViewCreateInfo create_info{};
                    create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                    create_info.image = swap_chain_images[i];
                    create_info.viewType = VK_IMAGE_VIEW_TYPE_2D; //treat image as 1D, 2D, 3D textures or else
                    create_info.format = swap_chain_images_format;
                    // Allow to swizzle color channels
                    create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
                    create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
                    create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
                    create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
                    // subresourceRange describes the purpose of the image and which part of it should be accessed
                    create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                    create_info.subresourceRange.baseMipLevel = 0;
                    create_info.subresourceRange.levelCount = 1;
                    create_info.subresourceRange.baseArrayLayer = 0;
                    create_info.subresourceRange.layerCount = 1;

                    if (vkCreateImageView(logical_device, &create_info, nullptr, &res[i]) != VK_SUCCESS) {
                        throw std::runtime_error("Cannot create image view");
                    }
                }
                return res;
            }

            void _destroy(
                const VkDevice &logical_device,
                const std::vector<VkImageView> &image_view_handlers,
                VkAllocationCallbacks **pp_allocator
            ) {

                if (pp_allocator == nullptr) {
                    for (const VkImageView &image_view : image_view_handlers) {
                        vkDestroyImageView(logical_device, image_view, nullptr);
                    }
                } else {
                    VkAllocationCallbacks **tmp_callback = pp_allocator;
                    for (const VkImageView &image_view : image_view_handlers) {
                        vkDestroyImageView(logical_device, image_view, *tmp_callback);
                        tmp_callback++;
                    }
                }
            }

        } // _image_view
    } // namespace _swap_chain
} // vulkan_wrapper
