#ifndef __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__MESH_HPP__
#define __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__MESH_HPP__

#include "Status.hpp"
#include "asset/Mesh.hpp"

#include <memory>
#include <string>

namespace gfx {
    namespace __private {
        namespace __registry {
            class __Mesh {
                public:
                    __Mesh(void);
                    ~__Mesh();

                    [[nodiscard]] Status add(const std::string &name, asset::Mesh &&mesh);
                    bool exists(const std::string &name) const;
                    const gfx::asset::Mesh *getByPath(const fs::Path &path);
                    const gfx::asset::Mesh *get(const std::string &name) const;

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;
            };         
        } // namespace __registry
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__MESH_HPP__