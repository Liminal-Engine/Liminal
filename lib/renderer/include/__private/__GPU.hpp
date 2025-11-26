/**
 * @file __GPU.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-05
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__RENDERER__INCLUDE___PRIVATE__RENDERER__GPU_HPP__
#define __LIMINAL__RENDERER__INCLUDE___PRIVATE__RENDERER__GPU_HPP__

#include "__private/__Status.hpp"

#include <vulkan/vulkan_raii.hpp>

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <unordered_map>
#include <tuple>

namespace renderer {
    namespace __private {
        class __GPU {
            private:
                class __Impl;
            
            public:
                class __SurfaceSupport {
                    friend class __GPU; // surface support must only be created from the __GPU class
                    public:
                        ~__SurfaceSupport();
                        const vk::SurfaceCapabilitiesKHR &getCapabilitiles(void) const;
                        const std::vector<vk::SurfaceFormatKHR> &getFormats(void) const;
                        const std::vector<vk::PresentModeKHR> &getPresentModes(void) const;
                    private:
                        __SurfaceSupport(
                            const vk::raii::PhysicalDevice &vkGPU,
                            const vk::raii::SurfaceKHR &VKSurface
                        );

                        class __Impl;
                        std::unique_ptr<__Impl> __impl;

                };
            
            class __Queue {
                    friend class __GPU::__Impl;
                    public:
                        ~__Queue();
                        
                        __Queue(__Queue&&) noexcept;
                        __Queue& operator=(__Queue&&) noexcept;
                        __Queue(const __Queue&) = delete;
                        __Queue& operator=(const __Queue&) = delete;
                        
                        const std::string &getName(void) const;
                        const uint32_t &getIndex(void) const;
                        const uint32_t &getCount(void) const;
                        const std::vector<float> &getPriorities(void) const;
                        const vk::raii::Queue &getVKQueue(void) const;

                    private:
                        __Queue(
                            const vk::raii::Device &vkLogicalDevice,
                            const std::string &name,
                            const vk::DeviceQueueCreateInfo &createInfo
                        );
                        class __Impl;
                        std::unique_ptr<__Impl> __impl;
                };
                                                            // [name,                 index, priorities] // number of element in priorities will determine how much queue is created for the given index
                                                            
                using QueuesCreationMap_t = std::unordered_map<std::string, std::tuple<uint32_t, std::vector<float>>>;
                ~__GPU();
                __GPU(__GPU&&) noexcept;
                __GPU& operator=(__GPU&&) noexcept;
                __GPU(const __GPU&) = delete;
                __GPU& operator=(const __GPU&) = delete;
                
                static std::vector<__GPU> listAvailableGPUs(
                    const vk::raii::Instance &VKInstance,
                    const vk::raii::SurfaceKHR &VKSurface,
                    const bool &suitableOnly
                );

                const vk::raii::PhysicalDevice &getVKPhysicalDevice(void) const;
                const std::string &getName(void) const;
                const vk::PhysicalDeviceProperties &getProperties(void) const;
                const vk::PhysicalDeviceFeatures &getFeatures(void) const;
                const std::vector<std::string> &getExtensionNames(void) const;
                const __SurfaceSupport &getSurfaceSupport(void) const;
                const std::vector<vk::QueueFamilyProperties> &getQueueFamilies(void) const;
                const vk::raii::Device &getVKLogicalDevice(void) const;

                std::vector<uint32_t> getAvailableQueueFamilyIndicesSupportingFlags(const vk::QueueFlags &flags) const;
                std::vector<uint32_t> getAvailableQueueFamilyIndicesSupportingSurface(const vk::raii::SurfaceKHR &VKSurface) const;

                
                // The __GPU needs to have it's queue created before usage.
                // __Status registerQueue(const std::string &name, const uint32_t &index);
                // __Status removeQueue(const std::string &name);
                // std::optional<std::reference_wrapper<const __Queue>> &getQueue(const std::string &name) const;
                __Status create(const QueuesCreationMap_t &queuesCreationMap);
                std::optional<std::reference_wrapper<const __Queue>> getQueue(const std::string &name) const;
                std::vector<uint32_t> getQueuesIndicies(void) const;

            private:
                explicit __GPU(const vk::raii::PhysicalDevice &vkGPU, const vk::raii::SurfaceKHR &surface);
                std::unique_ptr<__Impl> __impl;
        };
    }
    
} // namespace renderer

#endif // __LIMINAL__RENDERER__INCLUDE___PRIVATE__RENDERER__GPU_HPP__

