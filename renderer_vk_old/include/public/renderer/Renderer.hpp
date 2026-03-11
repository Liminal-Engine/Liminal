/**
 * @file Renderer.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__RENDERER_HPP__
#define __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__RENDERER_HPP__

#include <GLFW/glfw3.h>

#include <memory>
namespace renderer_vk_old {
    class Renderer {
        public:
            Renderer(GLFWwindow *window);
            ~Renderer();

            void draw(void);
            void waitForGPUToFinishJobs(void);
            void handleSurfaceChange(void);

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
            

    };
} // namespace renderer_vk_old


#endif // __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__RENDERER_HPP__