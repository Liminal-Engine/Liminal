#include "_command/_buffer/_VkCommandBuffer_wrappers.hpp"

#include <stdexcept>


namespace vulkan_wrapper {
    namespace _command {
        namespace _buffer {
            
            VkCommandBuffer _load(const VkDevice &logical_device, const VkCommandPool &command_pool) {
                VkCommandBuffer res{};
                VkCommandBufferAllocateInfo command_buffer_alloc_info{};
                command_buffer_alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                command_buffer_alloc_info.commandPool = command_pool;
                command_buffer_alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                command_buffer_alloc_info.commandBufferCount = 1;
                if (vkAllocateCommandBuffers(logical_device, &command_buffer_alloc_info, &res) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to allocate memory for command buffers");
                }
                return res;
            }

        } // namespace _buffer
    } // namespace _command
} // namespace vulkan_wrapper

