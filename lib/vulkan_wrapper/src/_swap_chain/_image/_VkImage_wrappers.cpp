#include "_swap_chain/_image/_VkImage_wrappers.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _swap_chain {
        namespace _image {

            std::vector<VkImage> _load(const VkDevice &logical_device, const VkSwapchainKHR &swap_chain) {
                // 1. Get the swapChain images count
                uint32_t swap_chain_n_images = 0;
                vkGetSwapchainImagesKHR(logical_device, swap_chain, &swap_chain_n_images, nullptr);
                if (swap_chain_n_images == 0) {
                    throw std::runtime_error("Error : the swap chain has been loaded with 0 images");
                }
                // 2. Create the res with the found size
                std::vector<VkImage> res(swap_chain_n_images);
                vkGetSwapchainImagesKHR(logical_device, swap_chain, &swap_chain_n_images, res.data());
                return res;
            }

        } // _image
    } // namespace _swap_chain
} // vulkan_wrapper



