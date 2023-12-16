#include "WindowWrapper.hpp"

#include <stdexcept>

static GLFWwindow *_load_window(const std::string &app_name) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Explicelty tells GFLW to NOT use OpenGL context
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); //Disable resize because wi will need to handle it later

    GLFWwindow *res = glfwCreateWindow(800, 600, app_name.c_str(), nullptr, nullptr);
    if (res == nullptr) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    return res;
}

namespace window_wrapper {
    WindowWrapper::WindowWrapper(void):
    window(_load_window("Liminal Engine"))
    {        

    }

    WindowWrapper::~WindowWrapper(void) {
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }

    VkResult WindowWrapper::createSurface(
        const VkInstance &instance,
        VkSurfaceKHR *p_surface, 
        VkAllocationCallbacks *p_allocator
    ) const {
        return glfwCreateWindowSurface(instance, this->window, p_allocator, p_surface);
    }

    const char **WindowWrapper::getRequiredExtensions(uint32_t __restrict__ *n_extensions) const {
        const char **res = glfwGetRequiredInstanceExtensions(n_extensions);

        if (n_extensions == 0) {
            throw std::runtime_error("No GLFW extension found"); // Should I really throw here ?
        }
        return res;
    }

    VkExtent2D WindowWrapper::getFrameBufferSize(void) const {
        int width = 0;
        int height = 0;
        VkExtent2D res{};

        glfwGetFramebufferSize(this->window, &width, &height);
        res.width = static_cast<uint32_t>(width);
        res.height = static_cast<uint32_t>(height);
        return res;
    }
}

