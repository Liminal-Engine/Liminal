#ifndef __LIMINAL__LIB__RHI__REGISTRY_HPP__
#define __LIMINAL__LIB__RHI__REGISTRY_HPP__

#include "Status.hpp"
#include "resource/Shader.hpp"
#include "resource/Texture.hpp"
#include "resource/Mesh.hpp"
#include "def/Vertex.hpp"
#include "def/Handle.hpp"

#include <memory>

#include <glm/glm.hpp>

namespace rhi {
    class Registry {
        public:
            Registry(void);
            ~Registry();

            def::Handle getShaderHandle(const std::string &name) const;
            def::Handle getTextureHandle(const std::string &name) const;
            def::Handle getMeshHandle(const std::string &name) const;

            const resource::Shader *getShaderResource(def::Handle handle) const;
            const resource::Texture *getTextureResource(def::Handle handle) const;
            const resource::Mesh *getMeshResource(def::Handle handle) const;

            Status addMesh(
                const std::string &name,
                const std::vector<def::Vertex> &vertices,
                const std::vector<uint32_t> &indices
            );

            Status addTexture(const std::string &name, const unsigned char* data, const glm::ivec2 &size, const int nChannels);

            Status addShader(
                const std::string name,
                const std::string &vertexSource,
                const std::string &geometrySource,
                const std::string &fragmentSource,
                const std::string &computeSource
            );

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__REGISTRY_HPP__