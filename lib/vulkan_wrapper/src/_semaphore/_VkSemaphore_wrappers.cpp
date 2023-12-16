#include "_semaphore/_VkSemaphore_wrappers.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _semaphore {

        VkSemaphore _load(const VkDevice &logical_device) {
            VkSemaphore res{};
            VkSemaphoreCreateInfo create_info{};
            create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

            if (vkCreateSemaphore(logical_device, &create_info, nullptr, &res) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create semaphore");
            }
            return res;
        }

        void _destroy(
            const VkDevice &logical_device,
            const VkSemaphore &semaphore,
            const VkAllocationCallbacks *p_allocator
        ) {
            vkDestroySemaphore(logical_device, semaphore, p_allocator);
        }

    } // namespace _semaphore
} // vulkan_wrapper


