/**
 * @file Context.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-05
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__RENDERER__INCLUDE___PRIVATE__RENDERER__CONTEXT_HPP__
#define __LIMINAL__RENDERER__INCLUDE___PRIVATE__RENDERER__CONTEXT_HPP__




#include "GPU.hpp"

#include <vector>
#include <string>
#include <memory>

#include <vulkan/vulkan_raii.hpp>
#include <GLFW/glfw3.h>

namespace renderer {
    class Context {
        public:
            Context(const vk::raii::Context &vkRAIIContext, GLFWwindow *window);
            ~Context();
        private:
            class _Impl;
            std::unique_ptr<_Impl> _impl;
    };
} // namespace renderer

#endif // __LIMINAL__RENDERER__INCLUDE___PRIVATE__RENDERER__CONTEXT_HPP__
