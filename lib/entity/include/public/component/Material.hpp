#ifndef __LIMINAL__LIB__ENTITY__COMPONENT__MATERIAL_HPP__
#define __LIMINAL__LIB__ENTITY__COMPONENT__MATERIAL_HPP__

#include <memory>

#include <glm/glm.hpp>

namespace entity {
    namespace component {
        class Material {
            public:
                Material(void);
                ~Material();
                Material(const Material &) = delete;
                Material &operator=(const Material &) = delete;
                Material(Material &&other) noexcept;
                Material &operator=(Material &&other) noexcept;
                
                void setColor(const glm::vec3 &color);
                const glm::vec3 &getColor(void) const;

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace component
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__COMPONENT__MATERIAL_HPP__