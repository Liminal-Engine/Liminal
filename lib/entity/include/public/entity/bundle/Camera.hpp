#ifndef __LIMINAL__LIB__ENTITY__BUNDLE__CAMERA_HPP__
#define __LIMINAL__LIB__ENTITY__BUNDLE__CAMERA_HPP__

#include "entity/component/Transform.hpp"
#include "entity/component/CameraSettings.hpp"
#include "entity/component/tag/Camera.hpp"

#include <entt/entt.hpp>

namespace entity {
    namespace bundle {
        struct Camera {
            Camera(
                component::Transform &transfom,
                component::CameraSettings &settings
            );

            entt::entity id;
            component::Transform &transfom;
            component::CameraSettings &settings;
            component::tag::Camera cameraTag;
        };
    } // namespace bundle
} // namespace entity

#endif // __LIMINAL__LIB__ENTITY__BUNDLE__CAMERA_HPP__