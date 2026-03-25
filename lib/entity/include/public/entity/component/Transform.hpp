#ifndef __LIMINAL__LIB__ENTITY__COMPONENT__TRANSFORM_HPP__
#define __LIMINAL__LIB__ENTITY__COMPONENT__TRANSFORM_HPP__

#include <math/Axis.hpp>
#include <math/Angle.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace entity {
    namespace component {
        struct Transform {
            public:
                Transform(void);

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
                glm::vec3 __position;
                glm::vec3 __orientation;
                glm::vec3 __scale;
                mutable glm::mat4 __model;
                mutable bool __dirty;
            
        };     
    } // namespace component
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__COMPONENT__TRANSFORM_HPP__