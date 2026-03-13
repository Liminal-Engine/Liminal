#ifndef __LIMINAL__LIB__RHI__REGISTRY_HPP__
#define __LIMINAL__LIB__RHI__REGISTRY_HPP__

#include "Status.hpp"
#include "resource/Shader.hpp"
#include "ShaderCategory.hpp"
#include "resource/Texture.hpp"
#include "resource/Mesh.hpp"
#include "resource/Vertex.hpp"

#include <memory>

#include <glm/glm.hpp>

namespace rhi {
    class Registry {
        public:
            Registry(void);
            ~Registry();

            Status init(void);
            Status destroy(void);

            const resource::Shader *getShader(const ShaderCategory &category, const std::string &name) const;
            const resource::Texture *getTexture(const std::string &name) const;
            const resource::Mesh *getMesh(const std::string &name) const;

            Status addMesh(
                const std::string &name,
                const std::vector<resource::Vertex> &vertices,
                const std::vector<uint32_t> indices
            );

            Status addTexture(const std::string &name, const unsigned char* data, const glm::ivec2 &size, const int &nChannels);

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__REGISTRY_HPP__