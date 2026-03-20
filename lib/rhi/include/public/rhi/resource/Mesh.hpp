#ifndef __LIMINAL__RHI__RESOURCE__MESH_HPP__
#define __LIMINAL__RHI__RESOURCE__MESH_HPP__

#include "rhi/def/Vertex.hpp"

#include <memory>
#include <vector>
#include <cstdint>

namespace rhi {
    namespace resource {
        class Mesh {
            public:
                Mesh(const std::vector<def::Vertex> &vertices, const std::vector<uint32_t> &indices);
                ~Mesh();
                Mesh(Mesh&&) noexcept;
                Mesh& operator=(Mesh&&) noexcept;
                Mesh(const Mesh&) = delete;
                Mesh& operator=(const Mesh&) = delete;

                void draw(void) const;

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace resource
} // namespace rhi

#endif // __LIMINAL__RHI__RESOURCE__MESH_HPP__