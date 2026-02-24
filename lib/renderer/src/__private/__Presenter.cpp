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

#include "__private/__vkConfig.hpp"
#include "__private/__Presenter.hpp"
#include "__private/__Status.hpp"
#include "__private/__errors.hpp"
#include "temp_consts_need_to_remove_this.hpp"
#include "__private/__IndexBuffer.hpp"

#include <logger/logger.hpp>
#include <parseop/parseop.hpp>

#include <vulkan/vulkan_raii.hpp>

#include <vector>
#include <array>

namespace renderer {
    namespace __private {
        class __Presenter::__Impl {
            private:
                __GPU &__relatedGPU;
                __SwapChain &__relatedSwapChain;
                const __PipelineHandler &__relatedPipelineHandler;

                const __GPU::__Queue &__gpuGraphicsQueue;
                const __GPU::__Queue &__gpuPresentQueue;

                std::vector<vk::raii::Framebuffer> __frameBuffers;
                vk::raii::CommandPool __graphicsCommandPool;
                vk::raii::CommandPool __transferCommandPool;
                // we don't need raii here since they're auto destroyed when command pool is destroyed.
                // They are easier to create when non RAII
                std::vector<vk::CommandBuffer> __commandBuffers;
                std::vector<vk::raii::Semaphore> __imageAvailableSemaphores;
                std::vector<vk::raii::Semaphore> __renderFinishedSemaphores;
                std::vector<vk::raii::Fence> __renderFinishedFences;
                uint32_t __currentFrame;

                __VertexBuffer __vertexBuffer;
                __IndexBuffer __indexBuffer;




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
                        const vk::FramebufferCreateInfo createInfo(
                            {},
                            pipelineRenderPass,
                            attachments,
                            swapChainSettings.getExtent().width,
                            swapChainSettings.getExtent().height,
                            1
                        );
                        auto [result, rawFrameBuffer] = gpu.getRawVKLogicalDevice().createFramebuffer(createInfo);
                        if (result != vk::Result::eSuccess) {
                            __LOG_VK_CREATE_ERROR(gpu, result, "Presenter failed to create a framebuffer");
                            return std::vector<vk::raii::Framebuffer>{};
                        } else {
                            res.push_back(vk::raii::Framebuffer(gpu.getVKLogicalDevice(), rawFrameBuffer));
                        }
                    }
                    return res;
                }

                static vk::raii::CommandPool __createCommandPool(
                    const __GPU &gpu,
                    const __GPU::__Queue &relatedQueue,
                    const vk::CommandPoolCreateFlags &commandPoolCreateFlags
                ) {
                    logger::trace << "Retrieving graphics queue for command pool creation for GPU " << gpu.getName() << std::endl;
                    logger::trace << "Creating command pool create info for GPU " << gpu.getName() << std::endl;
                    vk::CommandPoolCreateInfo createInfo(commandPoolCreateFlags, relatedQueue.getFamilyIndex());
                    logger::trace << "Creating command pool for GPU " << gpu.getName() << std::endl;
                    auto [result, rawCommandPool] = gpu.getRawVKLogicalDevice().createCommandPool(createInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "Presenter failed to create a command pool for queue " + relatedQueue.getName());
                        return vk::raii::CommandPool(nullptr);
                    }
                    return vk::raii::CommandPool(gpu.getVKLogicalDevice(), rawCommandPool);
                }

                static std::vector<vk::CommandBuffer>__createCommandBuffers(const __GPU &gpu, const vk::raii::CommandPool &commandPool) {
                    logger::trace << "Creating command buffers allocation info for GPU " << gpu.getName() << std::endl;
                    vk::CommandBufferAllocateInfo allocInfo(*commandPool, vk::CommandBufferLevel::ePrimary, MAX_FRAMES_IN_FLIGHT);
                    logger::trace << "Creating command buffers for GPU " << gpu.getName() << std::endl;
                    auto [result, rawCommandBuffers] = gpu.getRawVKLogicalDevice().allocateCommandBuffers(allocInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "Presenter failed to create command buffers");
                        return std::vector<vk::CommandBuffer>{};
                    }
                    return rawCommandBuffers;
                }

                static vk::raii::Semaphore __createSemaphore(const __GPU &gpu) {
                    logger::trace << "Creating a semaphore for GPU " << gpu.getName() << std::endl;
                    vk::SemaphoreCreateInfo createInfo;
                    auto [result, rawSemaphore] = gpu.getRawVKLogicalDevice().createSemaphore(createInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "Presenter failed to create semaphore");
                        return vk::raii::Semaphore(nullptr);
                    }
                    return vk::raii::Semaphore(gpu.getVKLogicalDevice(), rawSemaphore);
                }

                static vk::raii::Fence __createFence(const __GPU &gpu, const vk::FenceCreateFlags createFlags = {}) {
                    logger::trace << "Creating a fence for GPU " << gpu.getName() << std::endl;
                    vk::FenceCreateInfo createInfo(createFlags);
                    auto [result, rawFence] = gpu.getRawVKLogicalDevice().createFence(createInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "Presenter failed to create fence");
                        return vk::raii::Fence(nullptr);
                    }
                    return vk::raii::Fence(gpu.getVKLogicalDevice(), rawFence);
                }

                __Status __bindCurrentCommandBufferToVertexBuffer(const __VertexBuffer &vertexBuffer) const {
                    if ( !vertexBuffer.isMapped() ) {
                        logger::error << "Renderer cannot bind current command buffer to a buffer. The buffer is not mapped for GPU " << this->__relatedGPU.getName() << std::endl;
                        return __Status::E_BUFFER_NOT_MAPPED;
                    }
                    this->__commandBuffers[this->__currentFrame].bindVertexBuffers(0, *vertexBuffer.getVKBuffer(), vk::DeviceSize(0));
                    return __Status::E_OK;
                }

                __Status __bindCurrentCommandBufferToIndexBuffer(const __IndexBuffer &indexBuffer) const {
                    if ( indexBuffer.isMapped() == false ) {
                        logger::error << "Renderer cannot bind current command buffer to an index buffer. The index buffer is not mapped for GPU " << this->__relatedGPU.getName() << std::endl;
                        return __Status::E_BUFFER_NOT_MAPPED;
                    }
                    this->__commandBuffers[this->__currentFrame].bindIndexBuffer(*indexBuffer.getVKBuffer(), vk::DeviceSize(0), vk::IndexType::eUint16);
                    return __Status::E_OK;
                }

                __Status __recordCommandBuffer(const uint32_t &nextImage, const __SwapChain &swapChain, const __PipelineHandler &pipelineHandler) const {
                    // 0. Setup variables
                    const __SwapChain::__Settings &swapChainSettings = swapChain.getSettings();
                    // 1. Record command buffer
                    vk::CommandBufferBeginInfo commandBufferBeginInfo;
                    if (this->__commandBuffers[this->__currentFrame].begin(commandBufferBeginInfo) != vk::Result::eSuccess) {
                        logger::error << "Failed to record command buffer" << std::endl;
                        return __Status::E_VK_INTERNAL_ERROR;
                    }
                    // 2. Start render pass
                    // 2.1 Create begin info
                    vk::Rect2D renderArea(vk::Offset2D(0, 0), swapChain.getSettings().getExtent());
                    vk::ClearValue clearValue(vk::ClearColorValue(std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f}));
                    vk::RenderPassBeginInfo renderPassBeginInfo(*pipelineHandler.getRenderPass(), *this->__frameBuffers[nextImage], renderArea, clearValue);
                    // 2.2 Start
                    this->__commandBuffers[this->__currentFrame].beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
                    // 2.3 Tell the command buffer which pipeline to use
                    // 2.3.1 Find pipeline
                    const std::optional<std::reference_wrapper<const vk::raii::Pipeline>> &pipeline = pipelineHandler.getPipeline("GRAPHICS");
                    if ( !pipeline.has_value() ) {
                        logger::error << "Failed to find \"graphics\" pipeline" << std::endl;
                        return __Status::E_PIPELINE_NOT_FOUND;
                    }
                    // 2.3.2 Bind pipeline to the command buffer
                    this->__commandBuffers[this->__currentFrame].bindPipeline(vk::PipelineBindPoint::eGraphics, *pipeline->get());
                    // 2.3.3 Bind the vertex buffer to the current command buffer
                    if (
                        __Status bindVertexBufferStatus;
                        (bindVertexBufferStatus = this->__bindCurrentCommandBufferToVertexBuffer(this->__vertexBuffer)) != __Status::E_OK
                    ) {
                        logger::error << "Presenter failed to bind current command buffer to vertex buffer for GPU " << this->__relatedGPU.getName() << std::endl;
                        return bindVertexBufferStatus;
                    }
                    // 2.3.4 Bind the index buffer to the current command buffer
                    if (
                        __Status bindIndexBufferStatus;
                        (bindIndexBufferStatus = this->__bindCurrentCommandBufferToIndexBuffer(this->__indexBuffer)) != __Status::E_OK
                    ) {
                        logger::error << "Presenter failed to bnd the currend command buffer to an index buffer for GPU " << this->__relatedGPU.getName() << std::endl;
                        return bindIndexBufferStatus;
                    }
                    
                    // 5. Since viewport and scissor are dynamic in graphics pipeline, we need to set them again here
                    // TODO : why make them dynamic ? Maybe undynamic them
                    vk::Viewport viewport(0.0f, 0.0f, swapChainSettings.getExtent().width, swapChainSettings.getExtent().height, 0.0f, 1.0f);
                    vk::Rect2D scissor(vk::Offset2D(0, 0), swapChainSettings.getExtent());
                    this->__commandBuffers[this->__currentFrame].setViewport(0, viewport);
                    this->__commandBuffers[this->__currentFrame].setScissor(0, scissor);
                    // 6. Draw
                    this->__commandBuffers[this->__currentFrame].drawIndexed(static_cast<uint32_t>(INDICES.size()), 1, 0, 0, 0);
                    // this->__commandBuffers[this->__currentFrame].draw(static_cast<uint32_t>(VERTICES.size()), 1, 0, 0);
                    // 7. End render pass
                    this->__commandBuffers[this->__currentFrame].endRenderPass();
                    // 8. Finish command buffer recording
                    if (this->__commandBuffers[this->__currentFrame].end() != vk::Result::eSuccess) {
                        logger::error << "Failed to end command buffer recording" << std::endl;
                        return __Status::E_VK_INTERNAL_ERROR;
                    }
                    return __Status::E_OK;
                }

                static __VertexBuffer __createVertexBuffer(
                    const __GPU &gpu,
                    const std::vector<VERTEX> &vertexData,
                    const vk::raii::CommandPool &commandPool
                ) {
                    logger::trace << "Presenter creating a vertex buffer for GPU " << gpu.getName() << std::endl;
                    return __VertexBuffer(gpu, vertexData, commandPool);                                        
                }

                static __IndexBuffer __createIndexBuffer(
                    const __GPU &gpu,
                    const std::vector<uint16_t> &indices,
                    const vk::raii::CommandPool &commandPool
                ) {
                    logger::trace << "Presenter creating an index buffer for GPU " << gpu.getName() << std::endl;
                    return __IndexBuffer(gpu, indices, commandPool);
                }
          
                public:
                __Impl(
                    __GPU &gpu,
                    __SwapChain &swapChain,
                    const __PipelineHandler &pipelineHandler
                ) :
                __relatedGPU(gpu),
                __relatedSwapChain(swapChain),
                __relatedPipelineHandler(pipelineHandler),
                __gpuGraphicsQueue(this->__relatedGPU.getGraphicsQueue()),
                __gpuPresentQueue(this->__relatedGPU.getPresentQueue()),
                __frameBuffers(__createFrameBuffers(this->__relatedGPU, this->__relatedSwapChain, this->__relatedPipelineHandler)),
                __graphicsCommandPool(__createCommandPool(this->__relatedGPU, this->__relatedGPU.getGraphicsQueue(), vk::CommandPoolCreateFlagBits::eResetCommandBuffer)),
                __transferCommandPool(__createCommandPool(this->__relatedGPU, this->__relatedGPU.getTransferQueue(), vk::CommandPoolCreateFlagBits::eTransient | vk::CommandPoolCreateFlagBits::eResetCommandBuffer)),
                __commandBuffers(__createCommandBuffers(this->__relatedGPU, this->__graphicsCommandPool)),
                __imageAvailableSemaphores([&]() -> std::vector<vk::raii::Semaphore> {
                    std::vector<vk::raii::Semaphore> res; res.reserve(MAX_FRAMES_IN_FLIGHT);

                    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
                        logger::trace << "Creating image available semaphore " << i << " for GPU " << this->__relatedGPU.getName() << std::endl;
                        res.push_back(__createSemaphore(this->__relatedGPU));
                    }
                    return res;
                }()),
                __renderFinishedSemaphores([&]() -> std::vector<vk::raii::Semaphore> {
                    std::vector<vk::raii::Semaphore> res; res.reserve(MAX_FRAMES_IN_FLIGHT);

                    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
                        logger::trace << "Creating render finished semaphore " << i << " for GPU " << this->__relatedGPU.getName() << std::endl;
                        res.push_back(__createSemaphore(this->__relatedGPU));
                    }
                    return res;
                }()),
                __renderFinishedFences([&]() -> std::vector<vk::raii::Fence> {
                    std::vector<vk::raii::Fence> res; res.reserve(MAX_FRAMES_IN_FLIGHT);

                    for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
                        logger::trace << "Creating render finished fence " << i << " for GPU " << this->__relatedGPU.getName() << std::endl;
                        res.push_back(__createFence(this->__relatedGPU, vk::FenceCreateFlagBits::eSignaled));
                    }
                    return res;
                }()),
                __currentFrame(0),
                __vertexBuffer(__createVertexBuffer(this->__relatedGPU, VERTICES, this->__transferCommandPool)),
                __indexBuffer(__createIndexBuffer(this->__relatedGPU, INDICES, this->__transferCommandPool))
                {
                }


                __Status draw(void) {
                    // 1. Wait until the previous frame has finished, so that command buffer and sempaphores are available
                    if (this->__relatedGPU.getVKLogicalDevice().waitForFences(*this->__renderFinishedFences[this->__currentFrame], vk::True, std::numeric_limits<uint64_t>::max()) != vk::Result::eSuccess) {
                        logger::error << "Error, cannot wait for \"render_finished\" fence" << std::endl;
                        return E_WAIT_FENCE;
                    }
                    // 2. Acquire image form the swap chain
                    auto [nextImageStatus, nextImage] = this->__relatedSwapChain.acquireNextimage(this->__imageAvailableSemaphores[this->__currentFrame]);
                    if (nextImageStatus != __Status::E_OK) {
                        logger::info << "Swap chain is no longer compatible. Aborting draw cycle" << std::endl;
                        return nextImageStatus;
                    }
                    // 3. make sure the fence goes back to "unsignaled" state after we acquire the next image
                    this->__relatedGPU.getVKLogicalDevice().resetFences(*this->__renderFinishedFences[this->__currentFrame]);
                    // 4. Reset and record command buffer
                    this->__commandBuffers[this->__currentFrame].reset();
                    if (const __Status recordStatus = this->__recordCommandBuffer(nextImage, this->__relatedSwapChain, this->__relatedPipelineHandler); recordStatus != __Status::E_OK) {
                        logger::error << "Failed to record command buffer for GPU " << this->__relatedGPU.getName() << std::endl;
                        return recordStatus;
                    }
                    // 5. Submit command buffer after recording it (NOTE: recording MAY not need to appen each frame)
                    // 5.1 Create submit info
                    vk::PipelineStageFlags waitStages(vk::PipelineStageFlagBits::eTopOfPipe);
                    vk::SubmitInfo submitInfo(
                        *this->__imageAvailableSemaphores[this->__currentFrame],
                        waitStages,
                        this->__commandBuffers[this->__currentFrame],
                        *this->__renderFinishedSemaphores[this->__currentFrame]
                    );
                    // 5.2 submit
                    this->__gpuGraphicsQueue.submit(submitInfo, this->__renderFinishedFences[this->__currentFrame]);
                    // 6. Presentation
                    vk::PresentInfoKHR presentInfo(*this->__renderFinishedSemaphores[this->__currentFrame], *this->__relatedSwapChain.getVKSwapChain(), nextImage);
                    // 7. Tell the swapchain we want to present an image to it (to the image reserved for presentation) using the present queue
                    if (const __Status presentStatus = this->__gpuPresentQueue.present(presentInfo); presentStatus != __Status::E_OK) {
                        logger::info << "Present queue is no longer compatible. Aborting draw cycle" << std::endl;
                        return presentStatus;
                    }
                    // 8. Advance to next frame
                    this->__currentFrame = (this->__currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
                    return __Status::E_OK;
                }

                void updateUponSurfaceChange(void) {
                    logger::trace << "\tPresenter destroying frame buffers" << std::endl;
                    this->__frameBuffers.clear();
                    logger::trace << "\tPresenter recreating frame buffers" << std::endl;
                    this->__frameBuffers = __createFrameBuffers(this->__relatedGPU, this->__relatedSwapChain, this->__relatedPipelineHandler);
                }

        };

        __Presenter::__Presenter(
            __GPU &gpu,
            __SwapChain &swapChain,
            const __PipelineHandler &pipelineHandler
        ) :
        __impl(std::make_unique<__Impl>(gpu, swapChain, pipelineHandler))
        {}

        __Presenter::~__Presenter() = default;

        __Status __Presenter::draw(void) { return this->__impl->draw(); }
        
        void __Presenter::updateUponSurfaceChange(void) { this->__impl->updateUponSurfaceChange(); }
    } // namespace __private
} // namespace renderer
