#ifndef __LIMINAL__RHI__PRIVATE__REGISTRY__MESH_HPP__
#define __LIMINAL__RHI__PRIVATE__REGISTRY__MESH_HPP__

#include "Status.hpp"
#include <resource/Mesh.hpp>

#include <memory>
#include <string>

namespace rhi {
    namespace __private {
        namespace __registry {
            class __Mesh {
                public:
                    __Mesh(void);
                    ~__Mesh(void);

                    Status init(void);
                    Status destroy(void);
                    const resource::Mesh *get(const std::string &name) const;

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;

            };
        } // namespace __registry
    } // namespace __private
} // namespace rhi


#endif // __LIMINAL__RHI__PRIVATE__REGISTRY__MESH_HPP__