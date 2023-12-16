/**
 * @file _VkSurfaceKHR_wrappers.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_surface/_VkSurfaceKHR_wrappers.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _surface {
        
        VkSurfaceKHR _load(const VkInstance &instance, GLFWwindow *window) {
            VkSurfaceKHR surface;

            if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
                std::runtime_error("Error while creating window surface");
            }
            return surface;
        }

        void _destroy(
            const VkInstance &instance,
            const VkSurfaceKHR &surface,
            VkAllocationCallbacks *p_allocator
        ) {
            vkDestroySurfaceKHR(instance, surface, p_allocator);
        }

    } // namespace _surface
} // namespace liminal_vulkan_wrapper 

