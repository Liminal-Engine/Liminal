#include "asset/Material.hpp"
#include "__private/__asset/__Shader.hpp"
#include "__private/__asset/__Texture.hpp"

#include <glm/glm.hpp>

namespace gfx {
    namespace asset {
        class Material::__Impl {
            private:
                __private::__asset::__Shader *__shader; // pointer because can be null before initialized
                __private::__asset::__Texture *__texture; // pointer because can be null if no texture is applied
                glm::vec3 __color;

            public:
                __Impl(void) :
                __shader(nullptr),
                __texture(nullptr),
                __color(0.0f)
                {

                }

                Status setColor(const glm::vec3 &color) {
                    this->__color = color;
                    return Status::OK;
                }
        };

        Material::Material(void) :
        __impl(std::make_unique<__Impl>())
        {}

        Material::~Material() = default;

        Material::Material(Material &&) noexcept = default;

        Material &Material::operator=(Material &&) noexcept = default;

        Status Material::setColor(const glm::vec3 &color) { return this->__impl->setColor(color); }
    } // namespace asset
} // namespace gfx
