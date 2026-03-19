#ifndef __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__MATERIAL_HPP__
#define __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__MATERIAL_HPP__

#include "Status.hpp"
#include "asset/Material.hpp"

#include <memory>
#include <string>

namespace gfx {
    namespace __private {
        namespace __registry {
            class __Material {
                public:
                    __Material(void);
                    ~__Material();

                    [[nodiscard]] Status add(const std::string &name, asset::Material &&material);
                    bool exists(const std::string &name) const;
                    const asset::Material *get(const std::string &name) const;

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;
            };
        } // namespace __registry
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__MATERIAL_HPP__