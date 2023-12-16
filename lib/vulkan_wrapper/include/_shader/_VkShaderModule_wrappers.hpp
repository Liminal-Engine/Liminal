/**
 * @file _VkShaderModule_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__SHADER__VKSHADERMODULE_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__SHADER__VKSHADERMODULE_WRAPPERS_HPP_

#include  <vulkan/vulkan.h>
#include <string>

namespace vulkan_wrapper {
    namespace _shader {

        /**
         * @brief Loads a Vulkan shader module, representing a shader
         * 
         * @param logical_device (const VkDevice &) The related Vulkan logical device
         * @param shader_file_path (const std::string &) The compiled shader file path
         * @return The created vulkan shader module handler (VkShaderModule )
         */
        VkShaderModule _load(const VkDevice &logical_device, const std::string &shader_file_path);

        /**
         * @brief Destroy a shader module
         * 
         * @param logical_device (const VkDevice &) The related Vulkan logical device
         * @param sahder_module (const VkShaderModule &) The shader module to destroy
         * @param p_allocator (const VkAllocationCallbacks *) (defualt = nullptr) The Vulkan custom allocator
         */
        void _destroy(
            const VkDevice &logical_device,
            const VkShaderModule &sahder_module,
            const VkAllocationCallbacks *p_allocator = nullptr
        );

    } // _shader
} // vulkan_wrapper

#endif // LIMINAL_LIB_VULKAN_WRAPPER__SHADER__VKSHADERMODULE_WRAPPERS_HPP_