/**
 * @file __Presenter.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-25
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__PRESENTER_HPP__
#define __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__PRESENTER_HPP__

#include "Renderer.hpp"
#include "__private/__GPU.hpp"
#include "__private/__SwapChain.hpp"
#include "__private/__PipelineHandler.hpp"

#include <memory>

namespace renderer {
    namespace __private {
        class __Presenter {
            public:
                __Presenter(
                    __GPU &gpu,
                    __SwapChain &swapChain,
                    const __PipelineHandler &pipelineHandler
                );
                ~__Presenter();

                __GPU::__Queue &getGPUGraphicsQueue(void);
                __GPU::__Queue &getGPUPresentQueue(void);
    
                void draw(void);

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace __private
    
} // namespace renderer


#endif // __LIMINAL__LIB__RENDERER__INCLUDE__PUBLIC__RENDERER__PRESENTER_HPP__