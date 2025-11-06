/**
 * @file Context.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-05
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "Context.hpp"
#include "temp_consts_need_to_remove_this.hpp"

#include <logger/logger.hpp>
#include <parseop/parseop.hpp>

#include <sstream>
#include <cstring>

namespace renderer {
    
    class Context::_Impl {
        private:
            std::vector<std::string> __availableInstanceLayerNames;
            std::vector<std::string> __availableInstanceExtensionNames;
            vk::raii::Instance __instanceHandler;
            vk::raii::SurfaceKHR __surfaceHandler;
            // GPU __GPU;

            vk::ApplicationInfo __createVkApplicationInfo(void) {
                logger::debug << "Creating Vulkan application info" << std::endl;
                return vk::ApplicationInfo(
                    APPLICATION_NAME,
                    APPLICATION_VERSION,
                    ENGINE_NAME,
                    ENGINE_VERSION,
                    MIN_VULKAN_VERSION
                );
            }

            vk::raii::Instance __createInstanceHandler(const vk::raii::Context &vkRAIIContext) {
                if ( !parseop::containsAll(this->__availableInstanceLayerNames, REQUIRED_INSTANCE_LAYER_NAMES) ) {
                    logger::fatal << "Required instance layers not available. Available instance layers are: \n" <<
                    parseop::prettify(this->__availableInstanceLayerNames) << std::endl;
                    return vk::raii::Instance(nullptr);
                }
                if ( !parseop::containsAll(this->__availableInstanceExtensionNames, REQUIRED_INSTANCE_EXTENSION_NAMES) ) {
                    logger::fatal << "Required instance extensions not available. Available instance extensions are: \n" <<
                    parseop::prettify(this->__availableInstanceExtensionNames) << std::endl;
                    return vk::raii::Instance(nullptr);
                }
                vk::ApplicationInfo applicationInfo = __createVkApplicationInfo();
                std::vector<const char *> instanceLayerNames(parseop::toCStrVector(REQUIRED_INSTANCE_LAYER_NAMES));
                std::vector<const char *> instanceExtensionNames(parseop::toCStrVector(REQUIRED_INSTANCE_EXTENSION_NAMES));
                logger::debug << "Creating Vulkan instance create info" << std::endl;
                vk::InstanceCreateInfo instanceCreateInfo({}, &applicationInfo, instanceLayerNames, instanceExtensionNames);
                
                logger::debug << "Creating Vulkan instance" << std::endl;
                return vk::raii::Instance(vkRAIIContext, instanceCreateInfo);
            }

        public:
            _Impl(const vk::raii::Context &vkRAIIContext, GLFWwindow *window) :
            __availableInstanceLayerNames(
                    []() {
                        logger::debug << "Loading available instance layers" << std::endl;
                        std::vector<vk::LayerProperties> availableInstanceLayers(vk::enumerateInstanceLayerProperties());
                        std::vector<std::string> res(availableInstanceLayers.size());
                        std::transform(
                            availableInstanceLayers.begin(),
                            availableInstanceLayers.end(),
                            res.begin(),
                            [](const vk::LayerProperties &availableInstanceLayer) {
                                return std::string(availableInstanceLayer.layerName);
                            }
                        );
                        return res;
                    }()
                ),
                __availableInstanceExtensionNames(
                    []() {
                        logger::debug << "Loading available instance extensions" << std::endl;
                        std::vector<vk::ExtensionProperties> availableInstanceExtensions(vk::enumerateInstanceExtensionProperties());
                        std::vector<std::string> res(availableInstanceExtensions.size());
                        std::transform(
                            availableInstanceExtensions.begin(),
                            availableInstanceExtensions.end(),
                            res.begin(),
                            [](const vk::ExtensionProperties &availableInstanceExtension) {
                                return std::string(availableInstanceExtension.extensionName);
                            }
                        );
                        return res;
                    }()
                ),
                __instanceHandler(this->__createInstanceHandler(vkRAIIContext)),
                __surfaceHandler(
                    [&]() {
                        VkSurfaceKHR rawSurface;
                        // vk::raii::SurfaceKHR overload the * operator to return a VkInstance
                        if (glfwCreateWindowSurface(*this->__instanceHandler, window, nullptr, &rawSurface) != VK_SUCCESS) {
                            logger::fatal << "Failed to create surface from GLFW" << std::endl;
                            vk::raii::SurfaceKHR(nullptr);
                        }
                        logger::debug << "Creating Vulkan surface" << std::endl;
                        return vk::raii::SurfaceKHR(this->__instanceHandler, rawSurface);
                    }()
                )
                {

                }
    };


    Context::Context(const vk::raii::Context &vkRAIIContext, GLFWwindow *window): _impl(std::make_unique<Context::_Impl>(vkRAIIContext, window)) {}
    Context::~Context() = default;
    
} // namespace renderer
