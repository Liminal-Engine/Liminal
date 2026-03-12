#ifndef __LIMINAL__LIB__RHI__PRIVATE__REGISTR__TEXTURE_HPP__
#define __LIMINAL__LIB__RHI__PRIVATE__REGISTR__TEXTURE_HPP__

#include "Status.hpp"
#include "resource/Texture.hpp"

#include <fs/Path.hpp>

namespace rhi {
    namespace __private {
        namespace __registry {
            class __Texture {
                public:
                    __Texture(void);
                    ~__Texture();

                    Status init(void);
                    Status destroy(void);
                    const resource::Texture *get(const std::string &name) const;

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;
            };         
        } // namespace __registry
    } // namespace __private
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__PRIVATE__REGISTR__TEXTURE_HPP__