/**
 * @file _VkCommandBuffer_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__COMMAND__BUFFER__VKCOMMANDBUFFER_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__COMMAND__BUFFER__VKCOMMANDBUFFER_WRAPPERS_HPP_

#include <vulkan/vulkan.h>

namespace vulkan_wrapper {
    namespace _command {
        namespace _buffer {
            
            /**
             * @brief Loads a Vulkan command buffer
             * 
             * @param logical_device (const VkDevice &) The related Vulkan logical device
             * @param command_pool (const VkCommandPool &) The related command pool
             * @return The created Vulkan command buffer (VkCommandBuffer )
             */
            VkCommandBuffer _load(const VkDevice &logical_device, const VkCommandPool &command_pool);

        } // namespace _buffer
    } // namespace _command
} // namespace vulkan_wrapper


#endif // LIMINAL_LIB_VULKAN_WRAPPER__COMMAND__BUFFER__VKCOMMANDBUFFER_WRAPPERS_HPP_