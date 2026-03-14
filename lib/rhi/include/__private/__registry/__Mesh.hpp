#ifndef __LIMINAL__RHI__PRIVATE__REGISTRY__MESH_HPP__
#define __LIMINAL__RHI__PRIVATE__REGISTRY__MESH_HPP__

#include "Status.hpp"
#include "resource/Handle.hpp"
#include "resource/Vertex.hpp"
#include "resource/Mesh.hpp"

#include <memory>
#include <string>
#include <vector>

namespace rhi {
    namespace __private {
        namespace __registry {
            class __Mesh {
                public:
                    __Mesh(void);
                    ~__Mesh(void);

                    Status init(void);
                    Status destroy(void);
                    const resource::Handle getHandle(const std::string &name) const;
                    const resource::Mesh *getResource(resource::Handle handle) const;

                    bool exists(const std::string &name) const;
                    Status add(const std::string &name, const std::vector<resource::Vertex> &vertices, const std::vector<uint32_t> &indices);

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;

            };
        } // namespace __registry
    } // namespace __private
} // namespace rhi


#endif // __LIMINAL__RHI__PRIVATE__REGISTRY__MESH_HPP__