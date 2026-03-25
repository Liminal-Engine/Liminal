#include "entity/component/Transform.hpp"

#define __AXIS_MEMBER_REF(axis, vec) \
    ((axis) == math::Axis::SIDE ? (vec).x : \
    (axis) == math::Axis::UP ? (vec).y : \
    (axis) == math::Axis::FRONT ? (vec).z : \
    throw std::invalid_argument("Invalid axis"))

namespace entity {
    namespace component {
        Transform::Transform(void) :
        __position(0.0f), __orientation(0.0f), __scale(1.0f), __model(1.0f), __dirty(true)
        {}

        void Transform::setPosition(const glm::vec3 &position) {
            this->__position = position;
            this->__dirty = true;
        }

        void Transform::setOrientation(const glm::vec3 &orientation) {
            this->__orientation = orientation;
            this->__dirty = true;
        }

        void Transform::setScale(const glm::vec3 &scale) {
            this->__scale = scale;
            this->__dirty = true;
        }

        const glm::mat4 &Transform::getModelMatrix(void) const {
            if (this->__dirty == false) return this->__model;
            
            // 1. Create identity matrix
            this->__model = glm::mat4(1.0f);
            // 2. Translation
            this->__model = glm::translate(this->__model, this->__position);
            // 3. Rotation
            this->__model = glm::rotate(this->__model, this->__orientation.x, glm::vec3(1, 0, 0));
            this->__model = glm::rotate(this->__model, this->__orientation.y, glm::vec3(0, 1, 0));
            this->__model = glm::rotate(this->__model, this->__orientation.z, glm::vec3(0, 0, 1));
            // 4. Scale
            this->__model = glm::scale(this->__model, this->__scale);

            this->__dirty = false;
            return this->__model;
        }

        void Transform::translate(math::Axis axis, float delta) {
            if (axis == math::Axis::ALL) this->__position += delta;
            else __AXIS_MEMBER_REF(axis, this->__position) += delta;
            this->__dirty = true;
        }

        void Transform::translate(const glm::vec3 &delta) {
            this->__position += delta;
            this->__dirty = true;
        }

        void Transform::rotate(math::Axis axis, const math::Angle &angle) {
            if (axis == math::Axis::ALL) this->__orientation += angle.getValue();
            else __AXIS_MEMBER_REF(axis, this->__orientation) += angle.getValue();
            this->__dirty = true;
        }

        void Transform::rotate(const glm::vec3 &angle) {
            this->__orientation += angle;
            this->__dirty = true;
        }

        void Transform::scale(math::Axis axis, float factor) {
            if (axis == math::Axis::ALL) this->__scale *= factor;
            else __AXIS_MEMBER_REF(axis, this->__scale) *= factor;
            this->__dirty = true;
        }

        void Transform::scale(const glm::vec3 &factor) {
            this->__scale *= factor;
            this->__dirty = true;
        }

        const glm::vec3 &Transform::getPosition(void) const { return this->__position; }

    } // namespace component
} // namespace entity
