/**
 * @file __SwapChain.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-16
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__SwapChain.hpp"

#include <logger/logger.hpp>

namespace renderer {
    namespace __private {
        class __SwapChain::__Impl {
            private:

                __SwapChain::__Settings __settings;
                vk::raii::SwapchainKHR __VKSwapChain;
                std::vector<vk::Image> __images;
                std::vector<vk::raii::ImageView> __imageViews;

                static vk::SwapchainCreateInfoKHR __createVKSwapChainCreateInfo(const __Settings &settings, const __GPU &gpu, const vk::raii::SurfaceKHR &surface) {
                    logger::trace << "Creating swap chain create info" << std::endl;
                    const __GPU::__SurfaceSupport &gpuSurfaceSupport = gpu.getSurfaceSupport();
                    vk::SurfaceCapabilitiesKHR gpuSurfaceCapabilities = gpuSurfaceSupport.getCapabilitiles();
                    uint32_t imageCount = gpuSurfaceCapabilities.maxImageCount > 0 && gpuSurfaceCapabilities.minImageCount + 1 > gpuSurfaceCapabilities.maxImageCount ?
                    gpuSurfaceCapabilities.maxImageCount :
                    gpuSurfaceCapabilities.minImageCount + 1;
                    std::vector<uint32_t> queuesIndicies = gpu.getQueuesIndicies();
                    return vk::SwapchainCreateInfoKHR(
                        {},
                        *surface,
                        imageCount,
                        settings.getFormat().format,
                        settings.getFormat().colorSpace,
                        settings.getExtent(),
                        1,
                        vk::ImageUsageFlagBits::eColorAttachment,
                        gpu.getQueue("graphics_present").has_value() ? vk::SharingMode::eExclusive : vk::SharingMode::eConcurrent,
                        queuesIndicies,
                        gpuSurfaceCapabilities.currentTransform,
                        vk::CompositeAlphaFlagBitsKHR::eOpaque,
                        settings.getPresentMode(),
                        vk::True
                    );
                }

                static vk::raii::SwapchainKHR __createVKSwapChain(
                    const __SwapChain::__Settings &settings,
                    const __GPU &gpu,
                    const vk::raii::SurfaceKHR &surface
                ) {
                    vk::SwapchainCreateInfoKHR createInfo = __createVKSwapChainCreateInfo(settings, gpu, surface);
                    logger::trace << "Creating swap chain" << std::endl;
                    return gpu.getVKLogicalDevice().createSwapchainKHR(createInfo);
                }

                static std::vector<vk::raii::ImageView> __createImageViews(
                    const __GPU &gpu,
                    const __SwapChain::__Settings &settings,
                    const std::vector<vk::Image> &images

                ) {
                    logger::trace << "Creating swap chain image views" << std::endl;
                    std::vector<vk::raii::ImageView> res;
                    res.reserve(images.size());
                    vk::ComponentMapping componentMapping{};
                    vk::ImageSubresourceRange subresourceRange(
                        vk::ImageAspectFlagBits::eColor,
                        0,
                        1,
                        0,
                        1
                    );

                    for (const vk::Image &image : images) {
                        vk::ImageViewCreateInfo imageViewCreateInfo(
                            {},
                            image,
                            vk::ImageViewType::e2D,
                            settings.getFormat().format,
                            componentMapping,
                            subresourceRange
                        );
                        res.push_back(gpu.getVKLogicalDevice().createImageView(imageViewCreateInfo));
                    }
                    return res;
                }

            public:
                __Impl(GLFWwindow* window, const __GPU &gpu, const vk::raii::SurfaceKHR &surface) :
                __settings([&]() {
                    logger::trace << "Creating swap chain settings" << std::endl;
                    return __SwapChain::__Settings::createOptimal(gpu, window);
                }()),
                __VKSwapChain(__createVKSwapChain(this->__settings, gpu, surface)),
                __images([&]() {
                    logger::trace << "Creating swap chain images" << std::endl;
                    return this->__VKSwapChain.getImages();
                }()),
                __imageViews(__createImageViews(gpu, this->__settings, this->__images))        
                {
                }

                const __SwapChain::__Settings &getSettings(void) const { return this->__settings; }
                const std::vector<vk::raii::ImageView> &getImageViews(void) const { return this->__imageViews; }
                const vk::raii::SwapchainKHR &getVKSwapChain(void) const { return this->__VKSwapChain; }

        };

        __SwapChain::__SwapChain(GLFWwindow* window, const __GPU &gpu, const vk::raii::SurfaceKHR &surface) : __impl(std::make_unique<__Impl>(window, gpu, surface)) {}
        __SwapChain::~__SwapChain() = default;

        const __SwapChain::__Settings &__SwapChain::getSettings(void) const { return this->__impl->getSettings(); }
        const std::vector<vk::raii::ImageView> &__SwapChain::getImageViews(void) const { return this->__impl->getImageViews(); }
        const vk::raii::SwapchainKHR &__SwapChain::getVKSwapChain(void) const { return this->__impl->getVKSwapChain(); }
    } // namespace __private

} // namespace renderer
