#ifndef __LIMINAL__LIB__RHI__PRIVATE__REGISTRY__SHADER_HPP__
#define __LIMINAL__LIB__RHI__PRIVATE__REGISTRY__SHADER_HPP__

#include "Status.hpp"
#include "resource/Shader.hpp"
#include "ShaderCategory.hpp"
#include <string>

#include <memory>

namespace rhi {
    namespace __private {
        namespace __registry {
            class __Shader {
                public:
                    __Shader(void);
                    ~__Shader(void);

                    Status init(void);
                    Status destroy(void);
                    const resource::Shader *get(const ShaderCategory &category, const std::string &name)  const;

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;
            };         
        } // namespace __registry
    } // namespace __private
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__PRIVATE__REGISTRY__SHADER_HPP__