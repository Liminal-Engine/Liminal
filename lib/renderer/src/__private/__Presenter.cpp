/**
 * @file __Presenter.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__Presenter.hpp"
#include "__private/__Status.hpp"

#include <logger/logger.hpp>

#include <vulkan/vulkan_raii.hpp>

#include <vector>

namespace renderer {
    namespace __private {
        class __Presenter::__Impl {
            private:
                std::vector<vk::raii::Framebuffer> __frameBuffers;
                vk::raii::CommandPool __commandPool;
                vk::raii::CommandBuffers __commandBuffers;
                std::unordered_map<std::string, vk::raii::Semaphore> __semaphores;
                std::unordered_map<std::string, vk::raii::Fence> __fences;

                static std::vector<vk::raii::Framebuffer> __createFrameBuffers(
                    const __GPU &gpu,
                    const __SwapChain &swapChain,
                    const __PipelineHandler &pipelineHandler
                ) {
                    const std::vector<vk::raii::ImageView> &swapChainImageViews = swapChain.getImageViews();
                    const __SwapChain::__Settings &swapChainSettings = swapChain.getSettings();
                    vk::RenderPass pipelineRenderPass = *(pipelineHandler.getRenderPass());
                    std::vector<vk::raii::Framebuffer> res;
                    res.reserve(swapChainImageViews.size());

                    logger::trace << "Creating frame buffers for GPU " << gpu.getName() << std::endl;
                    for (const vk::raii::ImageView &imageView : swapChainImageViews) {
                        std::vector<vk::ImageView> attachments{ *imageView };
                        vk::FramebufferCreateInfo createInfo(
                            {},
                            pipelineRenderPass,
                            attachments,
                            swapChainSettings.getExtent().width,
                            swapChainSettings.getExtent().height,
                            1
                        );
                        res.push_back(vk::raii::Framebuffer(gpu.getVKLogicalDevice(), createInfo));
                    }
                    return res;
                }

                static vk::raii::CommandPool __createCommandPool(const __GPU &gpu) {
                    logger::trace << "Retrieving graphics queue for command pool creation for GPU " << gpu.getName() << std::endl;
                    std::optional<std::reference_wrapper<const __GPU::__Queue>> graphicsQueue = gpu.getQueue("graphics_present");
                    if ( !graphicsQueue.has_value() ) graphicsQueue = gpu.getQueue("graphics");
                    if ( !graphicsQueue.has_value() ) {
                        logger::error << "Failed to find the graphics queue when creating the command pool for GPU" << gpu.getName() << std::endl;
                        return vk::raii::CommandPool(nullptr);
                    }
                    logger::trace << "Creating command pool create info for GPU " << gpu.getName() << std::endl;
                    vk::CommandPoolCreateInfo createInfo(vk::CommandPoolCreateFlagBits::eResetCommandBuffer, graphicsQueue->get().getIndex());
                    logger::trace << "Creating command pool for GPU " << gpu.getName() << std::endl;
                    return vk::raii::CommandPool(gpu.getVKLogicalDevice(), createInfo);
                }

                static vk::raii::CommandBuffers __createCommandBuffers(const __GPU &gpu, const vk::raii::CommandPool &commandPool) {
                    logger::trace << "Creating command buffers allocation info for GPU " << gpu.getName() << std::endl;
                    vk::CommandBufferAllocateInfo allocInfo(*commandPool, vk::CommandBufferLevel::ePrimary, 1);
                    logger::trace << "Creating command buffers for GPU " << gpu.getName() << std::endl;
                    return vk::raii::CommandBuffers(gpu.getVKLogicalDevice(), allocInfo);
                }

                static std::unordered_map<std::string, vk::raii::Semaphore> __createSemaphores(const __GPU &gpu) {
                    vk::SemaphoreCreateInfo createInfo;
                    std::unordered_map<std::string, vk::raii::Semaphore> res;
                    
                    logger::trace << "Creating \"image_available\" semaphore for GPU " << gpu.getName() << std::endl;
                    res.try_emplace("image_available", gpu.getVKLogicalDevice(), createInfo);
                    logger::trace << "Creating \"render_finished\" semaphore for GPU " << gpu.getName() << std::endl;
                    res.try_emplace("render_finished", gpu.getVKLogicalDevice(), createInfo);
                    return res;
                }

                static std::unordered_map<std::string, vk::raii::Fence> __createFences(const __GPU &gpu) {
                    vk::FenceCreateInfo createInfo(vk::FenceCreateFlagBits::eSignaled);
                    std::unordered_map<std::string, vk::raii::Fence> res;

                    logger::trace << "Creating \"render_finished\" fence for GPU " << gpu.getName() << std::endl;
                    res.try_emplace("render_finished", gpu.getVKLogicalDevice(), createInfo);
                    return res;
                }

                __Status __recordCommandBuffer(const uint32_t &imageIndex, const __SwapChain &swapChain, const __PipelineHandler &pipelineHandler) const {
                    // 0. Setup variables
                    const __SwapChain::__Settings &swapChainSettings = swapChain.getSettings();
                    // 1. Record command buffer
                    vk::CommandBufferBeginInfo commandBufferBeginInfo;
                    this->__commandBuffers.at(0).begin(commandBufferBeginInfo);
                    // 2. Start render pass
                    // 2.1 Create begin info
                    vk::Rect2D renderArea(vk::Offset2D(0, 0), swapChain.getSettings().getExtent());
                    vk::ClearValue clearValue(vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f}));
                    vk::RenderPassBeginInfo renderPassBeginInfo(*pipelineHandler.getRenderPass(), *this->__frameBuffers[imageIndex], renderArea, clearValue);
                    // 2.2 Start
                    this->__commandBuffers[0].beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
                    // 2.3 Tell the command buffer which pipeline to use
                    // 2.3.1 Find pipeline
                    const std::optional<std::reference_wrapper<const vk::raii::Pipeline>> &pipeline = pipelineHandler.getPipeline("graphics");
                    if ( !pipeline.has_value() ) {
                        logger::error << "Failed to find \"graphics\" pipeline" << std::endl;
                        return __Status::E_PIPELINE_NOT_FOUND;
                    }
                    // 2.3.2 Bind pipeline to the command buffer
                    this->__commandBuffers[0].bindPipeline(vk::PipelineBindPoint::eGraphics, *pipeline->get());
                    // 5. Since viewport and scissor are dynamic in graphics pipeline, we need to set them again here
                    // TODO : why make them dynamic ? Maybe undynamic them
                    vk::Viewport viewport(0.0f, 0.0f, swapChainSettings.getExtent().width, swapChainSettings.getExtent().height, 0.0f, 1.0f);
                    vk::Rect2D scissor(vk::Offset2D(0, 0), swapChainSettings.getExtent());
                    this->__commandBuffers[0].setViewport(0, viewport);
                    this->__commandBuffers[0].setScissor(0, scissor);
                    // 6. Draw
                    this->__commandBuffers[0].draw(3, 1, 0, 0);
                    // 7. End render pass
                    this->__commandBuffers[0].endRenderPass();
                    // 8. Finish command buffer recording
                    this->__commandBuffers[0].end();
                    return __Status::E_OK;
                }

            public:
                __Impl(
                    const __GPU &gpu,
                    const __SwapChain &swapChain,
                    const __PipelineHandler &pipelineHandler
                ) :
                __frameBuffers(__createFrameBuffers(gpu, swapChain, pipelineHandler)),
                __commandPool(__createCommandPool(gpu)),
                __commandBuffers(__createCommandBuffers(gpu, this->__commandPool)),
                __semaphores(__createSemaphores(gpu)),
                __fences(__createFences(gpu))
                {}

                void draw(
                    const __GPU &gpu,
                    const __SwapChain &swapChain,
                    const __PipelineHandler &pipelineHandler
                ) const {
                    // 1. Wait until the previous frame has finished, so that command buffer and sempaphores are available
                    if (gpu.getVKLogicalDevice().waitForFences(*this->__fences.at("render_finished"), vk::True, std::numeric_limits<uint64_t>::max()) != vk::Result::eSuccess) {
                        logger::error << "Error, cannot wait for \"render_finished\" fence" << std::endl;
                        return;
                    }
                    // 2. After waiting, reset the fence to "unsignaled" state
                    gpu.getVKLogicalDevice().resetFences(*this->__fences.at("render_finished"));
                    // 3. Acquire image form the swap chain
                    std::pair<vk::Result, uint32_t> nextImageResult = swapChain.getVKSwapChain().acquireNextImage(std::numeric_limits<uint64_t>::max(), *this->__semaphores.at("image_available"));
                    if (nextImageResult.first != vk::Result::eSuccess) {
                        logger::error << "Failed to find the swap chain next image for GPU " << gpu.getName() << std::endl;
                        return;
                    }
                    uint32_t imageIndex = nextImageResult.second;
                    // 4. Reset and record command buffer
                    this->__commandBuffers.at(0).reset();
                    this->__recordCommandBuffer(imageIndex, swapChain, pipelineHandler);
                    // 5. Submit command buffer after recording it (NOTE: recording MAY not need to appen each frame)
                    // 5.1 Create submit info
                    vk::PipelineStageFlags waitStages(vk::PipelineStageFlagBits::eTopOfPipe);
                    vk::SubmitInfo submitInfo(
                        *this->__semaphores.at("image_available"),
                        waitStages,
                        *this->__commandBuffers.at(0),
                        *this->__semaphores.at("render_finished")
                    );
                    // 5.2 Find the queue to submit
                    std::optional<std::reference_wrapper<const __GPU::__Queue>> graphicsQueue = gpu.getQueue("graphics_present");
                    if ( !graphicsQueue.has_value() ) graphicsQueue = gpu.getQueue("graphics");
                    if ( !graphicsQueue.has_value() ) {
                        logger::error << "Failed to find the graphics queue when creating the command pool for GPU" << gpu.getName() << std::endl;
                        return;
                    }
                    graphicsQueue->get().getVKQueue().submit(submitInfo, *this->__fences.at("render_finished"));
                    // 6. Presentation
                    vk::PresentInfoKHR presentInfo(*this->__semaphores.at("render_finished"), *swapChain.getVKSwapChain(), imageIndex);
                    // 7. Tell the swapchain we want to present an image to it (to the image reserved for presentation) using the present queue
                    // 7.1 Find the present queue
                    std::optional<std::reference_wrapper<const __GPU::__Queue>> presentQueue = gpu.getQueue("graphics_present");
                    if ( !presentQueue.has_value() ) presentQueue = gpu.getQueue("present");
                    if ( !presentQueue.has_value() ) {
                        logger::error << "Failed to find the graphics queue when creating the command pool for GPU" << gpu.getName() << std::endl;
                        return;
                    }
                    // 7.2 Present
                    if (presentQueue->get().getVKQueue().presentKHR(presentInfo) != vk::Result::eSuccess) {
                        logger::error << "Failed to present image for image index " << imageIndex << std::endl;
                        return;
                    }
                }
        };

        __Presenter::__Presenter(
            const __GPU &gpu,
            const __SwapChain &swapChain,
            const __PipelineHandler &pipelineHandler
        ) :
        __impl(std::make_unique<__Impl>(gpu, swapChain, pipelineHandler))
        {}

        __Presenter::~__Presenter() = default;

        void __Presenter::draw(
            const __GPU &gpu,
            const __SwapChain &swapChain,
            const __PipelineHandler &pipelineHandler
        ) const { return this->__impl->draw(gpu, swapChain, pipelineHandler); }
    } // namespace __private
} // namespace renderer
