#include "component/CameraSettings.hpp"

#include <glm/gtc/matrix_transform.hpp>


namespace entity {
    namespace component {
        CameraSettings::AspectRatio::AspectRatio(void) :
        width(16), height(9)
        {}

        float CameraSettings::AspectRatio::getCoefficient(void) const {
            return this->width / this->height;
        }

        CameraSettings::CameraSettings(void) :
        target(0.0f),
        direction(0.0f, 0.0f ,-1.0f),
        right(0.0f),
        up(0.0f, 1.0f, 0.0f),
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
        projectionMatrix(glm::perspective(this->FOV.getValue(), this->aspectRatio.getCoefficient(), this->nearPlane, this->farPlane))
        {}

        void CameraSettings::update(const component::Transform &relatedTransform) { // FIXME: use __dirty instead
            glm::vec3 position(relatedTransform.getPosition());
            glm::vec3 orientation(relatedTransform.getOrientation());

            float yaw = orientation.y; // convention: y = yaw
            float pitch = orientation.x; // convention: x = pitch
            float roll = orientation.z;

            glm::vec3 direction(0.0f);
            direction.x = cos(yaw) * cos(pitch);
            direction.y = sin(pitch);
            direction.z = sin(yaw) * cos(pitch);
            this->direction = glm::normalize(direction);

            // view matrix computation
            // base up vector
            glm::vec3 up(0.0f, 1.0f, 0.0f);
            // right vector
            glm::vec3 right = glm::normalize(glm::cross(this->direction, up));
            // apply roll around direction
            glm::mat4 rollMat = glm::rotate(glm::mat4(1.0f), roll, direction);
            glm::vec3 upRolled = glm::normalize(glm::vec3(rollMat * glm::vec4(up, 0.0f)));
            // direction doit être unitaire et représenter la direction de vue (ex: (0,0,-1))
            // up doit être (0,1,0) sauf cas particulier (caméra inclinée)
            this->viewMatrix = glm::lookAt(position, position + this->direction, upRolled);

            // Optionnel : recalcule la projection si FOV, aspect, near/far ont changé
            this->projectionMatrix = glm::perspective(
                this->FOV.getValue(),
                this->aspectRatio.getCoefficient(),
                this->nearPlane,
                this->farPlane
            );
        }
    } // namespace component
}