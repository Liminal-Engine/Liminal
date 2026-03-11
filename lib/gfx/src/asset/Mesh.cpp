#include "asset/Mesh.hpp"
#include "Vertex.hpp"

#include <rhi/resource/Mesh.hpp>
#include <fs/Path.hpp>

#include <vector>

namespace gfx {
    namespace asset {
        class Mesh::__Impl {
            private:
                rhi::resource::Mesh *__resource;
                std::vector<Vertex> __vertices;
                std::vector<uint32_t> __indices;
                int __BOUDING_BOX; // this is for later, type will change
                fs::Path __path;

            public:
                __Impl(void) :
                __resource(nullptr),
                __vertices{},
                __indices{},
                __BOUDING_BOX(-1),
                __path()
                {

                }
        };

        Mesh::Mesh(void) :
        __impl(std::make_unique<__Impl>())
        {}

        Mesh::~Mesh() = default;

    } // namespace asset
} // namespace gfx
