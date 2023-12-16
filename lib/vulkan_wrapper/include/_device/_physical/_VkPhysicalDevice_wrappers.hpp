/**
 * @file _VkPhysicalDevice_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_VULKAN_WRAPPER_LIB__DEVICE_LOGICAL__VKPHYSICALDEVICE_WRAPPERS_HPP_
#define LIMINAL_VULKAN_WRAPPER_LIB__DEVICE_LOGICAL__VKPHYSICALDEVICE_WRAPPERS_HPP_

#include <vulkan/vulkan.h>
#include <vector>

namespace vulkan_wrapper {
    namespace _device {
        namespace _physical {

            /**
             * @brief Pick a physical device according to preferences
             * 
             * @param instance (onst VkInstance &) The related instance
             * @param surface (onst VkSurfaceKHR &) The related surface
             * @param required_extensions (const std::vector<const char *> &) The required extensions
             * @return The created VkPhysicalDevice 
             */
            VkPhysicalDevice _pick(
                const VkInstance &instance,
                const VkSurfaceKHR &surface,
                const std::vector<const char *> &required_extensions
            );

        } // _physical
    } // _device
} // vulkan_wrapper

#endif // LIMINAL_VULKAN_WRAPPER_LIB__DEVICE_LOGICAL__VKPHYSICALDEVICE_WRAPPERS_HPP_