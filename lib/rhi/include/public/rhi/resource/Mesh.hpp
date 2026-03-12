#ifndef __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__MESH_HPP__
#define __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__MESH_HPP__

#include "Vertex.hpp"

#include <vector>
#include <memory>

namespace rhi {
    namespace resource {
        class Mesh {
            public:
                Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);
                ~Mesh();
    
                Mesh(const Mesh&) = delete;            // No copy
                Mesh& operator=(const Mesh&) = delete; // No affectation
                Mesh(Mesh&&) = delete;                 // No move
                Mesh& operator=(Mesh&&) = delete;      // No affectation by moving
    
            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace resource
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__MESH_HPP__