#include "system/Camera.hpp"
#include "component/tag/Active.hpp"

#include <entity/Registry.hpp>
#include <logger/logger.hpp>

namespace entity {
    namespace system {

        class Camera::__Impl {
            private:

            public:
                static entity::bundle::Camera getActiveCamera(void) {
                    // 1. Find active camera
                    auto &rawRegistry = entity::Registry::getRaw();
                    auto view = rawRegistry.view<
                        entity::component::tag::Camera,
                        entity::component::tag::Active,
                        entity::component::Transform,
                        entity::component::CameraSettings
                    >();
                    // 2. Check whether exactly one camera is activated
                    size_t size(view.size_hint());
                    if (size != 1) {
                        logger::error << "Invalid number of active camera: " << size << std::endl;
                        return entity::bundle::Camera::Null();
                    }
                    entt::entity id = *view.begin();
                    return entity::bundle::Camera(
                        id,
                        view.get<component::Transform>(id),
                        view.get<component::CameraSettings>(id)
                    );
                }
        };


        void Camera::update(void) {
            auto view = entity::Registry::getRaw().view<
                entity::component::tag::Camera,
                entity::component::Transform,
                entity::component::CameraSettings
            >();
            for (auto id : view) {
                auto &transform = view.get<entity::component::Transform>(id);
                auto &cameraSettings = view.get<entity::component::CameraSettings>(id);
                cameraSettings.update(transform);
            }
        }
        
        void Camera::activate(entt::entity id) {
            // 1. Check given id
            auto &rawRegistry = entity::Registry::getRaw();
            if (
                rawRegistry.valid(id) == false ||
                rawRegistry.all_of<entity::component::tag::Camera>(id) == false
            ) {
                logger::error << "Failed to activate camera, ID not found: " << (uint32_t)id << std::endl;
                return;
            }
            // 2. Remove active tag from all activated cameras (only one camera activated at a time)
            auto view = rawRegistry.view<
                entity::component::tag::Camera,
                entity::component::tag::Active
            >();
            for (auto &cameraId : view) {
                rawRegistry.remove<entity::component::tag::Active>(cameraId);
            }
            // 3. Add active tag to desired camera
            rawRegistry.emplace_or_replace<entity::component::tag::Active>(id);
        }

        void Camera::translate(math::Axis axis, float delta) {
            entity::bundle::Camera camera(__Impl::getActiveCamera());
            if (camera.isNull()) {
                logger::error << "Active camera not found, cannot apply translation" << std::endl;
                return;
            }
            camera.transform.translate(axis, delta);
        }

        void Camera::rotate(math::Axis axis, const math::Angle &angle) {
            entity::bundle::Camera camera(__Impl::getActiveCamera());
            if (camera.isNull()) {
                logger::error << "Active camera not found, cannot apply translation" << std::endl;
                return;
            }
            camera.transform.rotate(axis, angle);
        }
    } // namespace system
} // namespace entity
