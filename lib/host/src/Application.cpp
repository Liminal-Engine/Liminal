#include "Application.hpp"

#include <logger/logger.hpp>
#include <fs/Path.hpp>
#include <entity/AEntity.hpp>
#include <entity/Registry.hpp>
#include <gfx/gfx.hpp>

#include <vector>

namespace host {
    class Application::__Impl {
        private:

        public:
            __Impl() {}
            ~__Impl() {}

            Status init(void) const {
                // 1. Load resources
                gfx::load(gfx::ResourceType::MESH, fs::Path("asset/meshes/toto.obj"));
                gfx::load(gfx::ResourceType::SHADER, fs::Path("assets/shaders/core/textured.glsl"));

                // 2. Create entities and add them to entity registry
                entity::AEntity entity(gfx::getHandle("asset/meshes/toto.obj"));                
                entity.material.setColor(glm::vec3(0.090, 0.137, 0.639));
                entity::Registry::add(std::move(entity));
                
                return Status::OK;
            }
    };

    Application::Application(void) : __impl(std::make_unique<__Impl>()) {}
    Application::~Application() = default;

    Status Application::init(void) const { return this->__impl->init(); }
} // namespace host
