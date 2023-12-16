#include "_pipeline/_layout/_VkPipelineLayout_wrappers.hpp"

#include <stdexcept>

namespace vulkan_wrapper {
    namespace _pipeline {
        namespace _layout {

            VkPipelineLayout _load(const VkDevice &logical_device) {
                VkPipelineLayout res{};
                VkPipelineLayoutCreateInfo create_info{};

                create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                create_info.setLayoutCount = 0; // Optional
                create_info.pSetLayouts = nullptr; // Optional
                create_info.pushConstantRangeCount = 0; // Optional, other way of passing dynamic values
                create_info.pPushConstantRanges = nullptr; // Optional

                if (vkCreatePipelineLayout(logical_device, &create_info, nullptr, &res) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create pipeline layout");
                }
                return res;
            }

            void _destroy(
                const VkDevice &logical_device,
                const VkPipelineLayout &pipeline_layout,
                const VkAllocationCallbacks *p_allocator
            ) {
                vkDestroyPipelineLayout(logical_device, pipeline_layout, p_allocator);
            }

        } // namespace _layout
    } // _pipeline
} // vulkan_wrapper
