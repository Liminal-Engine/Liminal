#ifndef LIMINAL_LIB_VULKAN_WRAPPER__FENCE__VKFENCE_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__FENCE__VKFENCE_WRAPPERS_HPP_

#include <vulkan/vulkan.h>

namespace vulkan_wrapper {
    namespace _fence {

        /**
         * @brief Loads a VUlkan fence
         * 
         * @param logical_device (const VkDevice &) The related Vulkan logical device
         * @return The created Vulkan fence (VkFence)
         */
        VkFence _load(const VkDevice &logical_device);

        /**
         * @brief Destroys a Vulkan fence
         * 
         * @param logical_device (const VkDevice &) The related Vulkan logical device
         * @param fence (const VkFence &) The Vulkan fence to destroy
         * @param p_allocator (const VkAllocationCallbacks *) (default = nullptr) Vulkan custom allocator
         */
        void _destroy(
            const VkDevice &logical_device,
            const VkFence &fence,
            const VkAllocationCallbacks *p_allocator = nullptr
        );

    } // namespace _fence
} // vulkan_wrapper



#endif // LIMINAL_LIB_VULKAN_WRAPPER__FENCE__VKFENCE_WRAPPERS_HPP_