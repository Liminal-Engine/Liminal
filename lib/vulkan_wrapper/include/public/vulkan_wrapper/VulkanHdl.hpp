#ifndef VULKAN_HDL_LIB_VULKANHDL_HPP
#define VULKAN_HDL_LIB_VULKANHDL_HPP

/**
 * @file VulkanHdl.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/


#include "liminal_windowing/WindowWrapper.hpp"

#include <vulkan/vulkan.h>

#include <string>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <memory>

// Forward declarations :
namespace vulkan_wrapper {
    namespace _queue {
        using  _QueueHandlers_t = std::unordered_map<std::string, VkQueue>; ///< _QueueHandlers_t type = queue handlers for a specific device
        struct _QueueFamilies;
    }
    namespace _swap_chain {
        struct _Supports;
    }
    namespace _layer {
        using _Layers_t = std::vector<const char *>;
    }
    namespace _extension {
        using _Extensions_t = std::unordered_map<std::string, std::vector<const char *>>;
    }
}

namespace vulkan_wrapper {

    /**
     * @brief Handler for the Vulkan instance of the applcation
     * 
    */

    class VulkanHdl {

        private:
            const std::string _appName; ///< Name of the application
            const std::string _engineName; ///< Name of the engine
            _layer::_Layers_t _layers; ///< Vulkan optional additional layers

        public:
            /**
             * @brief Default constructor
            */
            VulkanHdl(void);
            ~VulkanHdl();

            void drawFrame(void);
            void waitIdle(void) const;

            window_wrapper::WindowWrapper window; ///< The window related to the vulkan instace. This will be taken out later in a separate lib

        private:
            _extension::_Extensions_t _extensions; ///< Vulkan compatible required extensions for the app to work
            VkInstance _instance; ///< The Vulkan instance
            VkSurfaceKHR _surface; ///< A surface is an interface between Vulkan and the windowing system
            VkPhysicalDevice _physicalDevice; ///< The choosen physical device
            std::unique_ptr<_swap_chain::_Supports> _swapChainSupports; ///< swap chain supported features for the related physical device
            std::unique_ptr<_queue::_QueueFamilies> _queueFamilies; ///< The physical device queue families
            VkDevice _logicalDevice; ///< Interface between Vulkan and a physical device
            _queue::_QueueHandlers_t _queueHandlers; ///< Queue handlers as specified in the config file
            VkSurfaceFormatKHR _swapChainImageFormat; ///< The swap chain images format
            VkExtent2D _swapChainExtent; ///< The swap chain images extent
            VkSwapchainKHR _swapChain; ///< The swap chain (e.g.) basically the queue for the images to draw
            std::vector<VkImage> _swapChainImagesHandlers; ///< Handlers of the swap chain images each in the form of a VkImage
            std::vector<VkImageView> _swapChainImagesViewsHandlers; ///< A handler of a "view" into an image. Views are required to access images. It describes how ot access it and which par of the image to access
            VkRenderPass _renderPass; ///< Describes various infos about rendering operations in a coherant set (attachlents, subpasses, depandencies, etc...) 
            VkPipelineLayout _pipelineLayout; ///< Describes tje set of ressources that can be accessible by a related pipeline
            VkPipeline _graphicsPipeline; ///< Describe the graphics pipeline
            std::vector<VkFramebuffer> _frameBuffers; ///< Ties the VkImages for a particular rendering operation e.g. collection of image attachments and the memory association between them.
            VkCommandPool _commandPool; ///< The commadn pool will manage allocation and memory of the commandBuffer;
            VkCommandBuffer _commandBuffer; ///< Buffer when we will store the commands to send to the SDK
            VkSemaphore _imageAvailableSemaphore; ///< Semaphore is to communicate with the GPU. Uses for GPU synchronization            VkSemaphore _renderFinishedSemaphore;
            VkSemaphore _renderFinishedSemaphore;
            VkFence _inFlightFence; ///< Fence is used for GPU-CPU synchronization.

            void _recordCommandBuffer(const VkCommandBuffer &commandBuffer, const uint32_t &image_index);
    };
}

#endif // VULKAN_HDL_LIB_VULKANHDL_HPP
