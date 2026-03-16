#include "Engine.hpp"

#include <wsi/Window.hpp>
#include <rhi/Renderer.hpp>
#include <rhi/Registry.hpp>
#include <gfx/Registry.hpp>
#include <logger/logger.hpp>
#include <entity/Registry.hpp>

#include <GLFW/glfw3.h>

namespace host {
    class Engine::__Impl {
        private:
            wsi::Window __window;
            // GLFWwindow *__window;
            rhi::Registry __RHIRegistry;
            gfx::Registry __assetRegistry;
            entity::Registry __entityRegistry;
            const Application &__application;
            rhi::Renderer *__renderer;

        public:
            
            __Impl(const Application &application) :
            __window(1280, 720, "PUT THE GAME NAME HERE"),
            // __window([&](void) -> GLFWwindow * {
            //     glfwInit();
            //     // FIXME : see if safe to put 4.5 instead
            //     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            //     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            //     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            //     logger::info << "Creating window" << std::endl;
            //     GLFWwindow *window = glfwCreateWindow(1280, 720, "PUT THE GAME NAME HERE", NULL, NULL);
            //     if (window == nullptr) {
            //         logger::fatal << "Failed to create window" << std::endl;
            //     }
            //     glfwMakeContextCurrent(window);
            //     return window;
            // }()),
            __RHIRegistry(),
            __assetRegistry(this->__RHIRegistry),
            __entityRegistry(),
            __application(application),
            __renderer([&](void) -> rhi::Renderer * {
                rhi::Renderer::init(this->__RHIRegistry);
                return rhi::Renderer::get();
            }())
            {
                // this->__resourceRegistry.init();
            }
            
            ~__Impl() {
                if (rhi::Status rhiStatus; (rhiStatus = this->__RHIRegistry.destroy()) != rhi::Status::OK) {
                    logger::error << "Failed to destroy RHI registry" << std::endl;
                }
                rhi::Renderer::destroy();
                // glfwDestroyWindow(this->__window);
                glfwTerminate();
            }

            int run(void) {
                if (this->__application.init(this->__assetRegistry, this->__entityRegistry) != host::Status::OK) {
                    logger::fatal << "Failed to initialize application" << std::endl;
                    return EXIT_FAILURE;
                }

                while (this->__window.shouldClose() == false) {
                    this->__window.pollEvents();
                    this->__renderer->draw(this->__entityRegistry);
                    this->__window.display();
                }
                // while (glfwWindowShouldClose(this->__window) == false) {
                //     glfwPollEvents();
                //     this->__renderer->draw(this->__entityRegistry);
                //     glfwSwapBuffers(this->__window);
                // }
                return 0;
            }
    };

    Engine::Engine(const Application &application) :
    __impl(std::make_unique<__Impl>(application))
    {

    }

    Engine::~Engine() = default;

    int Engine::run(void) { return this->__impl->run(); }
} // namespace host
