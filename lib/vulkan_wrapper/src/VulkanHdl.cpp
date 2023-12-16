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

#include "VulkanHdl.hpp"

#include "_instance/_VkInstance_wrappers.hpp"
#include "_surface/_VkSurfaceKHR_wrappers.hpp"
#include "_device/_physical/_VkPhysicalDevice_wrappers.hpp"
#include "_swap_chain/_Supports.hpp"
#include "_queue/_QueueFamilies.hpp"
#include "_device/_logical/_VkDevice_wrappers.hpp"
#include "_swap_chain/_optimal_settings.hpp"
#include "_swap_chain/_Supports.hpp"
#include "_swap_chain/_VkSwapChainKHR_wrappers.hpp"
#include "_swap_chain/_image/_VkImage_wrappers.hpp"
#include "_swap_chain/_image_view/_VkImageView_wrappers.hpp"
#include "_render_pass/_VKRenderPass_wrappers.hpp"
#include "_pipeline/_layout/_VkPipelineLayout_wrappers.hpp"
#include "_pipeline/_VkPipeline_wrappers.hpp"
#include "_frame_buffer/_VkFrameBuffer_wrappers.hpp"
#include "_command/_pool/_VkCommandPool_wrappers.hpp"
#include "_command/_buffer/_VkCommandBuffer_wrappers.hpp"
#include "_semaphore/_VkSemaphore_wrappers.hpp"
#include "_fence/_VkFence_wrappers.hpp"

#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <string.h>

const std::vector<const char*> VALIDATION_LAYERS = {
    "VK_LAYER_KHRONOS_validation"
};

GLFWwindow *TMP_GET_WINDOW(const std::string &app_name) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Explicelty tells GFLW to NOT use OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //Disable resize because wi will need to handle it later

    return glfwCreateWindow(800, 600, app_name.c_str(), nullptr, nullptr);
}

void TMP_DESTORY_WINDOW(GLFWwindow *window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}
const std::vector<const char *> DEVICE_EXTENSIONS = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

namespace vulkan_wrapper {

    bool TMP_checkValidationLayerSupport() {
        //1. List avialable validation layers
        uint32_t layerCount = 0;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        for (const char *layerName : VALIDATION_LAYERS) { //2. loop through wanted layers
            bool found = false;
            for (const auto &layerProperties : availableLayers) {//3. loop through available layers
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    found = true;
                    break;
                }
            }
            if (found == false) {
                return false;
            }
        }
        return true;
    }
        
    VulkanHdl::VulkanHdl(void) :
    _TMP{TMP_checkValidationLayerSupport()},
    _appName{"Vulkan Best Tutorial"},
    _engineName{"Liminal Engine"},
    _window{TMP_GET_WINDOW("Vulkan App")},
    _instance{_instance::_load(this->_appName, this->_engineName)},
    _surface{_surface::_load(this->_instance, this->_window)},
    _physicalDevice{_device::_physical::_pick(this->_instance, this->_surface, std::vector<const char *>())},
    _swapChainSupports{_swap_chain::_getSupports(this->_physicalDevice, this->_surface)},
    _queueFamilies{_queue::_load(this->_physicalDevice, this->_surface)},
    _logicalDevice{_device::_logical::_load(this->_physicalDevice, this->_surface, this->_queueFamilies._toSet(), DEVICE_EXTENSIONS)},
    _queueHandlers{_queue::_load(this->_logicalDevice, this->_queueFamilies)},
    _swapChainImageFormat{_swap_chain::_getBestSurfaceFormat(this->_swapChainSupports._surfaceFormats)},
    _swapChainExtent{_swap_chain::_getBestExtent(this->_window, this->_swapChainSupports._surfaceCapabilities)},
    _swapChain{_swap_chain::_load(this->_logicalDevice, this->_window, this->_surface, this->_swapChainSupports, this->_queueFamilies, this->_swapChainImageFormat, this->_swapChainExtent)},
    _swapChainImagesHandlers{_swap_chain::_image::_load(this->_logicalDevice, this->_swapChain)},
    _swapChainImagesViewsHandlers{_swap_chain::_image_view::_load(this->_logicalDevice, this->_swapChainImagesHandlers, this->_swapChainImageFormat.format)},
    _renderPass{_render_pass::_load(this->_logicalDevice, this->_swapChainImageFormat.format)},
    _pipelineLayout{_pipeline::_layout::_load(this->_logicalDevice)},
    _graphicsPipeline{_pipeline::_load(this->_logicalDevice, this->_swapChainExtent, this->_pipelineLayout, this->_renderPass)},
    _frameBuffers{_frame_buffer::_load(this->_logicalDevice, this->_swapChainImagesViewsHandlers, this->_swapChainExtent, this->_renderPass)},
    _commandPool{_command::_pool::_load(this->_logicalDevice, this->_queueFamilies)},
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
        TMP_DESTORY_WINDOW(this->_window);
    }
}