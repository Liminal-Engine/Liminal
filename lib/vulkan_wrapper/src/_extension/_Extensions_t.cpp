#include "_private/_extension/_Extensions_t.hpp"

#include "liminal_windowing/WindowWrapper.hpp"

#include <stdint.h>
#include <string.h>

namespace vulkan_wrapper{
    namespace _extension {
        
        _Extensions_t _load(void) {
            _Extensions_t res;
            _Extensions_group_t window_extensions = window_wrapper::getRequiredVulkanExtensions();

            res["window"] = std::vector(window_extensions.begin(), window_extensions.end());
            res["device"] = std::vector({VK_KHR_SWAPCHAIN_EXTENSION_NAME});

            return res;
        }

        bool _checkPhysicalDeviceExtensionSupport(const VkPhysicalDevice &physical_device, const _Extensions_group_t &wanted_extensions) {
            uint32_t n_extensions = 0;
            bool found = false;

            vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &n_extensions, nullptr);
            std::vector<VkExtensionProperties> available_extensions_props(n_extensions);
            vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &n_extensions, available_extensions_props.data());

            for (const char *wanted_extension : wanted_extensions) {
                found = false;
                for (const VkExtensionProperties &available_extension_props : available_extensions_props) {
                    if (strcmp(available_extension_props.extensionName, wanted_extension) == 0) {
                        found = true;
                    }
                }
                if (found == false) {
                    return false; // It means that at least one of the extension is not available
                }
            }
            return true;
        }
    } // namespace extension 
} // namespace vulkan_wrapper

