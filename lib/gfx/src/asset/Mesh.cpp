#include "asset/Mesh.hpp"

#include <rhi/def/Vertex.hpp>
#include <fs/Path.hpp>

#include <vector>

namespace gfx {
    namespace asset {
        class Mesh::__Impl {
            private:
                rhi::def::Handle __rhiHandle;
                std::vector<rhi::def::Vertex> __vertices;
                std::vector<uint32_t> __indices;
                int __BOUDING_BOX; // this is for later, type will change
                fs::Path __path;

            public:

                __Impl(void) :
                __rhiHandle(rhi::def::NULL_HANDLE),
                __vertices{},
                __indices{},
                __BOUDING_BOX(-1),
                __path()
                {}

                const std::vector<rhi::def::Vertex> &getVertices(void) const { return this->__vertices; }
                const std::vector<uint32_t> &getIndices(void) const { return this->__indices; }

                Status copy(const __Impl &other) {
                    this->__rhiHandle = other.__rhiHandle;
                    this->__vertices = other.__vertices;
                    this->__indices = other.__indices;
                    this->__BOUDING_BOX = other.__BOUDING_BOX;
                    this->__path = other.__path;
                    return Status::OK;
                }

                Status load(const fs::Path &path) {
                    rhi::def::Vertex v1;
                    v1.position = glm::vec3(0.0f, 0.5f, 0.0f);
                    v1.normal = glm::vec3(0.0f);
                    v1.uv = glm::vec2(0.0f);
                    rhi::def::Vertex v2;
                    v2.position = glm::vec3(0.5f, -0.5f, 0.0f);
                    v2.normal = glm::vec3(0.0f);
                    v2.uv = glm::vec2(0.0f);
                    rhi::def::Vertex v3;
                    v3.position = glm::vec3(-0.5f, -0.5f, 0.0f);
                    v3.normal = glm::vec3(0.0f);
                    v3.uv = glm::vec2(0.0f);
                    this->__vertices = { v1, v2, v3 };
                    this->__indices = {0, 1, 2};
                    this->__path = path;
                    return Status::OK;
                }

                void bind(const rhi::resource::Mesh *rhiMesh) {
                    this->__rhiHandle = rhiMesh->getRHIHandle();
                }

                rhi::def::Handle getRHIHandle(void) const { return this->__rhiHandle; }

                const fs::Path &getPath(void) const { return this->__path; }

        };

        Mesh::Mesh(void) :
        __impl(std::make_unique<__Impl>())
        {}

        Mesh::~Mesh() = default;

        Mesh::Mesh(Mesh &&) noexcept = default;

        Mesh &Mesh::operator=(Mesh &&) noexcept = default;

        const std::vector<rhi::def::Vertex> &Mesh::getVertices(void) const { return this->__impl->getVertices(); }
        const std::vector<uint32_t> &Mesh::getIndices(void) const { return this->__impl->getIndices(); }
        Status Mesh::load(const fs::Path &path) { return this->__impl->load(path); }
        const fs::Path &Mesh::getPath(void) const { return this->__impl->getPath(); }
        void Mesh::bind(const rhi::resource::Mesh *rhiMesh) { this->__impl->bind(rhiMesh); }
        rhi::def::Handle Mesh::getRHIHandle(void) const { return this->__impl->getRHIHandle(); }
        Status Mesh::copy(const Mesh &other) { return this->__impl->copy(*other.__impl); }

    } // namespace asset
} // namespace gfx
