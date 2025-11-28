/**
 * @file __PipelineHandler.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-23
 * 
 * @copyright Copyright (c) 2024
 * 
**/
#ifndef __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__GRAPHICS_PIPELINE_HPP__
#define __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__GRAPHICS_PIPELINE_HPP__

#include "__private/__GPU.hpp"
#include "__private/__SwapChain.hpp"

#include <memory>
#include <optional>

namespace renderer {
    namespace __private {
        class __PipelineHandler {
            public:
                __PipelineHandler(const __private::__GPU &gpu, const __private::__SwapChain &swapChain);
                ~__PipelineHandler();
    
                const vk::raii::RenderPass &getRenderPass(void) const;
    
                std::optional<std::reference_wrapper<const vk::raii::Pipeline>> getPipeline(const std::string &name) const;

                void updateUponSwapChainFormatChange(void);
    
            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace __private
} // namespace renderer


#endif // __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__GRAPHICS_PIPELINE_HPP__