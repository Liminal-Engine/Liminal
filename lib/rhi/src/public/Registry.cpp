#include "Registry.hpp"
#include "__private/__registry/__Shader.hpp"
#include "__private/__registry/__Texture.hpp"
#include "__private/__registry/__Mesh.hpp"

#include <logger/logger.hpp>

namespace rhi {
    class Registry::__Impl {
        private:
            __private::__registry::__Shader __shaderRegistry;
            __private::__registry::__Texture __textureRegistry;
            __private::__registry::__Mesh __meshRegistry;

        public:
            __Impl(void) {

            }

            ~__Impl() = default;
            
            const def::Handle getShaderHandle(const std::string &name) const {
                return this->__shaderRegistry.getHandle(name);
            }
            
            const def::Handle getTextureHandle(const std::string &name) const {
                return this->__textureRegistry.getHandle(name);
            }

            const def::Handle getMeshHandle(const std::string &name) const {
                return this->__meshRegistry.getHandle(name);
            }


            const resource::Shader *getShaderResource(def::Handle handle) const {
                return this->__shaderRegistry.getResource(handle);
            }

            const resource::Texture *getTextureResource(def::Handle handle) const {
                return this->__textureRegistry.getResource(handle);
            }

            const resource::Mesh *getMeshResource(def::Handle handle) const {
                return this->__meshRegistry.getResource(handle);
            }


            Status addMesh(                
                const std::string &name,
                const std::vector<def::Vertex> &vertices,
                const std::vector<uint32_t> indices
            ) {
                return this->__meshRegistry.add(name, vertices, indices);
            }

            Status addTexture(const std::string &name, const unsigned char* data, const glm::ivec2 &size, const int &nChannels) {
                return this->__textureRegistry.add(name, data, size, nChannels);
            }

            Status addShader(
                const std::string name,
                const std::string &vertexSource,
                const std::string &geometrySource,
                const std::string &fragmentSource,
                const std::string &computeSource
            ) {
                return this->__shaderRegistry.add(name, vertexSource, geometrySource, fragmentSource, computeSource);
            }
    };

    Registry::Registry(void) :
    __impl(std::make_unique<__Impl>())
    {}

    Registry::~Registry() = default;

    const def::Handle Registry::getShaderHandle(const std::string &name) const { return this->__impl->getShaderHandle(name); }
    const def::Handle Registry::getTextureHandle(const std::string &name) const { return this->__impl->getTextureHandle(name); }
    const def::Handle Registry::getMeshHandle(const std::string &name) const { return this->__impl->getMeshHandle(name); }
    const resource::Shader *Registry::getShaderResource(def::Handle handle) const { return this->__impl->getShaderResource(handle); }
    const resource::Texture *Registry::getTextureResource(def::Handle handle) const { return this->__impl->getTextureResource(handle); }
    const resource::Mesh *Registry::getMeshResource(def::Handle handle) const { return this->__impl->getMeshResource(handle); }
    Status Registry::addMesh(const std::string &name, const std::vector<def::Vertex> &vertices, const std::vector<uint32_t> indices) { return this->__impl->addMesh(name, vertices, indices); }
    Status Registry::addTexture(const std::string &name, const unsigned char* data, const glm::ivec2 &size, const int &nChannels) { return this->__impl->addTexture(name, data, size, nChannels); }
    Status Registry::addShader(const std::string name, const std::string &vertexSource, const std::string &geometrySource, const std::string &fragmentSource, const std::string &computeSource) { return this->__impl->addShader(name, vertexSource, geometrySource, fragmentSource, computeSource); }
} // namespace rhi
