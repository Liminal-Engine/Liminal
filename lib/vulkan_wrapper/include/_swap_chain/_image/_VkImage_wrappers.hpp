/**
 * @file _VkImage_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__VKIMAGE_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__VKIMAGE_WRAPPERS_HPP_

#include <vulkan/vulkan.h>
#include <vector>

namespace vulkan_wrapper {
    namespace _swap_chain {
        namespace _image {

            /**
             * @brief Loads a swap chain images
             * 
             * @param logical_device (const VkDevice &)  The related logical device
             * @param swap_chain (const VkSwapchainKHR &) The related swap chain
             * @return The created vector of Vulkan images (std::vector<VkImage>)
             */
            std::vector<VkImage> _load(const VkDevice &logical_device, const VkSwapchainKHR &swap_chain);

        } // _image
    } // namespace _swap_chain
} // vulkan_wrapper


#endif // LIMINAL_LIB_VULKAN_WRAPPER__SWAP_CHAIN__VKIMAGE_WRAPPERS_HPP_

