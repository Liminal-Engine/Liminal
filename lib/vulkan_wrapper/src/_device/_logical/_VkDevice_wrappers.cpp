/**
 * @file _VkDevice_wrappers.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_device/_logical/_VkDevice_wrappers.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _device {
        namespace _logical {

            static std::vector<VkDeviceQueueCreateInfo> __getQueueCreateInfos(
                    const VkPhysicalDevice &physicalDevice,
                    const VkSurfaceKHR &surface,
                    const std::set<_queue::_QueueFamilyIndex_t> &families_indices
                ) {
                    std::vector<VkDeviceQueueCreateInfo> res;
                    float queuePriorities[] = {1.0f}; // Scheduling command buffer execution. We must create one float per each queue index

                    for (_queue::_QueueFamilyIndex_t index : families_indices) {
                        VkDeviceQueueCreateInfo queueCreateInfo{};
                        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                        queueCreateInfo.queueFamilyIndex = index;
                        queueCreateInfo.queueCount = 1;
                        queueCreateInfo.pQueuePriorities = queuePriorities; //TODO new float{x} but we need to free it

                        res.push_back(queueCreateInfo);
                    }
                    return res;
                }

            VkDevice _load(
                const VkPhysicalDevice &physical_device,
                const VkSurfaceKHR &surface,
                const std::set<_queue::_QueueFamilyIndex_t> &families_indices,
                const std::vector<const char *> &device_extensions
            ) {
                // 1. Get the createInfo struct for all logical device queue families
                std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = __getQueueCreateInfos(physical_device, surface, families_indices);
                // 2. Get the features we want to enable for the device
                VkPhysicalDeviceFeatures deviceFeatures{}; //Leave blank for now as we don't anything special
                // 3. Create the logical device
                VkDeviceCreateInfo createInfo{};
                createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
                createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
                createInfo.pQueueCreateInfos = queueCreateInfos.data();
                createInfo.enabledExtensionCount = static_cast<uint32_t>(device_extensions.size());
                createInfo.ppEnabledExtensionNames = device_extensions.data();
                createInfo.pEnabledFeatures = &deviceFeatures;
                createInfo.pNext = nullptr;

                VkDevice res{};
                if (vkCreateDevice(physical_device, &createInfo, nullptr, &res) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create logical device");
                }
                return res;
            }

            void _destroy(
                const VkDevice &logicalDevice,
                VkAllocationCallbacks *p_allocator
            ) {
                vkDestroyDevice(logicalDevice, p_allocator);
            }
            
        } // namespace _logical
    } // namespace _device
} // namespace vulkan_wrapper
