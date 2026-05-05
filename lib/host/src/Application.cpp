#include "Application.hpp"

#include <logger/logger.hpp>
#include <fs/Path.hpp>
#include <entity/Object.hpp>
#include <entity/Registry.hpp>
#include <gfx/gfx.hpp>
#include <entity/component/Transform.hpp>
#include <entity/component/Geometry.hpp>
#include <entity/component/Material.hpp>
#include <entity/system/Camera.hpp>
#include <leh/EventHandler.hpp>


#include <entt/entt.hpp>

#include <vector>
#include <functional>
#include <random>

namespace host {
    class Application::__Impl {
        private:

        public:
            __Impl() {}
            ~__Impl() {}

            Status init(void) const {
                // 1. Load resources
                gfx::load(gfx::def::ResourceType::MESH, fs::Path("assets/meshes/toto.obj"));
                gfx::load(gfx::def::ResourceType::SHADER, fs::Path("assets/shaders/core/textured.glsl"));
                gfx::load(gfx::def::ResourceType::SHADER, fs::Path("assets/shaders/debug/wireframe.glsl"));

                entity::bundle::Object myFamousTriangle = entity::Registry::add<entity::bundle::Object>();
                myFamousTriangle.geometry.meshHandle = gfx::getHandle("assets/meshes/toto.obj");
                myFamousTriangle.material.color.x = 0.090f;

                entity::bundle::Camera myCamera = entity::Registry::add<entity::bundle::Camera>();
                myCamera.transform.translate(math::Axis::FRONT, 5.0f);
                myCamera.transform.setOrientation(glm::vec3(0.0f, -glm::half_pi<float>(), 0.0f));
                entity::system::Camera::activate(myCamera.id);

                wsi::KeyboardEvent keyboardEvent;
                keyboardEvent.key = wsi::Key::D;
                keyboardEvent.status = wsi::KeyStatus::PRESSED;      
                keyboardEvent.mod.num = true;          
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::translate(math::Axis::SIDE, 0.2f); }); // fixme, remove delta ans use translation and rotation speed instead, and use deltaTime also
                keyboardEvent.key = wsi::Key::Q;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::translate(math::Axis::SIDE, -0.2f); });
                keyboardEvent.key = wsi::Key::Z;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::translate(math::Axis::FRONT, -0.2f); });
                keyboardEvent.key = wsi::Key::S;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::translate(math::Axis::FRONT, 0.2f); });
                keyboardEvent.key = wsi::Key::R;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::translate(math::Axis::UP, 0.2f); });
                keyboardEvent.key = wsi::Key::F;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::translate(math::Axis::UP, -0.2f); });
                keyboardEvent.key = wsi::Key::ARROW_RIGHT;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::rotate(math::Axis::UP, math::Angle::Degrees(5.0f)); });
                keyboardEvent.key = wsi::Key::ARROW_LEFT;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::rotate(math::Axis::UP, math::Angle::Degrees(-5.0f)); });
                keyboardEvent.key = wsi::Key::ARROW_UP;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::rotate(math::Axis::SIDE, math::Angle::Degrees(5.0f)); });
                keyboardEvent.key = wsi::Key::ARROW_DOWN;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::rotate(math::Axis::SIDE, math::Angle::Degrees(-5.0f)); });
                keyboardEvent.key = wsi::Key::M;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::rotate(math::Axis::FRONT, math::Angle::Degrees(5.0f)); });
                keyboardEvent.key = wsi::Key::L;
                leh::EventHandler::add(keyboardEvent, []() { entity::system::Camera::rotate(math::Axis::FRONT, math::Angle::Degrees(-5.0f)); });
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
        }
    };

    Application::Application(void) : __impl(std::make_unique<__Impl>()) {}
    Application::~Application() = default;

    Status Application::init(void) const { return this->__impl->init(); }
    void Application::update(float deltaTime) { this->__impl->update(deltaTime); }
} // namespace host
