#ifndef LIMINAL_LIB_WINDOW_WRAPPER_WINDOWWRAPPER_HPP_
#define LIMINAL_LIB_WINDOW_WRAPPER_WINDOWWRAPPER_HPP_

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

namespace window_wrapper {
    class WindowWrapper {

        public:
            WindowWrapper(void);
            ~WindowWrapper(void);

            GLFWwindow *window;

            /**
             * @brief Create a Surface object
             * 
             * @param instance (const VkInstance &)
             * @param p_surface (VkSurfaceKHR *)
             * @param p_allocator (VkAllocationCallbacks *)
             * @return VkResult 
             */
            VkResult createSurface(
                const VkInstance &instance,
                VkSurfaceKHR *p_surface, 
                VkAllocationCallbacks *p_allocator = nullptr
            ) const;

            /**
             * @brief Get the Required Extensions object
             * 
             * @param n_extentsions (uint32_t *)
             * @return char** 
             */
            const char **getRequiredExtensions(uint32_t __restrict__ *n_extensions) const;

            /**
             * @brief Get the Frame Buffer Size object
             * 
             * @param width (int *)
             * @param height (int *)
            */
            VkExtent2D getFrameBufferSize(void) const;

            /**
             * @brief Tells if the window should close
             * 
             * @return true 
             * @return false 
             */ 
            bool shouldClose(void) const;

            void pollEvents(void) const;

        // private:
    };
}

#endif // LIMINAL_LIB_WINDOW_WRAPPER_WINDOWWRAPPER_HPP_