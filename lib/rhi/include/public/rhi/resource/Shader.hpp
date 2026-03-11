#ifndef __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__SHADER_HPP__
#define __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__SHADER_HPP__

#include <memory>

namespace rhi {
    namespace resource {
        class Shader {
            public:
                static void init(void);
                static void destroy(void);
    
                static Shader *get(void);
    
                Shader(const Shader&) = delete;            // No copy
                Shader& operator=(const Shader&) = delete; // No affectation
                Shader(Shader&&) = delete;                 // No move
                Shader& operator=(Shader&&) = delete;      // No affectation by moving
    
            private:
                Shader(void);
                ~Shader();
    
                static Shader *__instance;
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace resource
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__SHADER_HPP__