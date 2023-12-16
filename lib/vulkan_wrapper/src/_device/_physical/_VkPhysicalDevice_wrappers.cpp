/**
 * @file _VkPhysicalDevice_wrappers.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_device/_physical/_VkPhysicalDevice_wrappers.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _device {
        namespace _physical {
            
            VkPhysicalDevice _pick(
                const VkInstance &instance,
                const VkSurfaceKHR &surface,
                const std::vector<const char *> &required_extensions
            ) {
                (void)surface;
                (void)required_extensions;
                // 1. First, get the number of physical device on the computer
                uint32_t n_device = 0;
                if (vkEnumeratePhysicalDevices(instance, &n_device, nullptr) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to enumerate physical device on computer");
                }
                if (n_device == 0) {
                    throw std::runtime_error("No physical device found on computer");
                }
                // 2. Create vector with found size and fill it
                std::vector<VkPhysicalDevice> physical_devices(n_device);
                if (vkEnumeratePhysicalDevices(instance, &n_device, physical_devices.data()) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to enumerate physical device on computer");
                }
                // 3. For each found physical device, check if it is suitable and return the first suitable found. TODO : system of score
                return physical_devices.at(0);
                throw std::runtime_error("Failed to find a valid GPU with the given preferences");
            }

        } // namespace _physical

    } // _device
} // vulkan_wrapper