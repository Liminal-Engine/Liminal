/**
 * @file __PipelineHandler.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-23
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#include "__private/__vkConfig.hpp"
#include "__private/__PipelineHandler.hpp"
#include "__private/__VertexBuffer.hpp"
#include "__private/__errors.hpp"
#include "temp_consts_need_to_remove_this.hpp"

#include <logger/logger.hpp>
#include <fs/Path.hpp>
#include <fs/InFile.hpp>

#include <vulkan/vulkan_raii.hpp>

#include <vector>
#include <string>
#include <unordered_map>

namespace renderer {
    namespace __private {
        class __PipelineHandler::__Impl {
            private:
                const __GPU &__relatedGPU;
                const __SwapChain &__relatedSwapChain;

                vk::raii::PipelineLayout __vkLayout;
                vk::raii::RenderPass __vkRenderPass;
                std::unordered_map<std::string, vk::raii::Pipeline> __vkPipelines;

                __VertexBuffer __vertexBuffer;

                static vk::raii::PipelineLayout __createLayout(const __private::__GPU &gpu) {
                    logger::trace << "Creating graphics pipeline layout create info for GPU " << gpu.getName() << std::endl;
                    vk::PipelineLayoutCreateInfo createInfo(
                        {},
                        {},
                        {}
                    );
                    logger::trace << "Creating graphics pipeline layout for GPU " << gpu.getName() << std::endl;
                    auto [result, rawLayout] = gpu.getRawVKLogicalDevice().createPipelineLayout(createInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "PipelineHandler failed to create VK pipeline layout");
                        return vk::raii::PipelineLayout(nullptr);
                    }
                    return vk::raii::PipelineLayout(gpu.getVKLogicalDevice(), rawLayout);
                }

                static vk::raii::RenderPass __createRenderPass(const __private::__GPU &gpu, const __private::__SwapChain &swapChain) {
                    // 1. Attachments
                    logger::trace << "Creating render pass attachments for GPU " << gpu.getName() << std::endl;
                    std::vector<vk::AttachmentDescription> attachments {
                        vk::AttachmentDescription(
                            {},
                            swapChain.getSettings().getFormat().format,
                            vk::SampleCountFlagBits::e1,
                            vk::AttachmentLoadOp::eClear,
                            vk::AttachmentStoreOp::eStore,
                            vk::AttachmentLoadOp::eDontCare,
                            vk::AttachmentStoreOp::eDontCare,
                            vk::ImageLayout::eUndefined,
                            vk::ImageLayout::ePresentSrcKHR
                        )
                    };
                    // 2. Subpasses
                    logger::trace << "Creating render pass subpasses color attachments for GPU " << gpu.getName() << std::endl;
                    std::vector<vk::AttachmentReference> colorAttachments{
                        vk::AttachmentReference(0, vk::ImageLayout::eColorAttachmentOptimal)
                    };
                    logger::trace << "Creating render pass subpasses for GPU " << gpu.getName() << std::endl;
                    std::vector<vk::SubpassDescription> subpasses{
                        vk::SubpassDescription(
                            {},
                            vk::PipelineBindPoint::eGraphics,
                            {},
                            colorAttachments,
                            {},
                            nullptr,
                            {}
                        )
                    };
                    // 3. Create info
                    logger::trace << "Creating render pass create info for GPU " << gpu.getName() << std::endl;
                    vk::RenderPassCreateInfo createInfo(
                        {},
                        attachments,
                        subpasses
                    );
                    logger::trace << "Creating render pass for GPU " << gpu.getName() << std::endl;
                    auto [result, rawRenderPass] = gpu.getRawVKLogicalDevice().createRenderPass(createInfo);
                    if (result != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, result, "PipelineHandler failed to create a render pass");
                        return vk::raii::RenderPass(nullptr);
                    }
                    return vk::raii::RenderPass(gpu.getVKLogicalDevice(), rawRenderPass);
                }

                // TODO ? :
                // struct shaders {
                //     vert
                //     frag
                //     geom
                //     ...
                // }

                static vk::raii::Pipeline __createVKPipeline(
                    const __private::__GPU &gpu,
                    const __private::__SwapChain &swapChain,
                    const vk::raii::PipelineLayout &layout,
                    const vk::raii::RenderPass &renderPass
                ) {
                    const __SwapChain::__Settings &swapChainSettings = swapChain.getSettings();
                    // TODO : définir un système de shader, avec une prise en compte auto des différents type de shaders suivant les règles
                    // TODO : ajouter des règles de check des shaders
                    // TODO : ajouter les logs
                    #pragma region 1. vertex shader
                    fs::Path vertexSrcPath("/home/matteo/Projects/Liminal/shaders/triangle.vert.spv");
                    fs::InFile vertexFile(vertexSrcPath);
                    if (vertexFile.open() != fs::Status::OK) {
                        logger::error << "Failed to open shader: " << vertexSrcPath.asStr() << std::endl;
                        return vk::raii::Pipeline(nullptr);
                    }
                    if (vertexFile.read() != fs::Status::OK) {
                        logger::error << "Failed to read shader: " << vertexSrcPath.asStr() << std::endl;
                        return vk::raii::Pipeline(nullptr);
                    }
                    std::string vertexContent(vertexFile.getContent());
                    if (vertexContent.size() % 4 != 0) {
                        logger::error << "Error with shader: " << vertexSrcPath.asStr()
                        << "\n Content is not a multiple of 4 bytes" << std::endl;
                        return vk::raii::Pipeline(nullptr);
                    }
                    std::vector<uint32_t> vertexEncodedContent(vertexContent.size() / 4);
                    std::memcpy(vertexEncodedContent.data(), vertexContent.data(), vertexContent.size());
                    vk::ShaderModuleCreateInfo vertexShaderModuleCreateInfo({}, vertexEncodedContent);                    
                    vk::raii::ShaderModule vertexShaderModule(nullptr);
                    auto [rawVertexShaderResult, rawVertexShaderModule] = gpu.getRawVKLogicalDevice().createShaderModule(vertexShaderModuleCreateInfo);
                    if (rawVertexShaderResult != vk::Result::eSuccess) { __LOG_VK_CREATE_ERROR(gpu, rawVertexShaderResult, "PipelineHandler failed to create vertex shader module"); }
                    else { vertexShaderModule = vk::raii::ShaderModule(gpu.getVKLogicalDevice(), rawVertexShaderModule); }
                    #pragma endregion
                    #pragma region 2. fragment shader
                    fs::Path fragmentSrcPath("/home/matteo/Projects/Liminal/shaders/triangle.frag.spv");
                    fs::InFile fragmentFile(fragmentSrcPath);
                    if (fragmentFile.open() != fs::Status::OK) {
                        logger::error << "Failed to open shader: " << fragmentSrcPath.asStr() << std::endl;
                        return vk::raii::Pipeline(nullptr);
                    }
                    if (fragmentFile.read() != fs::Status::OK) {
                        logger::error << "Failed to read shader: " << fragmentSrcPath.asStr() << std::endl;
                        return vk::raii::Pipeline(nullptr);
                    }
                    std::string fragmentContent(fragmentFile.getContent());
                    if (fragmentContent.size() % 4 != 0) {
                        logger::error << "Error with shader: " << fragmentSrcPath.asStr()
                        << "\n Content is not a multiple of 4 bytes" << std::endl;
                        return vk::raii::Pipeline(nullptr);
                    }
                    std::vector<uint32_t> encodedContent(fragmentContent.size() / 4);
                    std::memcpy(encodedContent.data(), fragmentContent.data(), fragmentContent.size());
                    vk::ShaderModuleCreateInfo fragmentShaderModuleCreateInfo({}, encodedContent);
                    vk::raii::ShaderModule fragmentShaderModule(nullptr);
                    auto [rawFragmentShaderResult, rawFragmentShaderModule] = gpu.getRawVKLogicalDevice().createShaderModule(fragmentShaderModuleCreateInfo);
                    if (rawFragmentShaderResult != vk::Result::eSuccess) { __LOG_VK_CREATE_ERROR(gpu, rawFragmentShaderResult, "PipelineHandler failed to create fragment shader module"); }
                    else { fragmentShaderModule = vk::raii::ShaderModule(gpu.getVKLogicalDevice(), rawFragmentShaderModule); }
                    #pragma endregion
                    #pragma region 3. Shader stages
                    vk::PipelineShaderStageCreateInfo vertexShaderStageCreateInfo({}, vk::ShaderStageFlagBits::eVertex, *vertexShaderModule, "main");
                    vk::PipelineShaderStageCreateInfo fragmentShaderStageCreateInfo({}, vk::ShaderStageFlagBits::eFragment, *fragmentShaderModule, "main");
                    std::vector<vk::PipelineShaderStageCreateInfo> allStagesCreateInfos{vertexShaderStageCreateInfo, fragmentShaderStageCreateInfo};
                    #pragma endregion
                    #pragma region 4. Vertex input
                    auto bindingDescription = VERTEX::getBindingDescription();
                    auto attributeDescriptions = VERTEX::getAttributeDescriptions();
                    vk::PipelineVertexInputStateCreateInfo inputStateCreateInfo({}, bindingDescription, attributeDescriptions);
                    #pragma endregion
                    #pragma region 5. Input assembler
                    vk::PipelineInputAssemblyStateCreateInfo inputAssemblyCreateInfo({}, vk::PrimitiveTopology::eTriangleList, vk::False);
                    #pragma endregion
                    #pragma region 6. Viewport and scissor
                    std::vector<vk::Viewport> viewports{ vk::Viewport(0.0f, 0.0f, swapChainSettings.getExtent().width, swapChainSettings.getExtent().height, 0.0f, 1.0f) };
                    std::vector<vk::Rect2D> scissors{ vk::Rect2D(vk::Offset2D(0, 0), swapChainSettings.getExtent()) };
                    vk::PipelineViewportStateCreateInfo viewportCreateInfo({}, viewports, scissors);
                    #pragma endregion
                    #pragma region 7. Rasterizer
                    vk::PipelineRasterizationStateCreateInfo rasterizerCreateInfo(
                        {},
                        vk::False,
                        vk::False,
                        vk::PolygonMode::eFill,
                        vk::CullModeFlagBits::eBack,
                        vk::FrontFace::eClockwise,
                        vk::False,
                        0.0f,
                        0.0f,
                        0.0f,
                        1.0f
                    );
                    #pragma endregion
                    #pragma region 8. Multisampling
                    vk::PipelineMultisampleStateCreateInfo multisamplerCreateInfo(
                        {},
                        vk::SampleCountFlagBits::e1,
                        vk::False,
                        1.0f,
                        nullptr,
                        vk::False,
                        vk::False
                    );
                    #pragma endregion
                    #pragma region 9. Color blending
                    std::vector<vk::PipelineColorBlendAttachmentState> colorBlendAttachments{
                        vk::PipelineColorBlendAttachmentState(
                            vk::False,
                            vk::BlendFactor::eOne,
                            vk::BlendFactor::eZero,
                            vk::BlendOp::eAdd,
                            vk::BlendFactor::eOne,
                            vk::BlendFactor::eZero,
                            vk::BlendOp::eAdd,
                            vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA
                        )
                    };
                    std::array<float, 4> blendConstants{0.0f, 0.0f, 0.0f, 0.0f};
                    vk::PipelineColorBlendStateCreateInfo colorBlenderCreateInfo(
                        {},
                        vk::False,
                        vk::LogicOp::eCopy,
                        colorBlendAttachments,
                        blendConstants
                    );
                    #pragma endregion
                    #pragma region 10. Dynamic states
                    std::vector<vk::DynamicState> dynamicStates { vk::DynamicState::eViewport, vk::DynamicState::eScissor };
                    vk::PipelineDynamicStateCreateInfo dynamicStatesCreateInfo({}, dynamicStates);
                    #pragma endregion
                    #pragma region 11. Graphics pipeline create info
                    vk::GraphicsPipelineCreateInfo pipelineCreateInfo(
                        {},
                        allStagesCreateInfos,
                        &inputStateCreateInfo,
                        &inputAssemblyCreateInfo,
                        nullptr, 
                        &viewportCreateInfo,
                        &rasterizerCreateInfo,
                        &multisamplerCreateInfo,
                        nullptr,
                        &colorBlenderCreateInfo,
                        &dynamicStatesCreateInfo,
                        *layout,
                        *renderPass,
                        0,
                        {},
                        -1
                    );
                    #pragma endregion
                    #pragma region 12. Create graphics pipeline
                    auto [rawPipelineResult, rawPipeline] = gpu.getRawVKLogicalDevice().createGraphicsPipeline(nullptr, pipelineCreateInfo);
                    if (rawPipelineResult != vk::Result::eSuccess) {
                        __LOG_VK_CREATE_ERROR(gpu, rawPipelineResult, "PipelineHandler failed to create VK pipeline");
                        return vk::raii::Pipeline(nullptr);
                    }
                    return vk::raii::Pipeline(gpu.getVKLogicalDevice(), rawPipeline);
                    #pragma endregion
                }

                static std::unordered_map<std::string, vk::raii::Pipeline> __createVKPipelines(
                    const __private::__GPU &gpu,
                    const __private::__SwapChain &swapChain,
                    const vk::raii::PipelineLayout &vkLayout,
                    const vk::raii::RenderPass &vkRenderPass
                ) {
                    logger::trace << "PipelineHandler creating VK graphics pipelines" << std::endl;
                    std::unordered_map<std::string, vk::raii::Pipeline> map;
                    logger::trace << "Creating graphics pipeline \"" << "GRAPHICS" << "\"" << std::endl;
                    map.emplace("GRAPHICS", __createVKPipeline(gpu, swapChain, vkLayout, vkRenderPass));
                    return map;
                }

                static uint32_t __findGPUMemoryType(
                    const __GPU &gpu,
                    const uint32_t &filter,
                    const vk::MemoryPropertyFlags &memProperties
                ) {
                    vk::PhysicalDeviceMemoryProperties gpuMemProps = gpu.getVKPhysicalDevice().getMemoryProperties();
                    for (uint32_t i = 0; i < gpuMemProps.memoryTypeCount; i++) {
                        if (filter & (1 << i) && (gpuMemProps.memoryTypes[i].propertyFlags & memProperties) == memProperties) {
                            return i;
                        }
                    }
                    logger::error << "Cannot find a memory type suitable with given filter: " << filter << std::endl;
                    return 0;
                }
            
                static __VertexBuffer __createVertexBuffer(const __GPU &gpu) {
                    logger::trace << "PipelineHandler creating a vertex buffer for GPU " << gpu.getName() << std::endl;
                    return __VertexBuffer(gpu, VERTICES);
                    
                }
            public:
                __Impl(const __private::__GPU &gpu, const __private::__SwapChain &swapChain) :
                __relatedGPU(gpu),
                __relatedSwapChain(swapChain),
                __vkLayout(__createLayout(this->__relatedGPU)),
                __vkRenderPass(__createRenderPass(this->__relatedGPU, this->__relatedSwapChain)),
                __vkPipelines(__createVKPipelines(this->__relatedGPU, this->__relatedSwapChain, this->__vkLayout, this->__vkRenderPass)),
                __vertexBuffer(__createVertexBuffer(this->__relatedGPU))
                {
                    // // We MAP the data
                    // // 1. Map
                    // // The mapMemory method allow to accesss to specified region (defined py offset and size) of the
                    // // GPU RAM to a CPU pointer. You can specify VK_WHOLE_SIZE to map the whole size.
                    // auto [result, data] = this->__relatedGPU.getRawVKLogicalDevice().mapMemory(
                    //     *this->__oldVertexBufferMemoryDELETEME, // raw device memory
                    //     0, // offset 
                    //     sizeof(VERTICES[0]) * VERTICES.size() // total size (could be also bufferCreateInfo.size)
                    // );
                    // if (result != vk::Result::eSuccess) {
                    //     logger::error << "Failed to access GPU memory" << std::endl;
                    //     return;
                    // }
                    // // 2. Copy CPU content to CPU pointer
                    // // Now that we have a corresponding CPU pointer, let's fill it up
                    // if (memcpy(
                    //     data, // dest
                    //     VERTICES.data(), // src
                    //     sizeof(VERTICES[0]) * VERTICES.size() // size (could ba also bufferCreateInfo.size)
                    // ) == NULL) {
                    //     logger::error << "Failed to integrate verticies data to CPU pointer" << std::endl;
                    // }
                    // // 3. Unmap
                    // /**
                    //  * As long as the GPU memory is "mapped" to the CPU, the GPU cannot access it. This is why it is
                    //  * mandatory to unmap it.
                    //  * The driver may not immediately copy the data, because of caching for example.
                    //  * To handle this, we have 2 solutions :
                    //  * 1. use deviceMemoryAllocInfo.setMemoryTypeIndex(..., eHostCoherent)
                    //  * 2. call vkFlushMappedMemoryRanges after writting to the mapped memory and call vkInvalidateMappedMemoryRanges before reading from the mapped memory
                    //  * The solution 2 leads to slighlty better performances but we'll see later why it apparently does not matter.
                    //  * This does not return anything
                    //  */
                    // this->__relatedGPU.getRawVKLogicalDevice().unmapMemory(*this->__oldVertexBufferMemoryDELETEME);
                }

                const vk::raii::RenderPass &getRenderPass(void) const { return this->__vkRenderPass; }

                std::optional<std::reference_wrapper<const vk::raii::Pipeline>> getPipeline(const std::string &name) const {
                    auto it = this->__vkPipelines.find(name);
                    if (it == this->__vkPipelines.end()) return std::nullopt;
                    return std::cref(it->second);
                }

                void updateUponSwapChainFormatChange(void) {
                    logger::trace << "\tPipelineHandler destroying VK render pass" << std::endl;
                    this->__vkRenderPass.clear();
                    logger::trace << "\tPipelineHandler recreating VK render pass" << std::endl;
                    this->__vkRenderPass = __createRenderPass(this->__relatedGPU, this->__relatedSwapChain);
                    // graphics pipelines needs to be recreated if the render pass changes or if the viewport is non dynamic
                    // in our case, viewport is dynamic but since the renderpass change, we need to recreate the graphics pipelines as well
                    // N.B.: this only concerns the graphics pipelines
                    logger::trace << "\tPipelineHandler destroying VK graphics pipelines" << std::endl;
                    this->__vkPipelines.clear();
                    logger::trace << "\tPipelineHandler recreating VK graphics pipelines" << std::endl;
                    this->__vkPipelines = __createVKPipelines(this->__relatedGPU, this->__relatedSwapChain, this->__vkLayout, this->__vkRenderPass);
                }

                const __VertexBuffer &getVertexBuffer(void) const { return this->__vertexBuffer; }
        };

        __PipelineHandler::__PipelineHandler(const __private::__GPU &gpu,  const __private::__SwapChain &swapChain) : __impl(std::make_unique<__Impl>(gpu, swapChain)) {}
        __PipelineHandler::~__PipelineHandler() = default;

        const vk::raii::RenderPass &__PipelineHandler::getRenderPass(void) const { return this->__impl->getRenderPass(); }
        std::optional<std::reference_wrapper<const vk::raii::Pipeline>> __PipelineHandler::getPipeline(const std::string &name) const { return this->__impl->getPipeline(name); }
        void __PipelineHandler::updateUponSwapChainFormatChange(void) { this->__impl->updateUponSwapChainFormatChange(); }

        const __VertexBuffer &__PipelineHandler::getVertexBuffer(void) const { return this->__impl->getVertexBuffer(); }
    } // namespace __private
    
    

} // namespace renderer
