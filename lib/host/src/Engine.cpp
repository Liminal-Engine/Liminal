#include "Engine.hpp"

#include <rhi/Renderer.hpp>
#include <logger/logger.hpp>

#include <GLFW/glfw3.h>

namespace host {
    class Engine::__Impl {
        private:
            GLFWwindow *__window;
            rhi::Renderer *__renderer;
        public:
            
            __Impl(void) :
            __window([&](void) -> GLFWwindow * {
                glfwInit();
                // FIXME : see if safe to put 4.5 instead
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                logger::info << "Creating window" << std::endl;
                GLFWwindow *window = glfwCreateWindow(1280, 720, "PUT THE GAME NAME HERE", NULL, NULL);
                if (window == nullptr) {
                    logger::fatal << "Failed to create window" << std::endl;
                }
                glfwMakeContextCurrent(window);
                return window;
            }()),
            __renderer([&](void) -> rhi::Renderer * {
                rhi::Renderer::init();
                return rhi::Renderer::get();
            }())
            {
            }
            
            ~__Impl() {
                glfwTerminate();
                this->__renderer->destroy();
            }

            int run(void) {
                while (glfwWindowShouldClose(this->__window) == false) {
                    glfwPollEvents();
                    this->__renderer->draw();
                    glfwSwapBuffers(this->__window);
                }
                return 0;
            }
    };

    Engine::Engine(void) :
    __impl(std::make_unique<__Impl>())
    {

    }

    Engine::~Engine() = default;

    int Engine::run(void) { return this->__impl->run(); }
} // namespace host
