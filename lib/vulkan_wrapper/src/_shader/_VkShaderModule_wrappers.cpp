/**
 * @file _VkShaderModule_wrappers.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_shader/_VkShaderModule_wrappers.hpp"

#include <vector>
#include <fstream>
#include <stdexcept>

namespace vulkan_wrapper {
    namespace _shader {

        static std::vector<char> __getShaderCode(const std::string &shader_file_path) {
            // 1. Seak at the end and read as binary to avoid text transformation. Increase performances
            std::ifstream file(shader_file_path, std::ios::ate | std::ios::binary);
            if (file.is_open() == false) {
                throw std::runtime_error("Failed to open shader file : " + shader_file_path);
            }
            // 2. Get file size and allocate vector
            size_t file_size = file.tellg();
            std::vector<char> res(file_size);
            // 3. Seek at the begining and read all at once
            file.seekg(0);
            file.read(res.data(), file_size);
            file.close();
            return res;
        }

        VkShaderModule _load(const VkDevice &logical_device, const std::string &shader_file_path) {
            const std::vector<char> code = __getShaderCode(shader_file_path);
            
            VkShaderModuleCreateInfo create_info{};
            create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
            create_info.codeSize = code.size();
            create_info.pCode = reinterpret_cast<const uint32_t *>(code.data()); //code is formated in uint32_t *

            VkShaderModule res{};
            if (vkCreateShaderModule(logical_device, &create_info, nullptr, &res) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create shader module : " + shader_file_path);
            }
            return res;
        }

        void _destroy(
            const VkDevice &logical_device,
            const VkShaderModule &sahder_module,
            const VkAllocationCallbacks *p_allocator
        ) {
            vkDestroyShaderModule(logical_device, sahder_module, p_allocator);
        }

    } // _shader
} // vulkan_wrapper
