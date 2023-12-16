/**
 * @file _QueueFamilies.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-15
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__QUEUE_QUEUFAMILIES_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__QUEUE_QUEUFAMILIES_HPP_

#include <vulkan/vulkan.h>
#include <optional>
#include <unordered_map>
#include <vector>
#include <string>
#include <set>

namespace vulkan_wrapper {
    namespace _queue {

        typedef uint32_t _QueueFamilyIndex_t; ///< _QueueFamilyIndex_t type
        typedef std::unordered_map<std::string, VkQueue> _QueueHandlers_t; ///< _QueueHandlers_t type = queue handlers for a specific device

        /**
         * @brief _QueueFamilies Store the queue families of a device
         */
        struct _QueueFamilies {
            std::optional<_QueueFamilyIndex_t> _graphicsFamily; ///< The graphics family
            std::optional<_QueueFamilyIndex_t> _presentFamily; ///< The presentation family
            /**
             * @brief Check if the queue family meets all requirements
             * 
             * @return true if the queue family meets all requirements
             * @return false if the queue family does not meet all requirements
             */
            bool _isComplete(void) const;
            /**
             * @brief Get the indices set of the queue families indices
             * 
             * @return std::set<_QueueFamilyIndex_t> The set of queue familie indices
             */
            std::set<_QueueFamilyIndex_t> _toSet(void) const;
            /**
             * @brief Get the indices vector of the queue families indices
             * 
             * @return std::vector <_QueueFamilyIndex_t> 
             */
            std::vector <_QueueFamilyIndex_t> _toVector(void) const;
        }; // struct _QueueFamilies

        /**
         * @brief Loads the queue handlers from a _QueueFamilies 
         * 
         * @param logical_device (const VkDevice &) The related logical device
         * @param queue_families (const _QueueFamilies &) The queue families
         * @return The created queue handlers (_QueueHandlers_t)
         */
        _QueueHandlers_t _load(const VkDevice &logical_device, const _QueueFamilies &queue_families);

        /**
         * @brief Loads a physical device queue families
         * 
         * @param physical_device (const VkPhysicalDevice &) The related Vulkan physical device
         * @param surface (const VkSurfaceKHR &) The related Vulkan surface
         * @return The found queue families (_QueueFamilies )
         */
        _QueueFamilies _load(const VkPhysicalDevice &physical_device, const VkSurfaceKHR &surface);

    } // namespace _queue
} // namespace vulkan_wrapper


#endif // LIMINAL_LIB_VULKAN_WRAPPER__QUEUE_QUEUFAMILIES_HPP_