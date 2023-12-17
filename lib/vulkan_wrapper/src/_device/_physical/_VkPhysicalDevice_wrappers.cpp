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
#include "_queue/_QueueFamilies.hpp"
#include "_extension/_Extensions_t.hpp"
#include "_swap_chain/_Supports.hpp"

#include <stdexcept>
#include <iostream>

namespace vulkan_wrapper {
    namespace _device {
        namespace _physical {

            // Checks if the given physical device is suitable with the given surface and extensions.
            // You should do this for all physical device found on the host
            static bool _isPhysicalDeviceSuitable(
                const VkPhysicalDevice &physical_device,
                const VkSurfaceKHR &surface,
                const _extension::_Extensions_group_t &wanted_device_extension_group

            ) {
                VkPhysicalDeviceProperties physical_device_properties{};
                VkPhysicalDeviceFeatures physical_device_features{};
                _queue::_QueueFamilies physical_device_queue_families{};

                vkGetPhysicalDeviceProperties(physical_device, &physical_device_properties);
                vkGetPhysicalDeviceFeatures(physical_device, &physical_device_features);
                physical_device_queue_families = _queue::_load(physical_device, surface);

                std::cout << "Device name : " << physical_device_properties.deviceName << std::endl;
                // 1. Check if required extensions are supported
                if (_extension::_checkPhysicalDeviceExtensionSupport(physical_device, wanted_device_extension_group) == true) {
                    // 2. Get the physical device swap chain supports and check for surface formats and presentation mode
                    _swap_chain::_Supports swap_chain_supports = _swap_chain::_getSupports(physical_device, surface);
                    if (swap_chain_supports._presentationModes.empty() == false && swap_chain_supports._surfaceFormats.empty() == false) {
                        // 3. Checks if all wanted queue families are present (THIS IS HARCODED AND MUST BE CHANGED #TODO)
                        if (physical_device_queue_families._graphicsFamily.has_value() && physical_device_queue_families._presentFamily.has_value()) {
                            return true;
                        }
                    }
                }
                return false;
            }
            
            VkPhysicalDevice _pick(
                const VkInstance &instance,
                const VkSurfaceKHR &surface,
                const _extension::_Extensions_group_t &wanteed_device_extension_group
            ) {
                (void)surface;
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
                // 3. For each found physical device, check if it is suitable and return the first suitable found. #TODO : system of score
                for (const VkPhysicalDevice &physical_device : physical_devices) {
                    if (_isPhysicalDeviceSuitable(physical_device, surface, wanteed_device_extension_group)) {
                        return physical_device;
                    }
                }
                throw std::runtime_error("Failed to find a valid GPU with the given preferences");
            }

        } // namespace _physical

    } // _device
} // vulkan_wrapper