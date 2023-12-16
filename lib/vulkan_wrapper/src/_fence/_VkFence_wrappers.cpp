#include "_fence/_VkFence_wrappers.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _fence {

        VkFence _load(const VkDevice &logical_device) {
                VkFence res{};
                VkFenceCreateInfo create_info{};
                create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
                create_info.flags = VK_FENCE_CREATE_SIGNALED_BIT;
                if (vkCreateFence(logical_device, &create_info, nullptr, &res) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create fence");
                }
                return res;
        }

        void _destroy(
            const VkDevice &logical_device,
            const VkFence &fence,
            const VkAllocationCallbacks *p_allocator
        ) {
            vkDestroyFence(logical_device, fence, p_allocator);
        }

    } // namespace _fence
} // vulkan_wrapper


