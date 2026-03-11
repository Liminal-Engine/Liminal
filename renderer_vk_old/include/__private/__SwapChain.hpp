/**
 * @file __SwapChain.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-14
 * 
 * @copyright Copyright (c) 2024
 * 
**/

#ifndef __LIMINAL__RENDERER__INCLUDE__PUBLIC__RENDERER__SWAPCHAIN_HPP__
#define __LIMINAL__RENDERER__INCLUDE__PUBLIC__RENDERER__SWAPCHAIN_HPP__

#include "__private/__GPU.hpp"
#include "__private/__Status.hpp"

#include <vulkan/vulkan_raii.hpp>
#include <GLFW/glfw3.h>

#include <memory>

namespace renderer_vk_old {
    namespace __private {
        class __SwapChain {
            public:
                class __Settings {
                    friend class __SwapChain;
                    public:
                        ~__Settings();
                        __Settings(__Settings&&) noexcept;
                        __Settings& operator=(__Settings&&) noexcept;
                        __Settings(const __Settings&) = delete;
                        __Settings& operator=(const __Settings&) = delete;

                        static __Settings createOptimal(__GPU &gpu, GLFWwindow *window);

                        const vk::SurfaceFormatKHR &getFormat(void) const;
                        const vk::PresentModeKHR &getPresentMode(void) const;
                        const vk::Extent2D &getExtent(void) const;                    

                        __Status setFormat(const vk::SurfaceFormatKHR &format);
                        __Status setPresentMode(const vk::PresentModeKHR &presentMode);
                        __Status setExtent(const vk::Extent2D &extent);
                    private:
                        __Settings(
                            const vk::SurfaceFormatKHR &format,
                            const vk::PresentModeKHR &presentMode,
                            const vk::Extent2D &extent
                        );
                        class __Impl;
                        std::unique_ptr<__Impl> __impl;
                };

                __SwapChain(GLFWwindow* window, const vk::raii::SurfaceKHR &surface, __GPU &gpu);
                ~__SwapChain();
                
                const __Settings &getSettings(void) const;
                const std::vector<vk::raii::ImageView> &getImageViews(void) const;
                const vk::raii::SwapchainKHR &getVKSwapChain(void) const;

                const std::pair<__Status, uint32_t> acquireNextimage(
                    const vk::raii::Semaphore &semaphore,
                    const uint64_t &timeout = std::numeric_limits<uint64_t>::max()
                );

                void updateUponSurfaceChange(void);

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namesapce __private
} // namespace renderer_vk_old

#endif // __LIMINAL__RENDERER__INCLUDE__PUBLIC__RENDERER__SWAPCHAIN_HPP__