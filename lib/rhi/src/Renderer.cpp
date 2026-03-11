#include "Renderer.hpp"

#include <logger/logger.hpp>

namespace rhi {

    Renderer *Renderer::__instance = nullptr;

    class Renderer::__Impl {

    };

    void Renderer::init(void) {
        if (__instance != nullptr) {
            logger::error << "Renderer already intialized, nothing to do" << std::endl;
            return;
        }
        __instance = new Renderer();
    }

    void Renderer::destroy(void) {
        if (__instance == nullptr) {
            logger::error << "Renderer not initialized or already destroyed, nothing to do" << std::endl;
            return;
        }
        delete __instance;
        __instance = nullptr;
    }

    Renderer *Renderer::get(void) {
        if (__instance == nullptr) {
            logger::fatal << "Renderer required but not initialized" << std::endl;
        }
        return __instance;
    }

    Renderer::Renderer(void) :
    __impl(std::make_unique<__Impl>())
    {

    }

    Renderer::~Renderer() = default;
} // namespace rhi
