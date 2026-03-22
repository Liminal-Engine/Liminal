#include "component/Material.hpp"

namespace entity {
    namespace component {
        class Material::__Impl {
            private:
                glm::vec3 __color;

            public:
                __Impl(void) :
                __color(1.0f)
                {}

                ~__Impl() = default;

                void setColor(const glm::vec3 &color) { this->__color = color; }
                const glm::vec3 &getColor(void) const { return this->__color; }
        };

        Material::Material(void) : __impl(std::make_unique<__Impl>()) {}
        Material::Material(Material &&other) noexcept = default;
        Material &Material::operator=(Material &&other) noexcept = default;
        Material::~Material() = default;

        void Material::setColor(const glm::vec3 &color) { this->__impl->setColor(color); }
        const glm::vec3 &Material::getColor(void) const { return this->__impl->getColor(); }
    } // namespace component
} // namespace entity
