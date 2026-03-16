#ifndef __LIMINAL__LIB__GFX__INCLUDE__ASSET__MESH_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__ASSET__MESH_HPP__

#include "../Status.hpp" // FIXME

#include <fs/Path.hpp>
#include <rhi/def/Handle.hpp>
#include <rhi/def/Vertex.hpp>

#include <memory>

namespace gfx {
    namespace asset {
        class Mesh {
            public:
                Mesh(void);
                ~Mesh();

                Mesh(const Mesh &) = delete;
                Mesh &operator=(const Mesh &) = delete;
                Mesh(Mesh &&) noexcept;
                Mesh &operator=(Mesh &&) noexcept;

                const std::vector<rhi::def::Vertex> &getVertices(void) const;
                const std::vector<uint32_t> &getIndices(void) const;
                const fs::Path &getPath(void) const;

                
                Status copy(const Mesh &other);
                Status load(const fs::Path &path);

                Status setRHIHandle(rhi::def::Handle handle);
                rhi::def::Handle getRHIHandle(void) const;

                
            
            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace asset
} // namespace gfx

#endif // __LIMINAL__LIB__GFX__INCLUDE__ASSET__MESH_HPP__