#include "asset/Material.hpp"
#include "__private/__asset/__Shader.hpp"
#include "__private/__asset/__Texture.hpp"

#include <jsonio/InJson.hpp>
#include <logger/logger.hpp>
#include <fs/Path.hpp>

#include <glm/glm.hpp>

#include <string>
#include <algorithm>

namespace gfx
{
    namespace asset
    {
        class Material::__Impl
        {
        private:
            static glm::vec3 __parseColor(const jsonio::InJson &jsonFile)
            {
                std::optional<jsonio::types::Any_t> optional(std::nullopt);
                optional = jsonFile.get<jsonio::types::Array_t>("properties.color");
                if (
                    jsonFile.getType("properties.color") != jsonio::types::ValueTypes::ARRAY ||
                    optional.has_value() == false)
                {
                    logger::error << "No valid color specified in material file. Selecting default color" << std::endl;
                    return glm::vec3(1.0f);
                }
                optional = jsonFile.get<jsonio::types::Array_t>("properties.color");
                jsonio::types::Array_t colorArray = std::get<jsonio::types::Array_t>(optional.value());
                if (colorArray.getLen() != 3 || colorArray.hasNestedContainers() == true)
                {
                    logger::error << "Invalid color array format for material file. Selecting default color" << std::endl;
                    return glm::vec3(1.0f);
                }
                float localColors[3] = {1.0f, 1.0f, 1.0f};
                for (size_t i = 0; i < 3; i++) {
                    optional = colorArray.get<jsonio::types::FloatNum_t>(i);
                    if (optional.has_value() == false) {
                        logger::error << "Invalid color array formating. Selecting default color" << std::endl;
                        return glm::vec3(1.0f);
                    }                    
                    localColors[i] =  std::get<jsonio::types::FloatNum_t>(optional.value());
                }
                return glm::vec3(localColors[0], localColors[1], localColors[2]);
            }

            __private::__asset::__Shader *__shader;   // pointer because can be null before initialized
            __private::__asset::__Texture *__texture; // pointer because can be null if no texture is applied
            glm::vec3 __color;
            bool __mustHaveTexture;
            fs::Path __texturePath;
            fs::Path __path;

        public:
            __Impl(void) : 
            __shader(nullptr),
            __texture(nullptr),
            __color(0.0f),
            __mustHaveTexture(false),
            __texturePath(),
            __path()
            {
            }

            Status copy(const __Impl &other)
            {
                this->__shader = other.__shader;
                this->__texture = other.__texture;
                this->__color = other.__color;
                this->__mustHaveTexture = other.__mustHaveTexture;
                this->__texturePath = other.__texturePath;
                this->__path = other.__path;
                return Status::OK;
            }

            Status load(const fs::Path &path)
            { // Here, we only setup the file info struct and the properties
                // 0. Set path
                this->__path = path;
                // 1. Open and parse json file
                jsonio::InJson file;
                if (jsonio::Status jsonioStatus = jsonio::Status::OK; (jsonioStatus = file.parse(path)) != jsonio::Status::OK)
                {
                    logger::error << "Failed to parse json file:" << path.asStr() << "error: " << jsonio::toStr(jsonioStatus) << std::endl;
                    return Status::E_FILE_CONTENT;
                }
                // 2. Get texture info, if it has one
                std::optional<jsonio::types::Any_t> optional(std::nullopt);
                if (file.getType("texture") == jsonio::types::ValueTypes::NULL_VALUE)
                {
                    logger::debug << "Material has no texture to laod: " << path.asStr() << std::endl;
                    this->__mustHaveTexture = false;
                    this->__texturePath = fs::Path();
                }
                else
                {
                    optional = file.get<jsonio::types::String_t>("texture.path");
                    if (optional.has_value() == false)
                    {
                        logger::error << "Material shoudl have a texture but no path specified: " << path.asStr() << std::endl;
                        return Status::E_FILE_CONTENT;
                    }
                    this->__mustHaveTexture = true;
                    this->__texturePath = fs::Path(std::get<jsonio::types::String_t>(optional.value()));
                }
                // 3. Properties
                this->__color = __parseColor(file);
                return Status::OK;
            }

            const unsigned char *getTextureData(void) const { return this->__texture->getData(); }
            const glm::ivec2 &getTextureSize(void) const { return this->__texture->getSize(); }
            int getTextureNChannels(void) const { return this->__texture->getNChannels(); }
            const fs::Path &getPath(void) const { return this->__path; }

            bool mustHaveTexture(void) const { return this->__mustHaveTexture; }
            const fs::Path &getTexturePath(void) const { return this->__texturePath; }

           

            rhi::def::Handle getTextureRHIHandle(void) const { return this->__texture->getRHIHandle(); }
            rhi::def::Handle getShaderRHIHandle(void) const { return this->__shader->getRHIHandle(); }

            void bind(__private::__asset::__Texture *texture, __private::__asset::__Shader *shader) {
                if (texture == nullptr) logger::debug << "Setting material texture to NULL" << std::endl;
                if (shader ==nullptr) logger::error << "Setting material shader to NULL" << std::endl;
                this->__texture = texture;
                this->__shader = shader;
            }

            const std::vector<rhi::def::Uniform> &apply(void) const {
                this->__shader->set("uColor", this->__color);

                return this->__shader->getUniforms();
            }
        };

        Material::Material(void) : __impl(std::make_unique<__Impl>())
        {
        }

        Material::~Material() = default;

        Material::Material(Material &&) noexcept = default;

        Material &Material::operator=(Material &&) noexcept = default;

        Status Material::copy(const Material &other) { return this->__impl->copy(*other.__impl); }

        Status Material::load(const fs::Path &path) { return this->__impl->load(path); }

        const unsigned char *Material::getTextureData(void) const { return this->__impl->getTextureData(); }
        const glm::ivec2 &Material::getTextureSize(void) const { return this->__impl->getTextureSize(); }
        int Material::getTextureNChannels(void) const { return this->__impl->getTextureNChannels(); }

        rhi::def::Handle Material::getTextureRHIHandle(void) const { return this->__impl->getTextureRHIHandle(); }
        rhi::def::Handle Material::getShaderRHIHandle(void) const { return this->__impl->getShaderRHIHandle(); }
        const fs::Path &Material::getPath(void) const { return this->__impl->getPath(); }

        bool Material::mustHaveTexture(void) const { return this->__impl->mustHaveTexture(); }
        const fs::Path &Material::getTexturePath(void) const { return this->__impl->getTexturePath(); }

        void Material::bind(__private::__asset::__Texture *texture, __private::__asset::__Shader *shader) { this->__impl->bind(texture, shader); }

        const std::vector<rhi::def::Uniform> &Material::apply(void) const  { return this->__impl->apply(); }

    } // namespace asset
} // namespace gfx
