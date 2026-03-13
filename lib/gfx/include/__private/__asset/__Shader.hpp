#ifndef __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__SHADER_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__SHADER_HPP__

#include "Status.hpp"

#include <fs/Path.hpp>
#include <rhi/resource/Shader.hpp>

#include <memory>

namespace gfx {
    namespace __private {
        namespace __asset {
            class __Shader {
                public:
                    __Shader(void);
                    ~__Shader();

                    Status copy(const __Shader &other);
                    Status load(const fs::Path &path);

                    Status setResource(const rhi::resource::Shader *resource);

                    const std::string &getVertexSource(void) const;
                    const std::string &getGeometrySource(void) const;
                    const std::string &getFragmentSource(void) const;
                    const std::string &getComputeSource(void) const;

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;   
            };     
        } // namespace __asset
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__SHADER_HPP__