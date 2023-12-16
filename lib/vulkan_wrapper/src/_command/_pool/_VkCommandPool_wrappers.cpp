#include "_command/_pool/_VkCommandPool_wrappers.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _command {
        namespace _pool {

            VkCommandPool _load(const VkDevice &logical_device, const _queue::_QueueFamilies &queue_families) {
                VkCommandPool res{};
                VkCommandPoolCreateInfo create_info{};

                create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
                create_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
                create_info.queueFamilyIndex = queue_families._graphicsFamily.value();
                if (vkCreateCommandPool(logical_device, &create_info, nullptr, &res) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create command pool");
                }
                return res;
            }

            void _destroy(
                const VkDevice &logical_device,
                const VkCommandPool &command_pool,
                const VkAllocationCallbacks *p_allocator
            ) {
                vkDestroyCommandPool(logical_device, command_pool, p_allocator);
            }

        } // namespace _pool
    } // namespace _command
} // namespace vulkan_wrapper
