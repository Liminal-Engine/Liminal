/**
 * @file _VkSurfaceKHR_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKANWRAPPER__SURFACE__VKSURFACEKHR_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKANWRAPPER__SURFACE__VKSURFACEKHR_WRAPPERS_HPP_

#include "WindowWrapper.hpp"

#include <vulkan/vulkan.h>

namespace vulkan_wrapper {
    namespace _surface {
        
        /**
         * @brief Loads a VkSurfaceKHR
         * 
         * @param instance (const VkInstance &) The related vulkan instance
         * @param window (const window_wrapper::WindowWrapper &) The application window
         * @throw
         * @return The created VkSurfaceKHR
         */
        VkSurfaceKHR _load(const VkInstance &instance, const window_wrapper::WindowWrapper &window);

        /**
         * @brief Destroy a VkSurfaceKHR
         * 
         * @param instance (const VkInstance &) The related VkInstance
         * @param surface (const VkSurfaceKHR &) The surface to destroy
         * @param p_allocator (VkAllocationCallbacks *) (default = nullptr) Vulkan custom allcator
         */
        void _destroy(
            const VkInstance &instance,
            const VkSurfaceKHR &surface,
            VkAllocationCallbacks *p_allocator = nullptr
        );


    } // namespace _surface
} // namespace liminal_vulkan_wrapper 

#endif // LIMINAL_LIB_VULKANWRAPPER__SURFACE__VKSURFACEKHR_WRAPPERS_HPP_
