#ifndef __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__SHADER_HPP__
#define __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__SHADER_HPP__

#include <fs/Path.hpp>

#include <memory>

namespace rhi {
    namespace resource {
        class Shader {
            public:
                Shader(const fs::Path &path);
                ~Shader();
    
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