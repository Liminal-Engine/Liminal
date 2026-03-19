#ifndef __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__ASSET_REGISTRY_HPP__
#define __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__ASSET_REGISTRY_HPP__

#include "gfx/Status.hpp"

#include <fs/Path.hpp>

#include <string>
#include <memory>

namespace gfx {
    namespace __private {
        namespace __registry {
            template<typename T>
            class __AssetRegistry {
                public:
                    __AssetRegistry(void);
                    ~__AssetRegistry();

                    Status add(const std::string &name, T &&asset);
                    bool exists(const std::string &name) const;
                    bool exists(const fs::Path &path) const;
                    const T *get(const std::string &name) const;
                    const T *get(const fs::Path &path) const;
                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;
            };
        } // namespace __registry
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__ASSET_REGISTRY_HPP__