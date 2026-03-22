#ifndef __LIMINAL__RHI__RESOURCE__SHADER_HPP__
#define __LIMINAL__RHI__RESOURCE__SHADER_HPP__

#include "rhi/def/UniformValue.hpp"

#include <string>
#include <memory>

namespace rhi {
    namespace resource {
        class Shader {
            public:
                Shader(
                    const std::string &vertexSource,
                    const std::string &geometrySource,
                    const std::string &fragmentSource,
                    const std::string &computeSource
                );
                ~Shader();
                Shader(Shader&&) noexcept;
                Shader& operator=(Shader&&) noexcept;
                Shader(const Shader&) = delete;
                Shader& operator=(const Shader&) = delete;

                void use(void) const;

                void setUniform(const std::string &name, def::UniformValue value) const;
            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace resource
} // namespace rhi

#endif // __LIMINAL__RHI__RESOURCE__SHADER_HPP__