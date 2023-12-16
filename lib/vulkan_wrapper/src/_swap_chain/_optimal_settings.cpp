/**
 * @file _optimal_settings.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "_swap_chain/_optimal_settings.hpp"

#include <limits>

namespace vulkan_wrapper {
    namespace _swap_chain {

        VkPresentModeKHR _getBestPresentationMode(const std::vector<VkPresentModeKHR> &available_presentation_modes) {
            for (const auto &presentationMode : available_presentation_modes) {
                if (presentationMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                    return presentationMode;
                }
            }
            return VK_PRESENT_MODE_FIFO_KHR;
        }

        VkSurfaceFormatKHR _getBestSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &supported_formats) {
            for (const auto &format : supported_formats) {
                if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                    return format;
                }
            }
            return supported_formats.at(0);
        }

        VkExtent2D _getBestExtent(const window_wrapper::WindowWrapper &window, const VkSurfaceCapabilitiesKHR &surface_capabilities) {
            if (surface_capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
                return surface_capabilities.currentExtent;
            }
            // 1. Get the width and height
            VkExtent2D extent = window.getFrameBufferSize();
            // 2. We make sure values are contained in min and max possible values
            extent.width = std::clamp(extent.width, surface_capabilities.minImageExtent.width, surface_capabilities.maxImageExtent.width);
            extent.height = std::clamp(extent.height, surface_capabilities.minImageExtent.height, surface_capabilities.maxImageExtent.height);
            return extent;
        }

    } // namespace _swap_chain
} // vulkan_wrapper


