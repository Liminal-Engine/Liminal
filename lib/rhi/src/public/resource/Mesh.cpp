#include "resource/Mesh.hpp"

#include <logger/logger.hpp>

namespace rhi {
    namespace resource {
    
        class Mesh::__Impl {
            private:
                uint32_t __VAO;
                uint32_t __EBO;
                uint32_t __VBO;
                uint32_t __count;
    
            public:
                __Impl(void) :
                __VAO(0),
                __EBO(0),
                __VBO(0),
                __count(0)
                {
                    
                }
        };
    
        
    
        Mesh::Mesh(void) :
        __impl(std::make_unique<__Impl>())
        {
    
        }
    
        Mesh::~Mesh() = default;
    } // namespace resource
} // namespace rhi
