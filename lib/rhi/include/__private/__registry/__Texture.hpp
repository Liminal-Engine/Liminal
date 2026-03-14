#ifndef __LIMINAL__LIB__RHI__PRIVATE__REGISTR__TEXTURE_HPP__
#define __LIMINAL__LIB__RHI__PRIVATE__REGISTR__TEXTURE_HPP__

#include "Status.hpp"
#include "resource/Handle.hpp"
#include "resource/Texture.hpp"

#include <fs/Path.hpp>

#include <glm/glm.hpp>

namespace rhi {
    namespace __private {
        namespace __registry {
            class __Texture {
                public:
                    __Texture(void);
                    ~__Texture();

                    Status init(void);
                    Status destroy(void);
                    const resource::Handle getHandle(const std::string &name) const;
                    const resource::Texture *getResource(resource::Handle handle) const;
                    bool exists(const std::string &name) const;
                    
                    Status add(const std::string &name, const unsigned char* data, const glm::ivec2 &size, const int &nChannels);

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;
            };         
        } // namespace __registry
    } // namespace __private
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__PRIVATE__REGISTR__TEXTURE_HPP__