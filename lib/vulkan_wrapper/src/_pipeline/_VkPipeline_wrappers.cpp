#include "_private/_pipeline/_VkPipeline_wrappers.hpp"

#include "_private/_shader/_VkShaderModule_wrappers.hpp"

#include <vector>
#include <stdexcept>

namespace vulkan_wrapper {
    namespace _pipeline {

        static VkPipelineShaderStageCreateInfo __getVertexShaderCreateInfo(const VkShaderModule &vertex_module) {
            VkPipelineShaderStageCreateInfo res{};
            res.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            res.stage = VK_SHADER_STAGE_VERTEX_BIT; // Telling which pipeline stage it is
            res.module = vertex_module;
            res.pName = "main";
            return res;
        }

        static VkPipelineShaderStageCreateInfo __getFragmentShaderModuleCreateInfo(const VkShaderModule &fragment_module) {
            VkPipelineShaderStageCreateInfo res{};
            res.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            res.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
            res.module = fragment_module;
            res.pName = "main";
            return res;
        }

        static VkPipelineVertexInputStateCreateInfo __getVertexInputStateCreateInfo(void) {
            VkPipelineVertexInputStateCreateInfo res{};
            res.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
            res.vertexBindingDescriptionCount = 0;
            res.pVertexBindingDescriptions = nullptr; // Optional
            res.vertexAttributeDescriptionCount = 0;
            res.pVertexAttributeDescriptions = nullptr; // Optional
            return res;
        }

        static VkPipelineInputAssemblyStateCreateInfo __getInputAssemblyStateCreateInfo(void) {
            VkPipelineInputAssemblyStateCreateInfo res{};
            res.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
            res.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
            res.primitiveRestartEnable = VK_FALSE;
            return res;
        }

        static VkViewport __getViewport(const VkExtent2D &swap_chain_extent) {
            VkViewport res{};
            res.x = 0.0f;
            res.y = 0.0f;
            res.width = (float)swap_chain_extent.width;
            res.height = (float)swap_chain_extent.height;
            res.minDepth = 0.0f; //Specify range of depth values for the framebuffer
            res.maxDepth = 1.0f;
            return res;
        }

        static VkRect2D __getScissor(const VkExtent2D &swap_chain_extent) {
            VkRect2D res{};
            res.offset = {0, 0};
            res.extent = swap_chain_extent;
            return res;
        }

        static VkPipelineViewportStateCreateInfo __getViewportStateCreateInfo(VkViewport *viewport, VkRect2D *scissor) {
            VkPipelineViewportStateCreateInfo res{};
            res.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
            res.viewportCount = 1;
            res.pViewports = viewport;
            res.scissorCount = 1;
            res.pScissors = scissor;
            return res;
        }

        static VkPipelineRasterizationStateCreateInfo __getRasterizationStateCreateInfo(void) {
            VkPipelineRasterizationStateCreateInfo res{};
            res.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
            res.depthClampEnable = VK_FALSE;
            res.rasterizerDiscardEnable = VK_FALSE;
            res.polygonMode = VK_POLYGON_MODE_FILL;
            res.lineWidth = 1.0f;
            res.cullMode = VK_CULL_MODE_BACK_BIT;
            res.frontFace = VK_FRONT_FACE_CLOCKWISE;
            res.depthBiasEnable = VK_FALSE;
            res.depthBiasConstantFactor = 0.0f; // Optional
            res.depthBiasClamp = 0.0f; // Optional
            res.depthBiasSlopeFactor = 0.0f; // Optional
            return res;

        }

        static VkPipelineMultisampleStateCreateInfo __getMultisampleStateCreateInfo(void) {
            VkPipelineMultisampleStateCreateInfo res{};
            res.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
            res.sampleShadingEnable = VK_FALSE;
            res.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
            res.minSampleShading = 1.0f; // Optional
            res.pSampleMask = nullptr; // Optional
            res.alphaToCoverageEnable = VK_FALSE; // Optional
            res.alphaToOneEnable = VK_FALSE; // Optional
            return res;
        }

        static VkPipelineColorBlendAttachmentState __getColorBlendAttachmentState(void) {
            VkPipelineColorBlendAttachmentState res{};
            res.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
            res.blendEnable = VK_TRUE; // Optional
            res.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA; // Optional
            res.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA; // Optional
            res.colorBlendOp = VK_BLEND_OP_ADD; // Optional
            res.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
            res.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
            res.alphaBlendOp = VK_BLEND_OP_ADD; // Optional
            return res;
        }

        static VkPipelineColorBlendStateCreateInfo __getColorBlendStateCreateInfo(VkPipelineColorBlendAttachmentState *color_blend_attachment_state) {
            VkPipelineColorBlendStateCreateInfo res{};
            res.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
            res.logicOpEnable = VK_FALSE;
            res.logicOp = VK_LOGIC_OP_COPY; // Optional
            res.attachmentCount = 1;
            res.pAttachments = color_blend_attachment_state;
            res.blendConstants[0] = 0.0f; // Optional
            res.blendConstants[1] = 0.0f; // Optional
            res.blendConstants[2] = 0.0f; // Optional
            res.blendConstants[3] = 0.0f; // Optional
            /*If you preffer to use the second method of blending (bitwise combination), you must set "logicOpEnable" to
            VK_TRUE and set "logicOp". Doing so will automatically disable the first method.*/
            return res;
        }

        static std::vector<VkDynamicState> __getDynamicStates(void) {
            return std::vector<VkDynamicState> {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR};
        }

        static VkPipelineDynamicStateCreateInfo __getDynamicStateCreateInfo(const std::vector<VkDynamicState> &dynamic_states) {
            VkPipelineDynamicStateCreateInfo res{};
            res.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
            res.dynamicStateCount = static_cast<uint32_t>(dynamic_states.size());
            res.pDynamicStates = dynamic_states.data();
            return res;
        }

        VkPipeline _load(
            const VkDevice &logical_device,
            const VkExtent2D &swap_chain_extent,
            const VkPipelineLayout &pipeline_layout,
            const VkRenderPass &render_pass
        ) {
            VkPipeline res;

            // Can be united in one function call
            VkShaderModule vertex_module = _shader::_load(logical_device, "./shaders/shader.vert.spv");
            VkShaderModule fragment_module = _shader::_load(logical_device, "./shaders/shader.frag.spv");
            VkPipelineShaderStageCreateInfo vertex_shader_module = __getVertexShaderCreateInfo(vertex_module);
            VkPipelineShaderStageCreateInfo fragmentShaderModule = __getFragmentShaderModuleCreateInfo(fragment_module);
            VkPipelineShaderStageCreateInfo shader_stages[] = { vertex_shader_module, fragmentShaderModule };
            
            VkPipelineVertexInputStateCreateInfo vertexInputeStateCreateInfo = __getVertexInputStateCreateInfo();
            VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateCreateInfo = __getInputAssemblyStateCreateInfo();
            VkViewport viewport = __getViewport(swap_chain_extent);
            VkRect2D scissor = __getScissor(swap_chain_extent); // Describes in which region pixels will actually be stored
            VkPipelineViewportStateCreateInfo viewport_state_create_info = __getViewportStateCreateInfo(&viewport, &scissor); // Contains viewport and scissor
            VkPipelineRasterizationStateCreateInfo rasterization_state_create_info = __getRasterizationStateCreateInfo(); //takes geometry by vertices and turns it into fragment to be colored by the fragment shader
            VkPipelineMultisampleStateCreateInfo multisample_state_create_info = __getMultisampleStateCreateInfo();
            VkPipelineColorBlendAttachmentState color_blend_attachment_state = __getColorBlendAttachmentState();
            VkPipelineColorBlendStateCreateInfo color_blend_state_create_info = __getColorBlendStateCreateInfo(&color_blend_attachment_state);
            std::vector<VkDynamicState> dynamic_states = __getDynamicStates();
            VkPipelineDynamicStateCreateInfo dynamic_state_create_info = __getDynamicStateCreateInfo(dynamic_states);

            VkGraphicsPipelineCreateInfo create_info{};
            create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
            create_info.stageCount = 2;
            create_info.pStages = shader_stages;
            create_info.pVertexInputState = &vertexInputeStateCreateInfo;
            create_info.pInputAssemblyState = &inputAssemblyStateCreateInfo;
            create_info.pViewportState = &viewport_state_create_info;
            create_info.pRasterizationState = &rasterization_state_create_info;
            create_info.pMultisampleState = &multisample_state_create_info;
            create_info.pDepthStencilState = nullptr; // Optional
            create_info.pColorBlendState = &color_blend_state_create_info;
            create_info.pDynamicState = &dynamic_state_create_info;
            create_info.layout = pipeline_layout;
            create_info.renderPass = render_pass;
            create_info.subpass = 0;
            create_info.basePipelineHandle = VK_NULL_HANDLE;
            create_info.basePipelineIndex = -1;
            if (vkCreateGraphicsPipelines(logical_device, VK_NULL_HANDLE, 1, &create_info, nullptr, &res) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create graphics pipeline");
            }
            _shader::_destroy(logical_device, vertex_module, nullptr);
            _shader::_destroy(logical_device, fragment_module, nullptr);
            return res;
        }

        void _destroy(
            const VkDevice &logical_device,
            const VkPipeline &pipeline,
            VkAllocationCallbacks *p_allocator
        ) {
            vkDestroyPipeline(logical_device, pipeline, p_allocator);
        }

    } // _pipeline
} // vulkan_wrapper

