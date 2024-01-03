#ifndef LIMINAL_LIB_VULKAN_WRAPPER__SEMAPHORE__VKSEMAPHORE_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__SEMAPHORE__VKSEMAPHORE_WRAPPERS_HPP_

#include <vulkan/vulkan.h>

namespace vulkan_wrapper {
    namespace _semaphore {

        /**
         * @brief Loads a Vulkan semaphore
         * 
         * @param logical_device (const VkDevice &) The related logical device
         * @return The created Vulkan semaphore (VkSemaphore )
         */
        VkSemaphore _load(const VkDevice &logical_device);

        /**
         * @brief Destroys a Vulkan semaphore
         * 
         * @param logical_device (const VkDevice &) The related Vulkan logical device
         * @param semaphore (const VkSemaphore &) The Vulkan semaphore to destroy
         * @param p_allocator (const VkAllocationCallbacks *) (default = nullptr) Custom Vulkan allocator
         */
        void _destroy(
            const VkDevice &logical_device,
            const VkSemaphore &semaphore,
            const VkAllocationCallbacks *p_allocator = nullptr
        );

    } // namespace _semaphore
} // vulkan_wrapper



#endif // LIMINAL_LIB_VULKAN_WRAPPER__SEMAPHORE__VKSEMAPHORE_WRAPPERS_HPP_