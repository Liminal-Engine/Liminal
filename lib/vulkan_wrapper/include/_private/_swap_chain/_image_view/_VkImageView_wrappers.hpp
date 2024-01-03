/**
 * @file _VkImageView_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__IMAGE_VIEW__VKIMAGEVIEW_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__IMAGE_VIEW__VKIMAGEVIEW_WRAPPERS_HPP_

#include <vulkan/vulkan.h>
#include <vector>


namespace vulkan_wrapper {
    namespace _swap_chain {
        namespace _image_view {

            /**
             * @brief Load a swap chain image views
             * 
             * @param logical_device (const VkDevice &) The related logical device
             * @param swap_chain_images (const std::vector<VkImage> &) The related swap chain images handlers
             * @param swap_chain_images_format (const VkFormat &) The related swap chain images format
             * @return The created array of images view (std::vector<VkImage> )
            */
            std::vector<VkImageView> _load(
                const VkDevice &logical_device,
                const std::vector<VkImage> &swap_chain_images,
                const VkFormat &swap_chain_images_format
            );

            /**
             * @brief Destroy a swawp chain
             * 
             * @param logical_device (const VkDevice &) The related logical device
             * @param image_view_handlers (const std::vector<VkImageView> &) The related swap chain images views handlers
             * @param pp_allocator (VkAllocationCallbacks **) (default = nullptr) Vulkan allocation callbacks array pointers
            */
            void _destroy(
                const VkDevice &logical_device,
                const std::vector<VkImageView> &image_view_handlers,
                VkAllocationCallbacks **pp_allocator = nullptr
            );

        } // _image_view
    } // namespace _swap_chain
} // vulkan_wrapper


#endif // LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__IMAGE_VIEW__VKIMAGEVIEW_WRAPPERS_HPP_

