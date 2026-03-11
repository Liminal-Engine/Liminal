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

namespace renderer_vk_old {
    namespace __private {
        class __GPU::__SurfaceSupport::__Impl {
            private:
                const vk::raii::PhysicalDevice &__relatedVKGPU;
                const vk::raii::SurfaceKHR &__relatedSurface;

                vk::SurfaceCapabilitiesKHR __capabilities;
                std::vector<vk::SurfaceFormatKHR> __formats;
                std::vector<vk::PresentModeKHR> __presentModes;

                vk::SurfaceCapabilitiesKHR __createCapabilities(
                    const vk::raii::PhysicalDevice &vkGPU,
                    const vk::raii::SurfaceKHR &vkSurface
                ) {
                    logger::trace << "\t\tLoading surface support: loading capabilities for GPU "
                    << static_cast<const char*>(vkGPU.getProperties().deviceName.data()) << std::endl;
                    return vkGPU.getSurfaceCapabilitiesKHR(*vkSurface);
                }

                std::vector<vk::SurfaceFormatKHR> __createFormats(
                    const vk::raii::PhysicalDevice &vkGPU,
                    const vk::raii::SurfaceKHR &vkSurface
                ) {
                    logger::trace << "\t\tLoading surface support: loading formats for GPU "
                    << static_cast<const char*>(vkGPU.getProperties().deviceName.data()) << std::endl;
                    std::vector<vk::SurfaceFormatKHR> tmp = vkGPU.getSurfaceFormatsKHR(*vkSurface);
                    return vkGPU.getSurfaceFormatsKHR(*vkSurface);
                }

                std::vector<vk::PresentModeKHR> __createPresentModes(
                    const vk::raii::PhysicalDevice &vkGPU,
                    const vk::raii::SurfaceKHR &vkSurface
                ) {
                    logger::trace << "\t\tLoading surface support: loading present modes for GPU "
                    << static_cast<const char*>(vkGPU.getProperties().deviceName.data()) << std::endl;
                    return vkGPU.getSurfacePresentModesKHR(*vkSurface);
                }

            public:
                __Impl(
                    const vk::raii::PhysicalDevice &vkGPU,
                    const vk::raii::SurfaceKHR &vkSurface
                ) :
                __relatedVKGPU(vkGPU),
                __relatedSurface(vkSurface),
                __capabilities(__createCapabilities(this->__relatedVKGPU, this->__relatedSurface)),
                __formats(__createFormats(this->__relatedVKGPU, this->__relatedSurface)),
                __presentModes(__createPresentModes(this->__relatedVKGPU, this->__relatedSurface))
                {}

                const vk::SurfaceCapabilitiesKHR &getCapabilitiles(void) const { return this->__capabilities; }
                const std::vector<vk::SurfaceFormatKHR> &getFormats(void) const { return this->__formats; }
                const std::vector<vk::PresentModeKHR> &getPresentModes(void) const { return this->__presentModes; }

                void update (void) {
                    logger::trace << "\tGPU destroying GPU surface formats" << std::endl;
                    this->__formats.clear();
                    logger::trace << "\tGPU destroying surface present modes" << std::endl;
                    this->__presentModes.clear();
                    logger::trace << "\tGPU recreating surface capabilities" << std::endl;
                    this->__capabilities = __createCapabilities(this->__relatedVKGPU, this->__relatedSurface);
                    logger::trace << "\tGPU recreating surface formats" << std::endl;
                    this->__formats = __createFormats(this->__relatedVKGPU, this->__relatedSurface);
                    logger::trace << "\tGPU recreating surface present modes" << std::endl;
                    this->__presentModes = __createPresentModes(this->__relatedVKGPU, this->__relatedSurface);
                }
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
        void __GPU::__SurfaceSupport::update(void) { this->__impl->update(); }
    } // namespace __private
} // namespace renderer_vk_old
