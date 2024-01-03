/**
 * @file VulkanHdl.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/
#include "_private/_swap_chain/_Supports.hpp"

#include "_private/_layer/_Layer_t.hpp"
#include "_private/_extension/_Extensions_t.hpp"
#include "_private/_instance/_VkInstance_wrappers.hpp"
#include "_private/_surface/_VkSurfaceKHR_wrappers.hpp"
#include "_private/_device/_physical/_VkPhysicalDevice_wrappers.hpp"
#include "_private/_queue/_QueueFamilies.hpp"
#include "_private/_device/_logical/_VkDevice_wrappers.hpp"
#include "_private/_swap_chain/_optimal_settings.hpp"
#include "_private/_swap_chain/_Supports.hpp"
#include "_private/_swap_chain/_VkSwapChainKHR_wrappers.hpp"
#include "_private/_swap_chain/_image/_VkImage_wrappers.hpp"
#include "_private/_swap_chain/_image_view/_VkImageView_wrappers.hpp"
#include "_private/_render_pass/_VKRenderPass_wrappers.hpp"
#include "_private/_pipeline/_layout/_VkPipelineLayout_wrappers.hpp"
#include "_private/_pipeline/_VkPipeline_wrappers.hpp"
#include "_private/_frame_buffer/_VkFrameBuffer_wrappers.hpp"
#include "_private/_command/_pool/_VkCommandPool_wrappers.hpp"
#include "_private/_command/_buffer/_VkCommandBuffer_wrappers.hpp"
#include "_private/_semaphore/_VkSemaphore_wrappers.hpp"
#include "_private/_fence/_VkFence_wrappers.hpp"

#include "VulkanHdl.hpp"

#include <vector>
#include <string>
#include <string.h>
#include <stdexcept>

namespace vulkan_wrapper {
   
    VulkanHdl::VulkanHdl(void) :
    _appName{"Liminal Engine"},
    _engineName{"Liminal Engine"},
    _layers{_layer::_load()},    
    window{window_wrapper::WindowWrapper(this->_appName)},
    _extensions{_extension::_load()},
    _instance{_instance::_load(this->_appName, this->_engineName, this->_layers, this->_extensions)},
    _surface{_surface::_load(this->_instance, this->window)},
    _physicalDevice{_device::_physical::_pick(this->_instance, this->_surface, this->_extensions.at("device"))},
    _swapChainSupports{ std::make_unique<_swap_chain::_Supports>(_swap_chain::_getSupports(this->_physicalDevice, this->_surface)) },
    _queueFamilies{ std::make_unique<_queue::_QueueFamilies>(_queue::_load(this->_physicalDevice, this->_surface) ) },
    _logicalDevice{_device::_logical::_load(this->_physicalDevice, this->_queueFamilies.get()->_toSet(), this->_extensions.at("device"), this->_layers)},
    _queueHandlers{_queue::_load(this->_logicalDevice, *this->_queueFamilies.get())},
    _swapChainImageFormat{_swap_chain::_getBestSurfaceFormat(this->_swapChainSupports.get()->_surfaceFormats)},
    _swapChainExtent{_swap_chain::_getBestExtent(this->window, this->_swapChainSupports.get()->_surfaceCapabilities)},
    _swapChain{_swap_chain::_load(this->_logicalDevice, this->_surface, *this->_swapChainSupports.get(), *this->_queueFamilies.get(), this->_swapChainImageFormat, this->_swapChainExtent)},
    _swapChainImagesHandlers{_swap_chain::_image::_load(this->_logicalDevice, this->_swapChain)},
    _swapChainImagesViewsHandlers{_swap_chain::_image_view::_load(this->_logicalDevice, this->_swapChainImagesHandlers, this->_swapChainImageFormat.format)},
    _renderPass{_render_pass::_load(this->_logicalDevice, this->_swapChainImageFormat.format)},
    _pipelineLayout{_pipeline::_layout::_load(this->_logicalDevice)},
    _graphicsPipeline{_pipeline::_load(this->_logicalDevice, this->_swapChainExtent, this->_pipelineLayout, this->_renderPass)},
    _frameBuffers{_frame_buffer::_load(this->_logicalDevice, this->_swapChainImagesViewsHandlers, this->_swapChainExtent, this->_renderPass)},
    _commandPool{_command::_pool::_load(this->_logicalDevice, *this->_queueFamilies.get())},
    _commandBuffer{_command::_buffer::_load(this->_logicalDevice, this->_commandPool)},
    _imageAvailableSemaphore{_semaphore::_load(this->_logicalDevice)},
    _renderFinishedSemaphore{_semaphore::_load(this->_logicalDevice)},
    _inFlightFence{_fence::_load(this->_logicalDevice)}
    {

    }
    
    VulkanHdl::~VulkanHdl() {
        _semaphore::_destroy(this->_logicalDevice, this->_imageAvailableSemaphore, nullptr);
        _semaphore::_destroy(this->_logicalDevice, this->_renderFinishedSemaphore, nullptr);
        _fence::_destroy(this->_logicalDevice, this->_inFlightFence, nullptr);
        _command::_pool::_destroy(this->_logicalDevice, this->_commandPool, nullptr);
        _frame_buffer::_destroy(this->_logicalDevice, this->_frameBuffers, nullptr);
        _pipeline::_destroy(this->_logicalDevice, this->_graphicsPipeline, nullptr);
        _pipeline::_layout::_destroy(this->_logicalDevice, this->_pipelineLayout, nullptr);
        _render_pass::_destroy(this->_logicalDevice, this->_renderPass, nullptr);
        _swap_chain::_image_view::_destroy(this->_logicalDevice, this->_swapChainImagesViewsHandlers, nullptr);
        _swap_chain::_destroy(this->_logicalDevice, this->_swapChain, nullptr);
        _device::_logical::_destroy(this->_logicalDevice, nullptr);
        _surface::_destroy(this->_instance, this->_surface, nullptr);
        _instance::_destroy(this->_instance, nullptr);
    }

    void VulkanHdl::drawFrame(void) {
        vkWaitForFences(this->_logicalDevice, 1, &this->_inFlightFence, VK_TRUE, UINT64_MAX);
        vkResetFences(this->_logicalDevice, 1, &this->_inFlightFence);
        uint32_t imageIndex;
        vkAcquireNextImageKHR(
            this->_logicalDevice,
            this->_swapChain,
            UINT64_MAX, //Timeout, in this case no timeout
            this->_imageAvailableSemaphore, //Sync objects that are to be signlaed when the presentation engine is finished using the image
            VK_NULL_HANDLE, //Sync objects that are to be signlaed when the presentation engine is finished using the image
            &imageIndex //Variable to store the index of the swap chain image that has become available. It refers to the vkImage in our this->_swapChainImages array. We will use this index to pick the vkFrameBuffer
        );
        vkResetCommandBuffer(this->_commandBuffer, 0);
        this->_recordCommandBuffer(this->_commandBuffer, imageIndex);
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        VkSemaphore vkWaitSemaphores[] = {this->_imageAvailableSemaphore};
        VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = vkWaitSemaphores; //Which sempahores to wait on before execution begins
        submitInfo.pWaitDstStageMask = waitStages; // Which stage(s) of the pipeline to wait before execution begins
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &this->_commandBuffer;
        VkSemaphore signalSemaphores[] = {this->_renderFinishedSemaphore};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;
        if ( vkQueueSubmit(this->_queueHandlers["graphics"], 1, &submitInfo, this->_inFlightFence) != VK_SUCCESS ) {//The fence here is optional
            throw std::runtime_error("Failed to submit draw command buffer");
        }
        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        VkSwapchainKHR swapChains[] = {this->_swapChain};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;//The one we retrieved from the call to "vkAcquireNextImageKHR"
        presentInfo.pResults = nullptr; //Optional : allows you to specify an array of VkResult values to check for every individual swap chain if presentation was successful
        vkQueuePresentKHR(this->_queueHandlers["presentation"], &presentInfo);
    }

    void VulkanHdl::waitIdle(void) const {
        vkDeviceWaitIdle(this->_logicalDevice);
    }

    void VulkanHdl::_recordCommandBuffer(const VkCommandBuffer &commandBuffer, const uint32_t &image_index) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0; //Optional
        beginInfo.pInheritanceInfo = nullptr; //Optional
        if ( vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS ) {
            throw std::runtime_error("Failed to begin recording a command buffer");
        }
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = this->_renderPass; //bind render pass
        renderPassInfo.framebuffer = this->_frameBuffers[image_index]; //bind frame buffer
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = this->_swapChainExtent;
        VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f }}};
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;
        
        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->_graphicsPipeline);
        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = static_cast<float>(this->_swapChainExtent.width);
        viewport.height = static_cast<float>(this->_swapChainExtent.height);
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = {0, 0};
        scissor.extent = this->_swapChainExtent;
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
        vkCmdDraw(commandBuffer, 3, 1, 0, 0);
        vkCmdEndRenderPass(commandBuffer);
        if ( vkEndCommandBuffer(commandBuffer) != VK_SUCCESS ) {
            throw std::runtime_error("Failed to end command buffer recording");
        }
    }

}