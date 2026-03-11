/**
 * @file __Buffer.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-04
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__BUFFER__HPP__
#define __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__BUFFER__HPP__

#include "__private/__Status.hpp"
#include "__private/__GPU.hpp"

#include "vulkan/vulkan_raii.hpp"

#include <memory>
#include <set>

namespace renderer_vk_old {
    namespace __private {
        class __Buffer {
            public:
                __Buffer(
                    const __GPU &gpu,
                    const size_t &size,
                    const vk::BufferUsageFlags &usageFlags,
                    const vk::MemoryPropertyFlags &memPropsFlags,
                    const std::set<uint32_t> &queueFamilyIndices,
                    const void *inputData = nullptr
                );
                ~__Buffer();

                const vk::DeviceSize &getSize(void) const;
                const vk::raii::Buffer &getVKBuffer(void) const;
                const vk::raii::DeviceMemory &getVKMemory(void) const;

                __Status mapToGPU(const void *inputData);
                const void *getData(void) const;
                const bool &isMapped(void) const;

                __Status copy(
                    const __Buffer &other,
                    const vk::raii::CommandPool &transferCommandPool
                );

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace __private
    
} // namespace renderer_vk_old



#endif // __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__BUFFER__HPP__