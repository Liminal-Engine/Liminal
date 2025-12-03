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

#include "__private/__vkConfig.hpp"
#include "__private/__SwapChain.hpp"
#include "__private/__errors.hpp"

#include <logger/logger.hpp>

namespace renderer {
    namespace __private {
        class __SwapChain::__Impl {
            private:
                GLFWwindow *__relatedWindow;
                const vk::raii::SurfaceKHR &__relatedSurface;
                __GPU &__relatedGPU;

                __SwapChain::__Settings __settings;
                vk::raii::SwapchainKHR __VKSwapChain;
                std::vector<vk::Image> __images;
                std::vector<vk::raii::ImageView> __imageViews;

                static vk::SwapchainCreateInfoKHR __createVKSwapChainCreateInfo(const __Settings &settings, __GPU &gpu, const vk::raii::SurfaceKHR &surface) {
                    logger::trace << "Creating swap chain create info" << std::endl;
                    const __GPU::__SurfaceSupport &gpuSurfaceSupport = gpu.getSurfaceSupport();
                    vk::SurfaceCapabilitiesKHR gpuSurfaceCapabilities = gpuSurfaceSupport.getCapabilitiles();
                    const vk::SurfaceFormatKHR &swapChainSettingsSurfaceFormat = settings.getFormat();
                    uint32_t imageCount = gpuSurfaceCapabilities.maxImageCount > 0 && gpuSurfaceCapabilities.minImageCount + 1 > gpuSurfaceCapabilities.maxImageCount ?
                    gpuSurfaceCapabilities.maxImageCount :
                    gpuSurfaceCapabilities.minImageCount + 1;
                    std::set<uint32_t> queueIndicesSet = gpu.getQueueIndices();
                    std::vector<uint32_t> queueIndicesVec(queueIndicesSet.begin(), queueIndicesSet.end());
                    vk::SwapchainCreateInfoKHR res;
                    res.setFlags({})
                    .setSurface(*surface)
                    .setMinImageCount(imageCount)
                    .setImageFormat(swapChainSettingsSurfaceFormat.format)
                    .setImageColorSpace(swapChainSettingsSurfaceFormat.colorSpace)
                    .setImageExtent(settings.getExtent())
                    .setImageArrayLayers(1)
                    .setImageUsage(vk::ImageUsageFlagBits::eColorAttachment)
                    .setImageSharingMode(gpu.getGraphicsQueue().getFamilyIndex() == gpu.getGraphicsQueue().getFamilyIndex() ? vk::SharingMode::eExclusive : vk::SharingMode::eConcurrent)
                    .setQueueFamilyIndices(queueIndicesVec)
                    .setPreTransform(gpuSurfaceCapabilities.currentTransform)
                    .setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque)
                    .setPresentMode(settings.getPresentMode())
                    .setClipped(vk::True);
                    return res;
                }

                static vk::raii::SwapchainKHR __createVKSwapChain(
                    const __SwapChain::__Settings &settings,
                    __GPU &gpu,
                    const vk::raii::SurfaceKHR &surface
                ) {
                    vk::SwapchainCreateInfoKHR createInfo = __createVKSwapChainCreateInfo(settings, gpu, surface);
                    logger::trace << "SwapChain creating VK SwapChain" << std::endl;
                    auto [result, rawVKSwapChain] = gpu.getRawVKLogicalDevice().createSwapchainKHR(createInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "SwapChain failed to create VK SwapChain");
                        return vk::raii::SwapchainKHR(nullptr);
                    }
                    return vk::raii::SwapchainKHR(gpu.getVKLogicalDevice(), rawVKSwapChain);
                }

                static std::vector<vk::Image> __createImages(const vk::raii::SwapchainKHR &vkSwapChain) {
                    logger::trace << "Creating swap chain images" << std::endl;
                    return vkSwapChain.getImages();
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
                        auto [result, rawImageView] = gpu.getRawVKLogicalDevice().createImageView(imageViewCreateInfo);
                        if (result != vk::Result::eSuccess) {
                            __LOG_VK_CREATE_ERROR(gpu, result, "SwapChain failed to create an image view");
                            return std::vector<vk::raii::ImageView>{};
                        }
                        res.push_back(vk::raii::ImageView(gpu.getVKLogicalDevice(), rawImageView));
                    }
                    return res;
                }

            public:
                __Impl(GLFWwindow* window, const vk::raii::SurfaceKHR &surface, __GPU &gpu) :
                __relatedWindow(window),
                __relatedSurface(surface),
                __relatedGPU(gpu),
                __settings([&]() {
                    logger::trace << "Creating swap chain settings" << std::endl;
                    return __SwapChain::__Settings::createOptimal(this->__relatedGPU, this->__relatedWindow);
                }()),
                __VKSwapChain(__createVKSwapChain(this->__settings, this->__relatedGPU, this->__relatedSurface)),
                __images(__createImages(this->__VKSwapChain)),
                __imageViews(__createImageViews(this->__relatedGPU, this->__settings, this->__images))
                {
                }

                const __SwapChain::__Settings &getSettings(void) const { return this->__settings; }
                const std::vector<vk::raii::ImageView> &getImageViews(void) const { return this->__imageViews; }
                const vk::raii::SwapchainKHR &getVKSwapChain(void) const { return this->__VKSwapChain; }

                const std::pair<__Status, uint32_t> acquireNextImage(const vk::raii::Semaphore &semaphore, const uint64_t &timeout) {
                    auto [vkResult, nextImage] = this->__VKSwapChain.acquireNextImage(timeout, *semaphore);
                    if (vkResult == vk::Result::eSuccess) return std::make_pair(__Status::E_OK, nextImage);
                    /*
                    * This is not essentialy a serious error, it may be due to surface changes.
                    * However, it must be handled correctly.
                    */ 
                    
                    if (vkResult == vk::Result::eErrorOutOfDateKHR) {
                        logger::info << "VK swap chain is out of date" << std::endl;
                        return std::make_pair(__Status::E_SWAP_CHAIN_SUBOPTIMAL, nextImage);
                    }
                    else if (vkResult == vk::Result::eSuboptimalKHR) {
                        logger::info << "VK swap chain is suboptimal" << std::endl;
                        return std::make_pair(__Status::E_SWAP_CHAIN_OUT_OF_DATE, nextImage);
                    }
                    logger::error << "VK swap chain is in an unknown state: " << vk::to_string(vkResult)
                    << ". Undetermined behavior is expected" << std::endl;
                    return std::make_pair(__Status::E_VK_INTERNAL_ERROR, nextImage);
                    
                }

                void updateUponSurfaceChange(void) {
                    logger::trace << "\tSwapchain destroying image views" << std::endl;
                    this->__imageViews.clear();
                    logger::trace << "\tSwapchain destroying images" << std::endl;
                    this->__images.clear();
                    logger::trace << "\tSwapchain destroying VK SwapChain" << std::endl;
                    this->__VKSwapChain.clear();
                    logger::trace << "\tSwapchain recreating optimal settings" << std::endl;
                    this->__settings =__SwapChain::__Settings::createOptimal(this->__relatedGPU, this->__relatedWindow);
                    logger::trace << "\tSwapchain recreating VK SwapChain" << std::endl;
                    this->__VKSwapChain = __createVKSwapChain(this->__settings, this->__relatedGPU, this->__relatedSurface);
                    logger::trace << "\tSwapchain recreating images" << std::endl;
                    this->__images = __createImages(this->__VKSwapChain);
                    logger::trace << "\tSwapchain recreating image views" << std::endl;
                    this->__imageViews = __createImageViews(this->__relatedGPU, this->__settings, this->__images);
                }


        };

        __SwapChain::__SwapChain(GLFWwindow* window, const vk::raii::SurfaceKHR &surface, __GPU &gpu) : __impl(std::make_unique<__Impl>(window, surface, gpu)) {}
        __SwapChain::~__SwapChain() = default;

        const __SwapChain::__Settings &__SwapChain::getSettings(void) const { return this->__impl->getSettings(); }
        const std::vector<vk::raii::ImageView> &__SwapChain::getImageViews(void) const { return this->__impl->getImageViews(); }
        const vk::raii::SwapchainKHR &__SwapChain::getVKSwapChain(void) const { return this->__impl->getVKSwapChain(); }

        const std::pair<__Status, uint32_t>  __SwapChain::acquireNextimage(const vk::raii::Semaphore &semaphore, const uint64_t &timeout) { return this->__impl->acquireNextImage(semaphore, timeout); }

        void __SwapChain::updateUponSurfaceChange(void) { this->__impl->updateUponSurfaceChange(); }
    } // namespace __private

} // namespace renderer
