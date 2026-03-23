#include "Application.hpp"

#include <logger/logger.hpp>
#include <fs/Path.hpp>
#include <entity/Object.hpp>
#include <entity/Registry.hpp>
#include <gfx/gfx.hpp>
#include <entity/component/Transform.hpp>
#include <entity/component/Geometry.hpp>
#include <entity/component/Material.hpp>

#include <vector>

#include <entt/entt.hpp>

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

                entity::bundle::Object myFamousTriangle = entity::Registry::add<entity::bundle::Object>();
                myFamousTriangle.geometry.meshHandle = gfx::getHandle("asset/meshes/toto.obj");
                myFamousTriangle.material.color.x = 0.090f;                               
                
                return Status::OK;
            }
    };

    Application::Application(void) : __impl(std::make_unique<__Impl>()) {}
    Application::~Application() = default;

    Status Application::init(void) const { return this->__impl->init(); }
} // namespace host
