/**
 * @file _VkInstance_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKANWRAPPER__INSTANCE__VKINSTANCE_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKANWRAPPER__INSTANCE__VKINSTANCE_WRAPPERS_HPP_

#include "WindowWrapper.hpp"

#include "_layer/_Layer_t.hpp"
#include "_extension/_Extensions_t.hpp"

#include <vulkan/vulkan.h>
#include <string>
#include <vector>

#ifdef NDEBUG    
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

namespace vulkan_wrapper {
    namespace _instance {
        /**
         * @brief Loads a vulkan instance
         * 
         * @param app_name (const std::string &) The application name
         * @param engine_name (const std::string &) The engine name
         * @throw std::runtime_error if any error occurs
         * @return The created VkInstance 
         */
        VkInstance _load(
            const std::string &app_name,
            const std::string &engine_name,
            const _layer::_Layers_t &layers,
            const _extension::_Extensions_t &extensions
        );

        /**
         * @brief Destroy a VkInstance
         * 
         * @param instance (const VkInstance &) The instance to destroy
         * @param p_allocator (VkAllocationCallbacks *) (default = nullptr) Vulkan's custom allocator
         */
        void _destroy(const VkInstance &instance, VkAllocationCallbacks *p_allocator = nullptr);
    } // vulkan_wrapper
} // _instance

#endif // LIMINAL_LIB_VULKANWRAPPER__INSTANCE__VKINSTANCE_WRAPPERS_HPP_
