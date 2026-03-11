#ifndef __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__MESH_HPP__
#define __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__MESH_HPP__

#include <memory>

namespace rhi {
    namespace resource {
        class Mesh {
            public:
                static void init(void);
                static void destroy(void);
    
                static Mesh *get(void);
    
                Mesh(const Mesh&) = delete;            // No copy
                Mesh& operator=(const Mesh&) = delete; // No affectation
                Mesh(Mesh&&) = delete;                 // No move
                Mesh& operator=(Mesh&&) = delete;      // No affectation by moving
    
            private:
                Mesh(void);
                ~Mesh();
    
                static Mesh *__instance;
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };
    } // namespace resource
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__INCLUDE__PUBLIC__RESOURCE__MESH_HPP__