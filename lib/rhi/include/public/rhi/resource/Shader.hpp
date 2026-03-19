#ifndef __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__SHADER_HPP__
#define __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__SHADER_HPP__

#include "../def/Uniform.hpp" // FIXME
#include "../def/Handle.hpp" // FIXME
#include "../def/Uniform.hpp" // FIXME

#include <fs/Path.hpp>

#include <memory>
#include <vector>

namespace rhi {
    namespace resource {
        class Shader {
            public:
                Shader(
                    const std::string &vertexSource,
                    const std::string &geometrySource,
                    const std::string &fragmentSource,
                    const std::string &computeSource,
                    def::Handle handle
                );
                ~Shader();

                void use(const std::vector<def::Uniform> &uniforms = {}) const;

                const std::vector<def::Uniform> &getUniforms(void) const;
                def::Handle getRHIHandle(void) const;
    
                Shader(const Shader&) = delete;            // No copy
                Shader& operator=(const Shader&) = delete; // No affectation
                Shader(Shader&&) = delete;                 // No move
                Shader& operator=(Shader&&) = delete;      // No affectation by moving
    
            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace resource
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__SHADER_HPP__