/**
 * @file _QueueFamilies.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_queue/_QueueFamilies.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _queue {

        bool _QueueFamilies::_isComplete(void) const {
            return this->_graphicsFamily.has_value() && this->_presentFamily.has_value();
        }

        std::set<_QueueFamilyIndex_t> _QueueFamilies::_toSet(void) const {
            return std::set<_QueueFamilyIndex_t> {this->_graphicsFamily.value(), this->_presentFamily.value()};
        }

        std::vector <_QueueFamilyIndex_t> _QueueFamilies::_toVector(void) const {
            return std::vector<_QueueFamilyIndex_t> {this->_graphicsFamily.value(), this->_presentFamily.value()};
        }

        _QueueHandlers_t _load(const VkDevice &logical_device, const _QueueFamilies &queue_families) {
            _QueueHandlers_t res;

            res["graphics"] = VkQueue{};
            res["presentation"] = VkQueue{};
            // Bind the logical device to the queues object
            // We are using 0 because we only create a single queue from this family (so index is 0)
            vkGetDeviceQueue(logical_device, queue_families._graphicsFamily.value(), 0, &res["graphics"]);
            vkGetDeviceQueue(logical_device, queue_families._presentFamily.value(), 0, &res["presentation"]);
            return res;
        }

        _QueueFamilies _load(const VkPhysicalDevice &physical_device, const VkSurfaceKHR &surface) {
            _QueueFamilies res = {};
            VkBool32 presentationSupport = false;

            // 1. Get the physical device queue family properties count
            uint32_t nQueueFamily = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &nQueueFamily, nullptr);
            if (nQueueFamily == 0) {
                throw std::runtime_error("No queue family for the given device");
            }
            // 2. Allocate vector and fill it up
            std::vector<VkQueueFamilyProperties> queueFamilyProperties(nQueueFamily);
            vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &nQueueFamily, queueFamilyProperties.data());

            // 3. Loop through the physical device found queue families and get the indices in the _QueueFamilies struct
            for (_QueueFamilyIndex_t i = 0; i < static_cast<_QueueFamilyIndex_t>(queueFamilyProperties.size()); i++) {
                if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                    res._graphicsFamily = i;
                }
                // 3.1 Check if this queue family supports presentation
                vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &presentationSupport);
                if (presentationSupport == true) {
                    res._presentFamily = i;
                }
            }
            return res;
        }

    } // namespace _queue
} // namespace vulkan_wrapper

