#ifndef __LIMINAL__LIB__RHI__PRIVATE__REGISTRY__SHADER_HPP__
#define __LIMINAL__LIB__RHI__PRIVATE__REGISTRY__SHADER_HPP__

#include "Status.hpp"
#include "resource/Shader.hpp"
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
                    const resource::Shader *get(const std::string &name) const;
                    bool exists(const std::string &name) const;

                    Status add(
                        const std::string &name,
                        const std::string &vertexSource,
                        const std::string &geometrySource,
                        const std::string &fragmentSource,
                        const std::string &computeSource
                    );

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;
            };         
        } // namespace __registry
    } // namespace __private
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__PRIVATE__REGISTRY__SHADER_HPP__