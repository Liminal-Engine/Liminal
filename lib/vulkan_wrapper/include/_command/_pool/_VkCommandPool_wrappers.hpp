/**
 * @file _VkCommandPool_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__COMMAND__POOL__VKCOMMANDPOOL_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__COMMAND__POOL__VKCOMMANDPOOL_WRAPPERS_HPP_

#include "_queue/_QueueFamilies.hpp"

#include <vulkan/vulkan.h>


namespace vulkan_wrapper {
    namespace _command {
        namespace _pool {

            /**
             * @brief Loads a Vulkan command pool
             * 
             * @param logical_device 
             * @param queue_families 
             * @return The createed Vulkan command pool (VkCommandPool )
             */
            VkCommandPool _load(const VkDevice &logical_device, const _queue::_QueueFamilies &queue_families);

            /**
             * @brief Destroys a Vulkan command pool
             * 
             * @param logical_device (const VkDevice &) The related Vulkan logical device
             * @param command_pool (const VkCommandPool &) The command pool to destroy
             * @param p_allocator (const VkAllocationCallbacks *) (default = nullptr) Vulkan custom allocator
             */
            void _destroy(
                const VkDevice &logical_device,
                const VkCommandPool &command_pool,
                const VkAllocationCallbacks *p_allocator = nullptr
            );

        } // namespace _pool
    } // namespace _command
} // namespace vulkan_wrapper

#endif // LIMINAL_LIB_VULKAN_WRAPPER__COMMAND__POOL__VKCOMMANDPOOL_WRAPPERS_HPP_