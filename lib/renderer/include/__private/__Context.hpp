/**
 * @file __Context.hpp
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


 

#include "__private/__GPU.hpp"

#include <vector>
#include <string>
#include <memory>

#include <GLFW/glfw3.h>
#include <vulkan/vulkan_raii.hpp>

namespace renderer {
    namespace __private {
        class __Context {
            public:
                __Context(GLFWwindow *window);
                ~__Context();
    
                const vk::raii::Context& getVKRAIIContext(void) const;
                const vk::raii::Instance& getVKInstance(void) const;
                const vk::raii::SurfaceKHR& getVKSurface(void) const;
                const __GPU &getGPU(void) const;
    
            private:
                class _Impl;
                std::unique_ptr<_Impl> _impl;
        };
    } // namespace __private
} // namespace renderer

#endif // __LIMINAL__RENDERER__INCLUDE___PRIVATE__RENDERER__CONTEXT_HPP__
