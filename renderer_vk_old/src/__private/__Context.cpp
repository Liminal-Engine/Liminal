/**
 * @file __Context.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-05
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__vkConfig.hpp"
#include "__private/__Context.hpp"
#include "__private/__GPU.hpp"
#include "__private/__errors.hpp"
#include "temp_consts_need_to_remove_this.hpp"

#include <logger/logger.hpp>

#include <parseop/parseop.hpp>


#include <sstream>
#include <cstring>


namespace renderer_vk_old {
    namespace __private {
        VkBool32 VKAPI_PTR __vulkanLogsCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
            void* pUserData
        ) {
            logger::Logger &selectedLogger = [&]() -> logger::Logger& {
                if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) return logger::error;
                if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) return logger::warn;
                if (messageSeverity & (VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)) return logger::trace; // Vulkan is so verbose we move both info and verbose into trace
                return logger::fatal;
            }();
            std::string messageTypesStr = [&]() -> std::string {
                std::stringstream ss;
                if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT) ss << "GENERAL - ";
                if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT) ss << "VALIDATION - ";
                if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT) ss << "PERFORMANCE - ";
                if (messageType & VK_DEBUG_UTILS_MESSAGE_TYPE_DEVICE_ADDRESS_BINDING_BIT_EXT) ss << "DEVICE ADRESS BINDING - ";
                std::string res = ss.str();
                if (res.empty()) return "UNKNOWN";
                return res.erase(res.size() - 3); // remove the last " - ";
            }();
            auto getLabels = [&](const VkDebugUtilsLabelEXT *labels, const uint32_t &count) -> std::string {
                if (!labels || count == 0) return "NO EXISTS";
                std::stringstream ss;
                for (uint32_t i = 0; i < count; i++) {
                    ss << labels[i].pLabelName;
                    if (i + 1 < count) ss << " - ";
                }
                return ss.str();
            };
            std::string objectNames = [&]() -> std::string {
                if (!pCallbackData->pObjects || pCallbackData->objectCount == 0) return "NO EXISTS";
                std::stringstream ss;
                for (uint32_t i = 0; i < pCallbackData->objectCount; i++) {
                    ss << pCallbackData->pObjects[i].pObjectName;
                    if (i + 1 < pCallbackData->objectCount) ss << " - ";
                }
                std::string res = ss.str();
                return res.empty() ? "NO EXISTS" : res;
            }();
            std::stringstream ss;
            ss << "[VULKAN] - [MESSAGE TYPES: " << messageTypesStr
            << "] - [MESSAGE ID NAME: " << pCallbackData->pMessageIdName
            << "] - [QUEUES LABELS: " << getLabels(pCallbackData->pQueueLabels, pCallbackData->queueLabelCount)
            << "] - [COMMANDS BUFFER LABELS: " << getLabels(pCallbackData->pCmdBufLabels, pCallbackData->cmdBufLabelCount)
            << "] - [OBJECTS NAMES: " << objectNames
            << "] - [USER DATA ADRESS: " << pUserData
            << "]\t> " << pCallbackData->pMessage;
            selectedLogger << ss.str() << std::endl;
            return VK_FALSE;
        }
    
        class __Context::_Impl {
            private:
                std::vector<std::string> __availableInstanceLayerNames;
                std::vector<std::string> __availableInstanceExtensionNames;
                vk::raii::Context __vkRAIIContext;
                vk::raii::Instance __instance;
                vk::DispatchLoaderDynamic __dynamicDispatchLoader;
                vk::raii::DebugUtilsMessengerEXT __messenger;
                vk::raii::SurfaceKHR __surface;
                __GPU __gpu;
                // __GPU __selectedGPU;

                // __GPU __GPU;

                static vk::ApplicationInfo __createVkApplicationInfo(void) {
                    logger::trace << "Creating Vulkan application info" << std::endl;
                    return vk::ApplicationInfo(
                        APPLICATION_NAME,
                        APPLICATION_VERSION,
                        ENGINE_NAME,
                        ENGINE_VERSION,
                        MIN_VULKAN_VERSION
                    );
                }

                static vk::raii::Instance __createInstanceHandler(
                    const vk::raii::Context &vkRAIIContext,
                    const std::vector<std::string> &availableInstanceLayerNames,
                    const std::vector<std::string> &availableInstanceExtensionNames
                ) {
                    if ( !parseop::containsAll(availableInstanceLayerNames, REQUIRED_INSTANCE_LAYER_NAMES) ) {
                        logger::fatal << "Required instance layers not available. Available instance layers are: \n" <<
                        parseop::prettify(availableInstanceLayerNames) << std::endl;
                        return vk::raii::Instance(nullptr);
                    }
                    if ( !parseop::containsAll(availableInstanceExtensionNames, REQUIRED_INSTANCE_EXTENSION_NAMES) ) {
                        logger::fatal << "Required instance extensions not available. Available instance extensions are: \n" <<
                        parseop::prettify(availableInstanceExtensionNames) << std::endl;
                        return vk::raii::Instance(nullptr);
                    }
                    vk::ApplicationInfo applicationInfo = __createVkApplicationInfo();
                    std::vector<const char *> instanceLayerNames(parseop::toCStrVector(REQUIRED_INSTANCE_LAYER_NAMES));
                    std::vector<const char *> instanceExtensionNames(parseop::toCStrVector(REQUIRED_INSTANCE_EXTENSION_NAMES));
                    logger::trace << "Creating Vulkan instance create info" << std::endl;
                    vk::InstanceCreateInfo instanceCreateInfo({}, &applicationInfo, instanceLayerNames, instanceExtensionNames);
                    vk::DebugUtilsMessengerCreateInfoEXT messenger = __createMessengerCreateInfo();
                    instanceCreateInfo.pNext = &messenger;                    
                    logger::trace << "Creating Vulkan instance" << std::endl;
                    auto [result, rawInstance] = vk::createInstance(instanceCreateInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(result, "Context failed to create VK Instance");
                        return vk::raii::Instance(nullptr);
                    }
                    return vk::raii::Instance(vkRAIIContext, rawInstance);
                }

                static vk::DebugUtilsMessengerCreateInfoEXT __createMessengerCreateInfo(void) {
                    logger::trace << "Creating Vulkan messenger create info" << std::endl;
                    return vk::DebugUtilsMessengerCreateInfoEXT(
                        {},
                        vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
                        vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
                        vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
                        vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose,
                        
                        vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
                        vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
                        vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
                        vk::DebugUtilsMessageTypeFlagBitsEXT::eDeviceAddressBinding,
                        __vulkanLogsCallback,
                        nullptr
                    );
                }

                static vk::raii::DebugUtilsMessengerEXT __createMessenger(const vk::raii::Instance &vkInstance, const vk::DispatchLoaderDynamic &dynamicDispatchLoader) {
                    logger::trace << "Creating instance messenger" << std::endl;
                    vk::DebugUtilsMessengerCreateInfoEXT createInfo = __createMessengerCreateInfo();                    
                    auto [result, rawMessenger] = (*vkInstance).createDebugUtilsMessengerEXT(createInfo, nullptr, dynamicDispatchLoader);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(result, "Contxt failed to create messenger");
                        return vk::raii::DebugUtilsMessengerEXT(nullptr);
                    }
                    return vk::raii::DebugUtilsMessengerEXT(vkInstance, rawMessenger);
                }

                static __GPU __setupGPU(const vk::raii::Instance &instance, const vk::raii::SurfaceKHR &surface) {
                    std::vector<__GPU> suitableGPUs(__GPU::listAvailableGPUs(instance, surface, true));
                    __GPU res = std::move(suitableGPUs.front());
                    logger::info << "Selected GPU: " << res.getName() << std::endl;
                    if (res.setup(surface) != __Status::E_OK) {
                        logger::error << "Failed to setup GPU " << res.getName() << std::endl;
                    }
                    return res;
                }

            public:
                _Impl(GLFWwindow *window) :
                __availableInstanceLayerNames(
                        []() {
                            logger::trace << "Loading available instance layers" << std::endl;
                            auto [result, availableInstanceLayers] = vk::enumerateInstanceLayerProperties();
                            if (result != vk::Result::eSuccess) {
                                __LOG_VK_CREATE_ERROR(result, "Context failed to enumerate available instance layers");
                                return std::vector<std::string>{};
                            }
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
                            logger::trace << "Loading available instance extensions" << std::endl;
                            auto [result, availableInstanceExtensions] = vk::enumerateInstanceExtensionProperties();
                            if (result != vk::Result::eSuccess) {
                                __LOG_VK_CREATE_ERROR(result, "Context failed to enumerate available instance extensions");
                                return std::vector<std::string>{};
                            }
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
                    __instance(
                        this->__createInstanceHandler(
                            this->__vkRAIIContext,
                            this->__availableInstanceLayerNames,
                            this->__availableInstanceExtensionNames
                        )
                    ),
                    __dynamicDispatchLoader(*this->__instance, vkGetInstanceProcAddr),
                    __messenger(__createMessenger(this->__instance, this->__dynamicDispatchLoader)),
                    __surface(
                        [&]() {
                            VkSurfaceKHR rawSurface;
                            // vk::raii::SurfaceKHR overload the * operator to return a VkInstance
                            if (glfwCreateWindowSurface(*this->__instance, window, nullptr, &rawSurface) != VK_SUCCESS) {
                                logger::fatal << "Failed to create surface from GLFW" << std::endl;
                                vk::raii::SurfaceKHR(nullptr);
                            }
                            logger::trace << "Creating Vulkan surface" << std::endl;
                            return vk::raii::SurfaceKHR(this->__instance, rawSurface);
                        }()
                    ),
                    __gpu(__setupGPU(this->__instance, this->__surface))
                    {
                    }

                    const vk::raii::Context& getVKRAIIContext(void) const { return this->__vkRAIIContext; }
                    const vk::raii::Instance& getVKInstance(void) const { return this->__instance; }
                    const vk::raii::SurfaceKHR& getVKSurface(void) const { return this->__surface; }
                    __GPU &getGPU(void) { return this->__gpu; }

        };


        __Context::__Context(GLFWwindow *window): _impl(std::make_unique<__Context::_Impl>(window)) {}
        __Context::~__Context() = default;

        const vk::raii::Context& __Context::getVKRAIIContext(void) const { return this->_impl->getVKRAIIContext(); }
        const vk::raii::Instance& __Context::getVKInstance(void) const { return this->_impl->getVKInstance(); };
        const vk::raii::SurfaceKHR& __Context::getVKSurface(void) const { return this->_impl->getVKSurface(); }
        __GPU &__Context::getGPU(void) { return this->_impl->getGPU(); }
    } // namespace __private
} // namespace renderer_vk_old
