#include "asset/Material.hpp"
#include "__private/__asset/__Shader.hpp"
#include "__private/__asset/__Texture.hpp"

#include <glm/glm.hpp>

#include <string>

namespace gfx {
    namespace asset {
        class Material::__Impl {
            private:
            
                std::unique_ptr<__private::__asset::__Shader> __shader; // pointer because can be null before initialized
                std::unique_ptr<__private::__asset::__Texture> __texture; // pointer because can be null if no texture is applied
                glm::vec3 __color;
                std::string __resourceKey;

            public:
                __Impl(void) :
                __shader(std::make_unique<__private::__asset::__Shader>()),
                __texture(std::make_unique<__private::__asset::__Texture>()),
                __color(0.0f),
                __resourceKey("")
                {

                }

                Status setColor(const glm::vec3 &color) {
                    this->__color = color;
                    return Status::OK;
                }

                const std::string &getRessourceKey(void) const { return this->__resourceKey; }

                Status copy(const __Impl &other) {
                    this->__shader->copy(*other.__shader);
                    this->__texture->copy(*other.__texture);
                    this->__color = other.__color;
                    this->__resourceKey = other.__resourceKey;
                    return Status::OK;
                }

                Status load(const fs::Path &texturePath) {
                    this->__texture->load(texturePath);
                    this->__shader->load(fs::Path("/home/matteo/Projects/Liminal/assets/shaders/core/textured.glsl")); //  FIXME: this is one of the place where shader selection should happen, should be someting like "default.glsl" by default
                    return Status::OK;
                }

                const unsigned char *getTextureData(void) const { return this->__texture->getData(); }
                const glm::ivec2 &getTextureSize(void) const { return this->__texture->getSize(); }
                const int &getTextureNChannels(void) const { return this->__texture->getNChannels(); }

                Status setTextureRHIHandle(const rhi::def::Handle &RHIHandle) {
                    return this->__texture->setRHIHandle(RHIHandle);
                }

                Status setShaderRHIHandle(const rhi::def::Handle &RHIHandle) {
                    return this->__shader->setRHIHandle(RHIHandle);
                }

                rhi::def::Handle getTextureRHIHandle(void) const { return this->__texture->getRHIHandle(); }
                rhi::def::Handle getShaderRHIHandle(void) const { return this->__shader->getRHIHandle(); }

                const std::string &getShaderVertexSource(void) const { return this->__shader->getVertexSource(); }
                const std::string &getShaderGeometrySource(void) const { return this->__shader->getGeometrySource(); }
                const std::string &getShaderFragmentSource(void) const { return this->__shader->getFragmentSource(); }
                const std::string &getShaderComputeSource(void) const { return this->__shader->getComputeSource(); }
        };

        Material::Material(void) :
        __impl(std::make_unique<__Impl>())
        {}

        Material::~Material() = default;

        Material::Material(Material &&) noexcept = default;

        Material &Material::operator=(Material &&) noexcept = default;

        Status Material::setColor(const glm::vec3 &color) { return this->__impl->setColor(color); }

        const std::string &Material::getRessourceKey(void) const { return this->__impl->getRessourceKey(); }

        Status Material::copy(const Material &other) { return this->__impl->copy(*other.__impl); }

        Status Material::load(const fs::Path &texturePath) { return this->__impl->load(texturePath); }

        const unsigned char *Material::getTextureData(void) const { return this->__impl->getTextureData(); }
        const glm::ivec2 &Material::getTextureSize(void) const { return this->__impl->getTextureSize(); }
        const int &Material::getTextureNChannels(void) const { return this->__impl->getTextureNChannels(); }

        Status Material::setTextureRHIHandle(const rhi::def::Handle &RHIHandle) { return this->__impl->setTextureRHIHandle(RHIHandle); }
        Status Material::setShaderRHIHandle(const rhi::def::Handle &RHIHandle) { return this->__impl->setShaderRHIHandle(RHIHandle); }
        rhi::def::Handle Material::getTextureRHIHandle(void) const { return this->__impl->getTextureRHIHandle(); }
        rhi::def::Handle Material::getShaderRHIHandle(void) const { return this->__impl->getShaderRHIHandle(); }

        const std::string &Material::getShaderVertexSource(void) const { return this->__impl->getShaderVertexSource(); }
        const std::string &Material::getShaderGeometrySource(void) const { return this->__impl->getShaderGeometrySource(); }
        const std::string &Material::getShaderFragmentSource(void) const { return this->__impl->getShaderFragmentSource(); }
        const std::string &Material::getShaderComputeSource(void) const { return this->__impl->getShaderComputeSource(); }
    } // namespace asset
} // namespace gfx
