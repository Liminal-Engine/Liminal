#include "component/Transform.hpp"

#include <glm/gtc/matrix_transform.hpp>

#define __AXIS_MEMBER_REF(axis, vec) \
    ((axis) == math::Axis::SIDE ? (vec).x : \
    (axis) == math::Axis::UP ? (vec).y : \
    (axis) == math::Axis::FRONT ? (vec).z : \
    throw std::invalid_argument("Invalid axis"))

namespace entity {
    namespace component {
        class Transform::__Impl {
            private:
                glm::vec3 __position;
                glm::vec3 __orientation;
                glm::vec3 __scale;
                mutable glm::mat4 __model;
                mutable bool __dirty;

            public:
                __Impl(void) :
                __position(0.0f),
                __orientation(0.0f),
                __scale(1.0f),
                __model(1.0f),
                __dirty(true)
                {}

                ~__Impl() = default;

                void setPosition(const glm::vec3 &position) {
                    this->__position = position;
                    this->__dirty = true;
                }

                void setOrientation(const glm::vec3 &orientation) {
                    this->__orientation = orientation;
                    this->__dirty = true;
                }

                void setScale(const glm::vec3 &scale) {
                    this->__scale = scale;
                    this->__dirty = true;
                }

                const glm::mat4 &getModelMatrix(void) const {
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

                void translate(math::Axis axis, float delta) {
                    if (axis == math::Axis::ALL) this->__position += delta;
                    else __AXIS_MEMBER_REF(axis, this->__position) += delta;
                    this->__dirty = true;
                }

                void translate(const glm::vec3 &delta) {
                    this->__position += delta;
                    this->__dirty = true;
                }

                void rotate(math::Axis axis, const math::Angle &angle) {
                    if (axis == math::Axis::ALL) this->__orientation += angle.getValue();
                    else __AXIS_MEMBER_REF(axis, this->__orientation) += angle.getValue();
                    this->__dirty = true;
                }

                void rotate(const glm::vec3 &angle) {
                    this->__orientation += angle;
                    this->__dirty = true;
                }

                void scale(math::Axis axis, float factor) {
                    if (axis == math::Axis::ALL) this->__scale *= factor;
                    else __AXIS_MEMBER_REF(axis, this->__scale) *= factor;
                    this->__dirty = true;
                }

                void scale(const glm::vec3 &factor) {
                    this->__scale *= factor;
                    this->__dirty = true;
                }

                const glm::vec3 &getPosition(void) const { return this->__position; }
        };

        Transform::Transform(void) : __impl(std::make_unique<__Impl>()) {}
        Transform::~Transform() = default;
        Transform::Transform(Transform &&other) noexcept = default;
        Transform &Transform::operator=(Transform &&other) noexcept = default;

        void Transform::setPosition(const glm::vec3 &position) { this->__impl->setPosition(position); }
        void Transform::setOrientation(const glm::vec3 &orientation) { this->__impl->setOrientation(orientation); }
        void Transform::setScale(const glm::vec3 &scale) { this->__impl->setScale(scale); }
        void Transform::translate(math::Axis axis, float delta) { this->__impl->translate(axis, delta); }
        void Transform::translate(const glm::vec3 &delta) { this->__impl->translate(delta); }
        void Transform::rotate(math::Axis axis, const math::Angle &angle) { this->__impl->rotate(axis, angle); }
        void Transform::rotate(const glm::vec3 &angle) { this->__impl->rotate(angle); }
        void Transform::scale(math::Axis axis, float factor) { this->__impl->scale(axis, factor); }
        void Transform::scale(const glm::vec3 &factor) { this->__impl->scale(factor); }
        const glm::mat4 &Transform::getModelMatrix(void) const { return this->__impl->getModelMatrix(); }
        const glm::vec3 &Transform::getPosition(void) const { return this->__impl->getPosition(); }
    } // namespace component
} // namespace entity
