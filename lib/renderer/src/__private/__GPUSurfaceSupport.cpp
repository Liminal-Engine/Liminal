/**
 * @file __GPU::__SurfaceSupport.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-11
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__vkConfig.hpp"
#include "__private/__GPU.hpp"

#include <logger/logger.hpp>

namespace renderer {
    namespace __private {
        class __GPU::__SurfaceSupport::__Impl {
            private:
                const vk::SurfaceCapabilitiesKHR __capabilities;
                const std::vector<vk::SurfaceFormatKHR> __formats;
                const std::vector<vk::PresentModeKHR> __presentModes;

            public:
                __Impl(
                    const vk::raii::PhysicalDevice &vkGPU,
                    const vk::raii::SurfaceKHR &VKSurface
                ) :
                __capabilities([&](){
                    logger::trace << "\t\tLoading surface support: loading capabilities for GPU "
                    << static_cast<const char*>(vkGPU.getProperties().deviceName.data()) << std::endl;
                    return vkGPU.getSurfaceCapabilitiesKHR(*VKSurface);
                }()),
                __formats([&](){
                    logger::trace << "\t\tLoading surface support: loading formats for GPU "
                    << static_cast<const char*>(vkGPU.getProperties().deviceName.data()) << std::endl;
                    return vkGPU.getSurfaceFormatsKHR(*VKSurface);
                }()),
                __presentModes([&](){
                    logger::trace << "\t\tLoading surface support: loading present modes for GPU "
                    << static_cast<const char*>(vkGPU.getProperties().deviceName.data()) << std::endl;
                    return vkGPU.getSurfacePresentModesKHR(*VKSurface);
                }())
                {}

                const vk::SurfaceCapabilitiesKHR &getCapabilitiles(void) const { return this->__capabilities; }
                const std::vector<vk::SurfaceFormatKHR> &getFormats(void) const { return this->__formats; }
                const std::vector<vk::PresentModeKHR> &getPresentModes(void) const { return this->__presentModes; }
        };

        __GPU::__SurfaceSupport::__SurfaceSupport(
            const vk::raii::PhysicalDevice &vkGPU,
            const vk::raii::SurfaceKHR &VKSurface
        ) :
        __impl(std::make_unique<__GPU::__SurfaceSupport::__Impl>(vkGPU, VKSurface))
        {
        }

        __GPU::__SurfaceSupport::~__SurfaceSupport() = default;


        const vk::SurfaceCapabilitiesKHR &__GPU::__SurfaceSupport::getCapabilitiles(void) const { return this->__impl->getCapabilitiles(); }
        const std::vector<vk::SurfaceFormatKHR> &__GPU::__SurfaceSupport::getFormats(void) const { return this->__impl->getFormats(); }
        const std::vector<vk::PresentModeKHR> &__GPU::__SurfaceSupport::getPresentModes(void) const { return this->__impl->getPresentModes(); }
    } // namespace __private
} // namespace renderer
