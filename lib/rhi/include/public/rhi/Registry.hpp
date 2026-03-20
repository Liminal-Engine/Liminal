#ifndef __LIMINAL__LIB__RHI__REGISTRY_HPP__
#define __LIMINAL__LIB__RHI__REGISTRY_HPP__

#include "Status.hpp"
#include "def/Handle.hpp"
#include "def/Vertex.hpp"
#include "resource/Mesh.hpp"
#include "resource/Shader.hpp"

#include <memory>
#include <string>
#include <vector>
#include <cstdint>

namespace rhi {
    class Registry {
        public:
            Registry(const Registry&) = delete;
            Registry(Registry&&) = delete;
            Registry &operator=(const Registry&) = delete;
            Registry &operator=(Registry&&) = delete;

            static bool exists(const std::string &name);
            static rhi::def::Handle getHandle(const std::string &name);
            static const resource::Mesh *getMesh(def::Handle handle);
            static const resource::Shader *getShader(def::Handle handle);
            
            
            static Status loadMesh(
                const std::string &name, 
                const std::vector<def::Vertex> &vertices,
                const std::vector<uint32_t> &indices
            );

            static Status loadShader(
                const std::string &name,
                const std::string &vertexSource,
                const std::string &geometrySource,
                const std::string &fragmentSource,
                const std::string &computeSource
            );


            static Status clear(void);

        private:
            Registry(void);
            ~Registry();
            static Registry &__instance(void);

            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__REGISTRY_HPP__