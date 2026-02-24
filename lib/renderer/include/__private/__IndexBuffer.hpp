/**
 * @file __IndexBuffer.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2026-02-24
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__LIB__RENDERER__INCLDUE__PRIVATE__INDEX_BUFFER_HPP__
#define __LIMINAL__LIB__RENDERER__INCLDUE__PRIVATE__INDEX_BUFFER_HPP__

#include "__private/__GPU.hpp"
#include "temp_consts_need_to_remove_this.hpp"
#include "__private/__Buffer.hpp"

#include <vulkan/vulkan_raii.hpp>

#include <memory>

namespace renderer {
    namespace __private {
        class __IndexBuffer {
            public:
                __IndexBuffer(
                    const __GPU &gpu,
                    const std::vector<uint16_t> &indices,
                    const vk::raii::CommandPool &transferCommandPool
                );
                ~__IndexBuffer();

                __Status mapToGPU(const void *inputData);
                const vk::raii::Buffer &getVKBuffer(void) const;
                const __Buffer &getBuffer(void) const;

                const bool &isMapped(void) const;

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace __private 
} // namespace renderer

#endif // __LIMINAL__LIB__RENDERER__INCLDUE__PRIVATE__INDEX_BUFFER_HPP__

