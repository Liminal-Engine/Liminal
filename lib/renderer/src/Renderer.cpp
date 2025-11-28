/**
 * @file Renderer.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__vkConfig.hpp"
#include "Renderer.hpp"
#include "__private/__Status.hpp"
#include "__private/__Context.hpp"
#include "__private/__GPU.hpp"
#include "__private/__SwapChain.hpp"
#include "__private/__PipelineHandler.hpp"
#include "__private/__Presenter.hpp"

#include <logger/logger.hpp>

#include <vulkan/vulkan_raii.hpp>

#include <vector>

namespace renderer {
    class Renderer::__Impl {
        private:
            GLFWwindow *__window;
            __private::__Context __context;
            __private::__SwapChain __swapChain;
            __private::__PipelineHandler __pipelineHandler;
            __private::__Presenter __presenter;

            static __private::__Context __createContext(GLFWwindow *window) {
                logger::info << "Creating renderer context" << std::endl;
                return __private::__Context(window);
            }

            static __private::__SwapChain __createSwapChain(GLFWwindow *window, __private::__GPU &gpu, const vk::raii::SurfaceKHR &surface) {
                logger::info << "Creating swap chain for GPU " << gpu.getName() << std::endl;
                return __private::__SwapChain(window,surface, gpu);
            }

            static __private::__PipelineHandler __createPipelineHandler(const __private::__GPU &gpu, const __private::__SwapChain &swapChain) {
                logger::info << "Creating pipeline handler for GPU " << gpu.getName() << std::endl;
                return __private::__PipelineHandler(gpu, swapChain);
            }

            static __private::__Presenter __createPresenter(__private::__GPU &gpu, __private::__SwapChain &swapChain, const __private::__PipelineHandler &pipelineHandler) {
                logger::info << "Creating presenter for GPU " << gpu.getName() << std::endl;
                return __private::__Presenter(gpu, swapChain, pipelineHandler);
            }

        public:
            __Impl(GLFWwindow *window) :
            __window(window),
            __context(__createContext(window)),
            __swapChain(__createSwapChain(window, this->__context.getGPU(), this->__context.getVKSurface())),
            __pipelineHandler(__createPipelineHandler(this->__context.getGPU(), this->__swapChain)),
            __presenter(__createPresenter(this->__context.getGPU(), this->__swapChain, this->__pipelineHandler))
            {}

            void draw(void) {
                // 3. Draw
                this->__presenter.draw();
            }

            void waitForGPUToFinishJobs(void) {
                this->__context.getGPU().getVKLogicalDevice().waitIdle();
            }

    };

    Renderer::Renderer(GLFWwindow *window) : __impl(std::make_unique<__Impl>(window))
    {}

    Renderer::~Renderer() = default;

    void Renderer::draw(void) { this->__impl->draw(); }
    void Renderer::waitForGPUToFinishJobs(void) { this->__impl->waitForGPUToFinishJobs(); }

} // namespace renderer
