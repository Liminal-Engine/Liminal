#ifndef __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__SHADER_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__SHADER_HPP__

#include "Status.hpp"

#include <fs/Path.hpp>
#include <rhi/def/Handle.hpp>
#include <rhi/def/ShaderType.hpp>


#include <memory>

namespace gfx {
    namespace __private {
        namespace __asset {
            class __Shader {
                public:
                    __Shader(void);
                    ~__Shader();

                    __Shader(const __Shader&) = delete;            // No copy
                    __Shader& operator=(const __Shader&) = delete; // No affectation
                    __Shader(__Shader&&) noexcept;                 // No move
                    __Shader& operator=(__Shader &&) noexcept;      // No affectation by moving

                    Status copy(const __Shader &other);
                    Status load(const fs::Path &path);
                    const fs::Path &getPath(void) const;

                    Status setRHIHandle(rhi::def::Handle RHIHandle);
                    rhi::def::Handle getRHIHandle(void) const;

                    const std::string &getSource(rhi::def::ShaderType type) const;

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;   
            };     
        } // namespace __asset
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__SHADER_HPP__