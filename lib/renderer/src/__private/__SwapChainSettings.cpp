/**
 * @file __SwapChainSettings.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-17
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__SwapChain.hpp"

namespace renderer {
    namespace __private {
        class __SwapChain::__Settings::__Impl {
            private:
                vk::SurfaceFormatKHR __format;
                vk::PresentModeKHR __presentMode;
                vk::Extent2D __extent;

            public:
                __Impl(
                    const vk::SurfaceFormatKHR &format,
                    const vk::PresentModeKHR &presentMode,
                    const vk::Extent2D &extent
                ) :
                __format(format),
                __presentMode(presentMode),
                __extent(extent)
                {}
                
                static __SwapChain::__Settings createOptimal(const __GPU &gpu, GLFWwindow *window) {
                    const __GPU::__SurfaceSupport &gpuSurfaceSupport = gpu.getSurfaceSupport();
                    const vk::SurfaceCapabilitiesKHR &gpuSurfaceCapabilities = gpuSurfaceSupport.getCapabilitiles();
                    const std::vector<vk::SurfaceFormatKHR> &gpuFormats = gpuSurfaceSupport.getFormats();
                    const std::vector<vk::PresentModeKHR> &gpuPresentModes = gpuSurfaceSupport.getPresentModes();
                    // 1. Surface format
                    // 1.1 Default initialize
                    vk::SurfaceFormatKHR bestSurfaceFormat = gpuSurfaceSupport.getFormats()[0];
                    // 1.2 Finding
                    for (const vk::SurfaceFormatKHR &format : gpuFormats) {
                        if (format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                            bestSurfaceFormat = format;
                        }
                    }
                    // 2. Present mode
                    // 2.1 Default initialize
                    vk::PresentModeKHR bestPresentMode = gpuPresentModes[0];
                    // 2.2 Finding
                    for (const vk::PresentModeKHR &presentMode : gpuPresentModes) {
                        if (presentMode == vk::PresentModeKHR::eMailbox) bestPresentMode = presentMode;
                    }
                    // 3. Extent
                    // 3.1 Default initialize
                    vk::Extent2D bestExtent(gpuSurfaceCapabilities.currentExtent);
                    // 3.2 Finding
                    int width = 0;
                    int height = 0;
                    glfwGetFramebufferSize(window, &width, &height);
                    bestExtent.setWidth(std::clamp(static_cast<uint32_t>(width), gpuSurfaceCapabilities.minImageExtent.width, gpuSurfaceCapabilities.maxImageExtent.width));
                    bestExtent.setHeight(std::clamp(static_cast<uint32_t>(height), gpuSurfaceCapabilities.minImageExtent.height, gpuSurfaceCapabilities.maxImageExtent.height));
                    return __Settings(bestSurfaceFormat, bestPresentMode, bestExtent);
                }

                const vk::SurfaceFormatKHR &getFormat(void) const { return this->__format; }
                const vk::PresentModeKHR &getPresentMode(void) const { return this->__presentMode; }
                const vk::Extent2D &getExtent(void) const { return this->__extent; }

                __Status setFormat(const vk::SurfaceFormatKHR &format) {
                    this->__format = format;
                    return __Status::__E_OK;
                }

                __Status setPresentMode(const vk::PresentModeKHR &presentMode) {
                    this->__presentMode = presentMode;
                    return __Status::__E_OK;
                }

                __Status setExtent(const vk::Extent2D &extent) {
                    this->__extent = extent;
                    return __Status::__E_OK;
                }
        };


        __SwapChain::__Settings::__Settings(
            const vk::SurfaceFormatKHR &format,
            const vk::PresentModeKHR &presentMode,
            const vk::Extent2D &extent
        ) :
        __impl(std::make_unique<__SwapChain::__Settings::__Impl>(format, presentMode, extent))
        {}

        __SwapChain::__Settings::~__Settings() = default;
        __SwapChain::__Settings::__Settings(__SwapChain::__Settings&&) noexcept = default;
        __SwapChain::__Settings& __SwapChain::__Settings::operator=(__SwapChain::__Settings&&) noexcept = default;

        __SwapChain::__Settings __SwapChain::__Settings::createOptimal(const __GPU &gpu, GLFWwindow *window) { return __SwapChain::__Settings::__Impl::createOptimal(gpu, window); }

        const vk::SurfaceFormatKHR &__SwapChain::__Settings::getFormat(void) const { return this->__impl->getFormat(); }
        const vk::PresentModeKHR &__SwapChain::__Settings::getPresentMode(void) const { return this->__impl->getPresentMode(); }
        const vk::Extent2D &__SwapChain::__Settings::getExtent(void) const { return this->__impl->getExtent(); }

        __Status __SwapChain::__Settings::setFormat(const vk::SurfaceFormatKHR &format) { return this->__impl->setFormat(format); }
        __Status __SwapChain::__Settings::setPresentMode(const vk::PresentModeKHR &presentMode) { return this->__impl->setPresentMode(presentMode); }
        __Status __SwapChain::__Settings::setExtent(const vk::Extent2D &extent) { return this->__impl->setExtent(extent); }
    } // namespace __private
} // namespace renderer
