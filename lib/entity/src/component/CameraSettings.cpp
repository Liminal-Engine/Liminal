#include "component/CameraSettings.hpp"

namespace entity {
    namespace component {
        CameraSettings::AspectRatio::AspectRatio(void) :
        width(16), height(9)
        {}

        CameraSettings::CameraSettings(void) :
        target(0.0f),
        direction(0.0f),
        right(0.0f),
        up(0.0f),
        translationSpeed(1.0f),
        rotationSpeed(0.5f),
        yaw(math::Angle::Degrees(-90.0f)),
        pitch(math::Angle::Degrees(0.0f)),
        roll(math::Angle::Degrees(0.0f)),
        FOV(math::Angle::Degrees(45.0f)),
        aspectRatio(),
        nearPlane(0.1f),
        farPlane(1'000.0f),
        projectionMode(ProjectionMode::PERSPECTTIVE),
        viewMatrix(1.0f),
        projectionMatrix(1.0f)
        {}
    } // namespace component
}