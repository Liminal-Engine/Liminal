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
#include <random>

namespace host {
    class Application::__Impl {
        private:

        public:
            __Impl() {}
            ~__Impl() {}

            Status init(void) const {
                // 1. Load resources
                gfx::load(gfx::ResourceType::MESH, fs::Path("assets/meshes/toto.obj"));
                gfx::load(gfx::ResourceType::SHADER, fs::Path("assets/shaders/core/textured.glsl"));

                entity::bundle::Object myFamousTriangle = entity::Registry::add<entity::bundle::Object>();
                myFamousTriangle.geometry.meshHandle = gfx::getHandle("assets/meshes/toto.obj");
                myFamousTriangle.material.color.x = 0.090f;

                entity::bundle::Camera myCamera = entity::Registry::add<entity::bundle::Camera>();
                myCamera.transfom.translate(math::Axis::FRONT, 2.0f);
                
                return Status::OK;
            }

            void update(float deltaTime) {
                auto view = entity::Registry::getRaw().view<
                entity::component::tag::Object,
                entity::component::Transform,
                entity::component::Material
            >();
            for (auto entity : view) {
                auto &transform = view.get<entity::component::Transform>(entity);
                auto &material = view.get<entity::component::Material>(entity);
                if (material.color.x >= 0.0f && material.color.x <= 1.0f) material.color.x += 0.0005f;
                else material.color.x = 0.0f;

                if (material.color.y >= 0.0f && material.color.y <= 1.0f) material.color.y += 0.001f;
                else material.color.y = 0.0f;

                if (material.color.z >= 0.0f && material.color.z <= 1.0f) material.color.z += 0.0007f;
                else material.color.z = 0.0f;

                // transform.rotate(math::Axis::SIDE, math::Angle::Degrees(1.0f));
                transform.rotate(math::Axis::UP, math::Angle::Degrees(1.0f));
                transform.rotate(math::Axis::SIDE, math::Angle::Degrees(1.0f));
                transform.rotate(math::Axis::FRONT, math::Angle::Degrees(1.0f));
            }
                // // FIXME : this should be a system
                // auto view = entity::Registry::getRaw().view<
                //     entity::component::tag::Camera,
                //     entity::component::Transform,
                //     entity::component::CameraSettings
                // >();
                // for (auto &camera : view) {
                //     auto &transform = view.get<entity::component::Transform>(camera);
                //     auto &settings = view.get<entity::component::CameraSettings>(camera);
                    
                //     // Gram-Schmidt compute
                //     settings.direction = glm::normalize(settings.target - transform.position);
                //     settings.right = glm::normalize(glm::cross(settings.up, settings.direction));
                //     settings.up = glm::cross(settings.direction, settings.right);
                //     settings.viewMatrix = glm::lookAt(transform.position, transform.position + settings.direction, settings.up);
                //     // FIXME : compute only if settings changed and maybe init in constructor
                //     float aspectRatio = settings.aspectRatio.width / settings.aspectRatio.height;
                //     settings.projectionMatrix = glm::perspective(settings.FOV.getValue(), aspectRatio, settings.nearPlane, settings.farPlane);
                // }
            }
    };

    Application::Application(void) : __impl(std::make_unique<__Impl>()) {}
    Application::~Application() = default;

    Status Application::init(void) const { return this->__impl->init(); }
    void Application::update(float deltaTime) { this->__impl->update(deltaTime); }
} // namespace host
