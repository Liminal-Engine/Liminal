#ifndef LIMINAL_LIB_VULKAN_WRAPPER__PIPELINE__VKPIPELINE_WRAPPERS_HPP_
#define LIMINAL_LIB_VULKAN_WRAPPER__PIPELINE__VKPIPELINE_WRAPPERS_HPP_

#include <vulkan/vulkan.h>

namespace vulkan_wrapper {
    namespace _pipeline {

        /**
         * @brief Loads a pipeline
         * 
         * @param logical_device (const VkDevice &) The related logical device
         * @param swap_chain_extent (const VkExtent2D &) The related swap chain extent
         * @param pipeline_layout (const VkPipelineLayout &) The related pipeline layout
         * @param render_pass (const VkRenderPass &) The related render pass
         * @return VkPipeline 
         */
        VkPipeline _load(
            const VkDevice &logical_device,
            const VkExtent2D &swap_chain_extent,
            const VkPipelineLayout &pipeline_layout,
            const VkRenderPass &render_pass
        );

        /**
         * @brief Destroy a Vulkan pipeline
         * 
         * @param logical_device (const VkDevice &) The related logical device
         * @param pipeline (const VkPipeline &) The pipeline to destroy
         * @param p_allocator (VkAllocationCallbacks *) Vulkan allocation callbacks 
         */
        void _destroy(
            const VkDevice &logical_device,
            const VkPipeline &pipeline,
            VkAllocationCallbacks *p_allocator = nullptr
        );

    } // _pipeline
} // vulkan_wrapper


#endif // LIMINAL_LIB_VULKAN_WRAPPER__PIPELINE__VKPIPELINE_WRAPPERS_HPP_