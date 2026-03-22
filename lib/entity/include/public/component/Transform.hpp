#ifndef __LIMINAL__ENTITY__COMPONENT__TRANSFORM_HPP__
#define __LIMINAL__ENTITY__COMPONENT__TRANSFORM_HPP__

#include <math/Axis.hpp>
#include <math/Angle.hpp>

#include <glm/glm.hpp>

#include <memory>

namespace entity {
    namespace component {
        class Transform {
            public:
                Transform(void);
                ~Transform();
                Transform(const Transform &) = delete;
                Transform &operator=(const Transform &) = delete;
                Transform(Transform &&other) noexcept;
                Transform &operator=(Transform &&other) noexcept;

                void setPosition(const glm::vec3 &position);
                void setOrientation(const glm::vec3 &orientation);
                void setScale(const glm::vec3 &scale);

                void translate(math::Axis axis, float delta);
                void translate(const glm::vec3 &delta);
                void rotate(math::Axis axis, const math::Angle &angle);
                void rotate(const glm::vec3 &angle);
                void scale(math::Axis axis, float factor);
                void scale(const glm::vec3 &factor);

                const glm::mat4 &getModelMatrix(void) const;
                const glm::vec3 &getPosition(void) const;

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace component
} // namespace entity


#endif // __LIMINAL__ENTITY__COMPONENT__TRANSFORM_HPP__