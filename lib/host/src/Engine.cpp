#include "Engine.hpp"

#include <wsi/Window.hpp>
#include <logger/logger.hpp>
#include <entity/Registry.hpp>
#include <rhi/Renderer.hpp>

#include <GLFW/glfw3.h>

namespace host {
    class Engine::__Impl {
        private:
            wsi::Window __window;
            const Application &__application;
            rhi::Renderer __renderer;

        public:
            
            __Impl(const Application &application) :
            __window(1280, 720, "PUT THE GAME NAME HERE"),
            __application(application),
            __renderer()
            {
            }
            
            ~__Impl() {
            
            }

            int run(void) {
                if (this->__application.init() != host::Status::OK) {
                    logger::fatal << "Failed to initialize application" << std::endl;
                    return EXIT_FAILURE;
                }

                while (this->__window.shouldClose() == false) {
                    this->__window.pollEvents();
                    this->__renderer.draw();
                    this->__window.display();
                }
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
