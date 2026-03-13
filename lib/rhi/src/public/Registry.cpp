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
            
            Status init(void) {
                Status tmpStatus = Status::OK;

                if ((tmpStatus = this->__meshRegistry.init()) != Status::OK) {
                    logger::error << "Failed to initialize mesh registry" << std::endl;
                    return tmpStatus;
                }
                if ((tmpStatus = this->__textureRegistry.init()) != Status::OK) {
                    logger::error << "Failed to initialize texture registry" << std::endl;
                    return tmpStatus;
                }
                if ((tmpStatus = this->__shaderRegistry.init()) != Status::OK) {
                    logger::error << "Failed to initialize shader registry" << std::endl;
                    return tmpStatus;
                }
                return Status::OK;
            }

            Status destroy(void) {
                logger::debug << "Destroying RHI registries" << std::endl;
                Status tmpStatus = Status::OK;
                if ((tmpStatus = this->__meshRegistry.destroy()) != Status::OK) {
                    logger::error << "Failed to destroy mesh registry" << std::endl;
                    return tmpStatus;
                }
                if ((tmpStatus = this->__textureRegistry.destroy()) != Status::OK) {
                    logger::error << "Failed to destroy texture registry" << std::endl;
                    return tmpStatus;
                }
                if ((tmpStatus = this->__shaderRegistry.destroy()) != Status::OK) {
                    logger::error << "Failed to destroy shader registry" << std::endl;
                    return tmpStatus;
                }
                return Status::OK;
            }

            const resource::Shader *getShader(const std::string &name) const {
                return this->__shaderRegistry.get(name);
            }
            
            const resource::Texture *getTexture(const std::string &name) const {
                return this->__textureRegistry.get(name);
            }

            const resource::Mesh *getMesh(const std::string &name) const {
                return this->__meshRegistry.get(name);
            }

            Status addMesh(                
                const std::string &name,
                const std::vector<resource::Vertex> &vertices,
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

    Status Registry::init(void) { return this->__impl->init(); }
    Status Registry::destroy(void) { return this->__impl->destroy(); }

    const resource::Shader *Registry::getShader(const std::string &name) const { return this->__impl->getShader(name); }
    const resource::Texture *Registry::getTexture(const std::string &name) const { return this->__impl->getTexture(name); }
    const resource::Mesh *Registry::getMesh(const std::string &name) const { return this->__impl->getMesh(name); }
    Status Registry::addMesh(const std::string &name, const std::vector<resource::Vertex> &vertices, const std::vector<uint32_t> indices) { return this->__impl->addMesh(name, vertices, indices); }
    Status Registry::addTexture(const std::string &name, const unsigned char* data, const glm::ivec2 &size, const int &nChannels) { return this->__impl->addTexture(name, data, size, nChannels); }
    Status Registry::addShader(const std::string name, const std::string &vertexSource, const std::string &geometrySource, const std::string &fragmentSource, const std::string &computeSource) { return this->__impl->addShader(name, vertexSource, geometrySource, fragmentSource, computeSource); }
} // namespace rhi
