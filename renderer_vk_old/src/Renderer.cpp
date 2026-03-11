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

namespace renderer_vk_old {
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
                if (const __private::__Status presenterDrawStatus = this->__presenter.draw(); presenterDrawStatus != __private::__Status::E_OK) {
                    switch (presenterDrawStatus) {
                        case __private::__Status::E_PRESENT_QUEUE_OUT_OF_DATE:
                        case __private::__Status::E_PRESENT_QUEUE_SUBOPTIMAL:
                        case __private::__Status::E_SWAP_CHAIN_OUT_OF_DATE:
                        case __private::__Status::E_SWAP_CHAIN_SUBOPTIMAL:
                            return this->handleSurfaceChange();
                        default:
                            break;
                    }
                }
            }

            void waitForGPUToFinishJobs(void) {
                this->__context.getGPU().getVKLogicalDevice().waitIdle();
            }

            void handleSurfaceChange(void) {
                /**
                 * Things that needs to be recreated upon surface change (in this exact order only)
                 * 1. SwapChain:
                 *      1.1 SwapChain VK image views
                 *      1.2 Swap chain VK images
                 *      1.3 VK swap chain
                 * 2. Pipeline Handler (under conditions)
                 *      2.1 PipelineHandler VK render pass if __SwapChain::__Settings__Format has changed
                 *      2.2 PipelineHandler VK graphics pipelines if render pass has changed or viewport is non dynamic (Liminal Engine has dynamic viewport)
                 * 3. Presenter:
                 *      3.1 Presenter VK framebuffers
                **/
                // 1. Wait for the GPU to finish all its ongoing jobs
                logger::trace << "Renderer waiting for GPU to finish all jobs..." << std::endl;
                this->waitForGPUToFinishJobs();
                // 2. Update surface properties
                logger::trace << "Renderer updating surface properties" << std::endl;
                this->__context.getGPU().getSurfaceSupport().update();
                // 3. Update swap chain
                logger::trace << "Renderer updating Swap Chain" << std::endl;
                const vk::SurfaceFormatKHR oldSwapChainFormat = this->__swapChain.getSettings().getFormat();
                this->__swapChain.updateUponSurfaceChange();
                // 4. If the format has changed update pipeline handler
                if (oldSwapChainFormat != this->__swapChain.getSettings().getFormat()) {
                    logger::trace << "SwapChain format has changed, so updating pipeline handler" << std::endl;
                    this->__pipelineHandler.updateUponSwapChainFormatChange();
                }
                // 5. Update presenter
                logger::trace << "Renderer updating Presenter" << std::endl;
                this->__presenter.updateUponSurfaceChange();
            }

    };

    Renderer::Renderer(GLFWwindow *window) : __impl(std::make_unique<__Impl>(window))
    {}

    Renderer::~Renderer() = default;

    void Renderer::draw(void) { this->__impl->draw(); }
    void Renderer::waitForGPUToFinishJobs(void) { this->__impl->waitForGPUToFinishJobs(); }
    void Renderer::handleSurfaceChange(void) { this->__impl->handleSurfaceChange(); }

} // namespace renderer_vk_old
