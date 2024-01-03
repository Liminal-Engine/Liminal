#ifndef LIMINAL_LIB_VULKAN_WRAPPER__EXTENSION__EXTENSION_WRAPPERS_HPP
#define LIMINAL_LIB_VULKAN_WRAPPER__EXTENSION__EXTENSION_WRAPPERS_HPP

#include <vulkan/vulkan.h>

#include <vector>
#include <string>
#include <unordered_map>

namespace vulkan_wrapper{
    namespace _extension {

        
        using _Extensions_group_t = std::vector<const char *>;
        using _Extensions_t = std::unordered_map<std::string, _Extensions_group_t>;

        /**
         * @brief Load wanted extensions
         * 
         * @return _Extensions_t
         */
        _Extensions_t _load(void);

        /**
         * @brief Checks if a physical device supports the wanted extensions
         * 
         * @param physical_device 
         * @param wanted_extensions 
         * @return true if found
         * @return false otherwise
         */
        bool _checkPhysicalDeviceExtensionSupport(const VkPhysicalDevice &physical_device, const _Extensions_group_t &wanted_extensions);

    } // namespace extension 
} // namespace vulkan_wrapper

#endif // LIMINAL_LIB_VULKAN_WRAPPER__EXTENSION__EXTENSION_WRAPPERS_HPP
