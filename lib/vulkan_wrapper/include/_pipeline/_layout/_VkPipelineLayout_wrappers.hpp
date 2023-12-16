/**
 * @file _VkPipelineLayout_wrappers.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-16
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_VULKAN_WRAPPER__PIPELINE__LAYOUT__VKPIPELINELAYOUT_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__PIPELINE__LAYOUT__VKPIPELINELAYOUT_WRAPPERS_HPP_

#include <vulkan/vulkan.h>

namespace vulkan_wrapper {
    namespace _pipeline {
        namespace _layout {

            /**
             * @brief Loads a Vulkan pipeline layout
             * 
             * @param logical_device 
             * @return The created Vulkan pipeline layout (VkPipelineLayout)
             */
            VkPipelineLayout _load(const VkDevice &logical_device);

            /**
             * @brief Destroy a Vulkan pipeline layout
             * 
             * @param logical_device (const VkDevice &) The related Vulkan logical device
             * @param pipeline_layout (const VkPipelineLayout &) The Vulkan pipeline layout to destroy
             * @param p_allocator (const VkAllocationCallbacks *) (default = nullptr) Vulkan custom allocator
             */
            void _destroy(
                const VkDevice &logical_device,
                const VkPipelineLayout &pipeline_layout,
                const VkAllocationCallbacks *p_allocator = nullptr
            );

        } // namespace _layout
    } // _pipeline
} // vulkan_wrapper


#endif // LIMINAL_LIB_VULKAN_WRAPPER__PIPELINE__LAYOUT__VKPIPELINELAYOUT_WRAPPERS_HPP_