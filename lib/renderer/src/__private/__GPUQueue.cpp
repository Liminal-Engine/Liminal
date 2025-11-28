/**
 * @file __GPUQueue.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-17
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__vkConfig.hpp"
#include "__private/__GPU.hpp"

#include <logger/logger.hpp>

namespace renderer {
    namespace __private {
        class __GPU::__Queue::__Impl {
            private:
                const std::string __name;
                const uint32_t __index;
                const uint32_t __count;
                const std::vector<float> __priorities;
                const vk::raii::Queue __VKQueue;
                vk::Result __status;

            public:
                __Impl(
                    const vk::raii::Device &vkLogicalDevice,
                    const std::string &name,
                    const vk::DeviceQueueCreateInfo &createInfo
                ) :
                __name([&]() {
                    logger::trace << "\t\tCreating Queue " << name << std::endl;
                    return name;
                }()),
                __index([&]() {
                    logger::trace << "\t\tIndex " << createInfo.queueFamilyIndex << std::endl;
                    return createInfo.queueFamilyIndex;
                }()),
                __count([&]() {
                    logger::trace << "\t\tCount: " << createInfo.queueCount << std::endl;
                    return createInfo.queueCount;
                }()),
                __priorities([&]() {
                    logger::trace << "\t\tPriorities:\n";
                    for (uint32_t i = 0; i < createInfo.queueCount; i++) {
                        logger::trace << "\t\t\t- " << createInfo.pQueuePriorities[i] << std::endl;
                    }
                    return std::vector<float>(createInfo.pQueuePriorities, createInfo.pQueuePriorities + createInfo.queueCount);
                }()),
                __VKQueue([&]() {
                    logger::trace << "\t\tCreating VK Queue for queue " << name << std::endl;
                    // This never returns a vk::Result even in non raii API because at this point, the queue is
                    // inevitably in the GPU
                    vk::Queue rawQueue = (*vkLogicalDevice).getQueue(createInfo.queueFamilyIndex, 0);
                    return vk::raii::Queue(vkLogicalDevice, rawQueue);
                }()),
                __status(vk::Result::eSuccess)
                {}

                const std::string &getName(void) const { return this->__name; }
                const uint32_t &getIndex(void) const { return this->__index; }
                const uint32_t &getCount(void) const { return this->__count; }
                const std::vector<float> &getPriorities(void) const { return this->__priorities; }
                const vk::raii::Queue &getVKQueue(void) const { return this->__VKQueue; }
                const vk::Result &getStatus(void) const { return this->__status; }

                void submit(const vk::SubmitInfo &submitInfo, const vk::raii::Fence &fence) {
                    this->__VKQueue.submit(submitInfo, *fence);
                }

                const vk::Result &present(const vk::PresentInfoKHR &presentInfo) {
                    return this->__status = this->__VKQueue.presentKHR(presentInfo);
                }

        };

        __GPU::__Queue::__Queue(
            const vk::raii::Device &vkLogicalDevice,
            const std::string &name,
            const vk::DeviceQueueCreateInfo &createInfo
        ) :
        __impl(std::make_unique<__GPU::__Queue::__Impl>(vkLogicalDevice, name, createInfo))
        {}

        __GPU::__Queue::~__Queue() = default;
        __GPU::__Queue::__Queue(__GPU::__Queue&&) noexcept = default;
        __GPU::__Queue& __GPU::__Queue::operator=(__GPU::__Queue&&) noexcept = default;

        const std::string &__GPU::__Queue::getName(void) const { return this->__impl->getName(); }
        const uint32_t &__GPU::__Queue::getIndex(void) const { return this->__impl->getIndex(); }
        const uint32_t &__GPU::__Queue::getCount(void) const { return this->__impl->getCount(); }
        const std::vector<float> &__GPU::__Queue::getPriorities(void) const { return this->__impl->getPriorities(); }
        const vk::raii::Queue &__GPU::__Queue::getVKQueue(void) const { return this->__impl->getVKQueue(); }
        const vk::Result &__GPU::__Queue::getStatus(void) const { return this->__impl->getStatus(); }
        
        void __GPU::__Queue::submit(const vk::SubmitInfo &submitInfo, const vk::raii::Fence &fence) { this->__impl->submit(submitInfo, fence); }
        const vk::Result &__GPU::__Queue::present(const vk::PresentInfoKHR &presentInfo) { return this->__impl->present(presentInfo); }
        
    } // namespace __private
} // namespace renderer
