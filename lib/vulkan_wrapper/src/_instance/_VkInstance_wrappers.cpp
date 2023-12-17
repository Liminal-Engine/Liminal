/**
 * @file _VkInstance_wrappers.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_instance/_VkInstance_wrappers.hpp"

#include <stdexcept>


const std::vector<const char*> VALIDATION_LAYERS = {
    "VK_LAYER_KHRONOS_validation"
};


#include <iostream>

namespace vulkan_wrapper {
    namespace _instance {

        /**
         * @brief Loads a VkApplicationInfo
         * 
         * @param app_name (const std::string &) The application name
         * @param engine_name (const std::string &) The engine name
         * @return The created VkApplicationInfo
        */
        static VkApplicationInfo __loadAppInfo(const std::string &app_name, const std::string &engine_name) {
            VkApplicationInfo res{};

            res.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            res.pApplicationName = app_name.c_str(),
            res.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            res.pEngineName = engine_name.c_str(),
            res.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            res.apiVersion = VK_API_VERSION_1_0;
            res.pNext = nullptr;
            return res;
        }

        /**
         * @brief Loadqs a VkInstanceCreateInfo
         * 
         * @param app_info (VkApplicationInfo *) - A pointer to a VkApplicationInfo to
         * integrate in the final VkInstanceCreateInfo
         * @return The created VkInstanceCreateInfo 
        */
        static VkInstanceCreateInfo __loadCreateInfo(
            VkApplicationInfo *app_info,
            const _layer::_Layers_t &layers,
            const _extension::_Extensions_t &extensions
        ) {
            VkInstanceCreateInfo create_info{};
            create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            create_info.pApplicationInfo = app_info;
            // 2.1 Get extensions required by GLFW.
            create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.at("window").size()); //TODO : see why only window and try with all extensions
            create_info.ppEnabledExtensionNames = extensions.at("window").data();
            create_info.enabledLayerCount = static_cast<uint32_t>(layers.size());
            create_info.ppEnabledLayerNames = layers.data();
            return create_info;
        }
        
        VkInstance _load(
            const std::string &app_name,
            const std::string &engine_name,
            const _layer::_Layers_t &layers,
            const _extension::_Extensions_t &extensions
        ) {
            if (app_name == "" || engine_name == "") {
                throw std::runtime_error("Parameter errors while creating instance");
            }
            // 1. Create appInfo : Optional but provides useful info to the driver in order to optimize.
            VkApplicationInfo app_info = __loadAppInfo(app_name, engine_name);
            // 2. Optional. Tells Vulan driver which extensions and validation layers we want to use.
            VkInstanceCreateInfo create_info = __loadCreateInfo(&app_info, layers, extensions);
            // 3. TODO : add validation layers in DEBUG mode ONLY
            VkInstance res;
            if (vkCreateInstance(&create_info, nullptr, &res) != VK_SUCCESS) {
                throw std::runtime_error("Error while creating the Vulkan instance");
            }
            return res;
        }
        
        void _destroy(const VkInstance &instance, VkAllocationCallbacks *p_allocator) {
            vkDestroyInstance(instance, p_allocator);
        }

    } // vulkan_wrapper
} // _instance
