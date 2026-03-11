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

namespace renderer_vk_old {
    namespace __private {
        class __GPU::__Queue::__Impl {
            private:
                const std::string __name;
                const uint32_t __familyIndex;
                const uint32_t __count;
                const vk::raii::Queue __VKQueue;

            public:
                __Impl(
                    const vk::raii::Device &vkLogicalDevice,
                    const std::string &name,
                    const uint32_t &familyIndex
                ) :
                __name([&]() {
                    logger::trace << "\t\tCreating Queue " << name << std::endl;
                    return name;
                }()),
                __familyIndex([&]() {
                    logger::trace << "\t\tIndex " << familyIndex << std::endl;
                    return familyIndex;
                }()),
                __count([&]() {
                    logger::trace << "\t\tCount: " << 1 << std::endl;
                    return 1;
                }()),
                __VKQueue([&]() {
                    logger::trace << "\t\tCreating VK Queue for queue " << name << std::endl;
                    // This never returns a vk::Result even in non raii API because at this point, the queue is
                    // inevitably in the GPU
                    vk::Queue rawQueue = (*vkLogicalDevice).getQueue(familyIndex, 0);
                    return vk::raii::Queue(vkLogicalDevice, rawQueue);

                }())
                {}

                const std::string &getName(void) const { return this->__name; }
                const uint32_t &getFamilyIndex(void) const { return this->__familyIndex; }
                const uint32_t &getCount(void) const { return this->__count; }
                const vk::raii::Queue &getVKQueue(void) const { return this->__VKQueue; }

                void submit(const vk::SubmitInfo &submitInfo, const vk::raii::Fence &fence) const {
                    this->__VKQueue.submit(submitInfo, *fence);
                }

                __Status present(const vk::PresentInfoKHR &presentInfo) const {
                    vk::Result vkPresentResult = this->__VKQueue.presentKHR(presentInfo);
                    if (vkPresentResult == vk::Result::eSuccess) return __Status::E_OK;
                    /**
                     * This is not essentialy a serious error. However, it must be handled correctly
                    **/
                    if (vkPresentResult == vk::Result::eErrorOutOfDateKHR) {
                        logger::info << "Present queue is out of date" << std::endl;
                        return __Status::E_PRESENT_QUEUE_OUT_OF_DATE;
                    }
                    if (vkPresentResult == vk::Result::eSuboptimalKHR) {
                        logger::info << "Present queue is suboptimal" << std::endl;
                        return __Status::E_PRESENT_QUEUE_SUBOPTIMAL;
                    }
                    logger::error << "Present queue is in an unknown state: " << vk::to_string(vkPresentResult)
                    << ". Undetermined behavior is expected" << std::endl;
                    return __Status::E_VK_INTERNAL_ERROR;
                }

        };

        __GPU::__Queue::__Queue(
            const vk::raii::Device &vkLogicalDevice,
            const std::string &name,
            const uint32_t &familyIndex
        ) :
        __impl(std::make_unique<__GPU::__Queue::__Impl>(vkLogicalDevice, name, familyIndex))
        {}

        __GPU::__Queue::__Queue(void) : __impl(nullptr) {}

        __GPU::__Queue::~__Queue() = default;
        __GPU::__Queue::__Queue(__GPU::__Queue&&) noexcept = default;
        __GPU::__Queue& __GPU::__Queue::operator=(__GPU::__Queue&&) noexcept = default;

        const std::string &__GPU::__Queue::getName(void) const { return this->__impl->getName(); }
        const uint32_t &__GPU::__Queue::getFamilyIndex(void) const { return this->__impl->getFamilyIndex(); }
        const uint32_t &__GPU::__Queue::getCount(void) const { return this->__impl->getCount(); }
        const vk::raii::Queue &__GPU::__Queue::getVKQueue(void) const { return this->__impl->getVKQueue(); }
        
        void __GPU::__Queue::submit(const vk::SubmitInfo &submitInfo, const vk::raii::Fence &fence) const { this->__impl->submit(submitInfo, fence); }
        __Status __GPU::__Queue::present(const vk::PresentInfoKHR &presentInfo) const { return this->__impl->present(presentInfo); }
        
    } // namespace __private
} // namespace renderer_vk_old
