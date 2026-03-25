#include "Engine.hpp"

#include <wsi/Window.hpp>
#include <logger/logger.hpp>
#include <entity/Registry.hpp>
#include <rhi/Context.hpp>
#include <gfx/Renderer.hpp>

#include <GLFW/glfw3.h>

namespace host {
    class Engine::__Impl {
        private:
            wsi::Window __window;
            Application &__application;
            rhi::Context __rhiContext;
            std::unique_ptr<gfx::Renderer> __renderer;

        public:
            
            __Impl(Application &application) :
            __window(1280, 720, "PUT THE GAME NAME HERE"),
            __application(application),
            __rhiContext(),
            __renderer(nullptr)
            {
                if (rhi::Status status; (status = this->__rhiContext.init()) != rhi::Status::OK) {
                    logger::fatal << "RHI context initialization failed, status=" << rhi::toStr(status) << std::endl;
                    return; // FIXME: maybe should throw and exit properly here
                }
                this->__renderer = std::make_unique<gfx::Renderer>(this->__rhiContext);
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
                    this->__application.update(0.0f);
                    this->__renderer->draw();
                    this->__window.display();
                }
                return 0;
            }
    };

    Engine::Engine(Application &application) :
    __impl(std::make_unique<__Impl>(application))
    {

    }

    Engine::~Engine() = default;

    int Engine::run(void) { return this->__impl->run(); }
} // namespace host
