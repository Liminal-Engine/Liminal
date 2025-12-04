/**
 * @file __VertexBuffer.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-03
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__BUFFER_HPP__
#define __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__BUFFER_HPP__

#include "__private/__GPU.hpp"
#include "temp_consts_need_to_remove_this.hpp"

#include <vulkan/vulkan_raii.hpp>

#include <memory>

namespace renderer {
    namespace __private {
        class __VertexBuffer {
            public:
            // For now, we can only create VertexBuffer (from a primivite, e.g. an array of vertex)
            __VertexBuffer(const __GPU &gpu, const std::vector<VERTEX> &vertices);
                ~__VertexBuffer();

                const vk::raii::Buffer &getVKBuffer(void) const;

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;


        };
    } // namespace __private
    
    
} // namespace renderer

#endif // __LIMINAL__LIB__RENDERER__INCLUDE__PRIVATE__BUFFER_HPP__