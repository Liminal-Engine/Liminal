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

#include "__private/__PipelineHandler.hpp"

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
                vk::raii::PipelineLayout __layout;
                vk::raii::RenderPass __renderPass;
                std::unordered_map<std::string, vk::raii::Pipeline> __pipelines;

                static vk::raii::PipelineLayout __createLayout(const __private::__GPU &gpu) {
                    logger::trace << "Creating graphics pipeline layout create info for GPU " << gpu.getName() << std::endl;
                    vk::PipelineLayoutCreateInfo createInfo(
                        {},
                        {},
                        {}
                    );
                    logger::trace << "Creating graphics pipeline layout for GPU " << gpu.getName() << std::endl;
                    return vk::raii::PipelineLayout(gpu.getVKLogicalDevice(), createInfo);
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
                    return vk::raii::RenderPass(gpu.getVKLogicalDevice(), createInfo);
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
                    vk::raii::ShaderModule vertexShaderModule(gpu.getVKLogicalDevice(), vertexShaderModuleCreateInfo);
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
                    vk::raii::ShaderModule fragmentShaderModule(gpu.getVKLogicalDevice(), fragmentShaderModuleCreateInfo);
                    #pragma endregion
                    #pragma region 3. Shader stages
                    vk::PipelineShaderStageCreateInfo vertexShaderStageCreateInfo({}, vk::ShaderStageFlagBits::eVertex, *vertexShaderModule, "main");
                    vk::PipelineShaderStageCreateInfo fragmentShaderStageCreateInfo({}, vk::ShaderStageFlagBits::eFragment, *fragmentShaderModule, "main");
                    std::vector<vk::PipelineShaderStageCreateInfo> allStagesCreateInfos{vertexShaderStageCreateInfo, fragmentShaderStageCreateInfo};
                    #pragma endregion
                    #pragma region 4. Vertex input
                    vk::PipelineVertexInputStateCreateInfo inputStateCreateInfo({}, 0, nullptr, 0, nullptr);
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
                    return vk::raii::Pipeline(gpu.getVKLogicalDevice(), nullptr, pipelineCreateInfo);
                    #pragma endregion
                }

            public:
                __Impl(const __private::__GPU &gpu, const __private::__SwapChain &swapChain) :
                __layout(__createLayout(gpu)),
                __renderPass(__createRenderPass(gpu, swapChain)),
                __pipelines([&]() {
                        std::unordered_map<std::string, vk::raii::Pipeline> map;
                        map.emplace("graphics", __createVKPipeline(gpu, swapChain, this->__layout, this->__renderPass));
                        return map;
                }())
                {

                }

                const vk::raii::RenderPass &getRenderPass(void) const { return this->__renderPass; }

                std::optional<std::reference_wrapper<const vk::raii::Pipeline>> getPipeline(const std::string &name) const {
                    auto it = this->__pipelines.find(name);
                    if (it == this->__pipelines.end()) return std::nullopt;
                    return std::cref(it->second);
                }
        };


        __PipelineHandler::__PipelineHandler(const __private::__GPU &gpu,  const __private::__SwapChain &swapChain) : __impl(std::make_unique<__Impl>(gpu, swapChain)) {}
        __PipelineHandler::~__PipelineHandler() = default;

        const vk::raii::RenderPass &__PipelineHandler::getRenderPass(void) const { return this->__impl->getRenderPass(); }
        std::optional<std::reference_wrapper<const vk::raii::Pipeline>> __PipelineHandler::getPipeline(const std::string &name) const { return this->__impl->getPipeline(name); }
    } // namespace __private
    
    

} // namespace renderer
