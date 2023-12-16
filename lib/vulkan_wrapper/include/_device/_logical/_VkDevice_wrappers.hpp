#ifndef LIMINAL_VULKAN_WRAPPER_LIB__DEVICE_PHYSICAL__VKPHYSICALDEVICE_WRAPPERS_HPP_
#define LIMINAL_VULKAN_WRAPPER_LIB__DEVICE_PHYSICAL__VKPHYSICALDEVICE_WRAPPERS_HPP_

#include "_queue/_QueueFamilies.hpp"

#include <vulkan/vulkan.h>
#include <set>
#include <vector>

namespace vulkan_wrapper {
    namespace _device {
        namespace _logical {

        /**
         * @brief Create a Vulkan logical device
         * 
         * @param physical_device (const VkPhysicalDevice &) The physical device
         * @param families_indices (const std::set<_queues::_QueueFamilyIndex_t> &) A set of the indices of the device families
         * @param device_extensions (const std::vector<const char *> &) Device extensions
         * @return The created VkDevice (VkDevice)
         */
        VkDevice _load(
            const VkPhysicalDevice &physical_device,
            const std::set<_queue::_QueueFamilyIndex_t> &families_indices,
            const std::vector<const char *> &device_extensions
        );

        /**
         * @brief Destroy a Vulkan logical device
         * 
         * @param logicalDevice (const VkDevice &) The logical device to destroy
         * @param p_allocator (VkAllocationCallbacks *) Vulkan allocator
         */
        void _destroy(
            const VkDevice &logicalDevice,
            VkAllocationCallbacks *p_allocator = nullptr
        );

        } // namespace _logical
    } // namespace _logical_device
} // namespace vulkan_wrapper


#endif // LIMINAL_VULKAN_WRAPPER_LIB__DEVICE_PHYSICAL__VKPHYSICALDEVICE_WRAPPERS_HPP_