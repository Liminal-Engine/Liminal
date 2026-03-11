#include "resource/Mesh.hpp"

#include <logger/logger.hpp>

namespace rhi {
    namespace resource {
        Mesh *Mesh::__instance = nullptr;
    
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
    
        void Mesh::init(void) {
            if (__instance != nullptr) {
                logger::error << "Mesh resource already intialized, nothing to do" << std::endl;
                return;
            }
            __instance = new Mesh();
        }
    
        void Mesh::destroy(void) {
            if (__instance == nullptr) {
                logger::error << "Mesh resource not initialized or already destroyed, nothing to do" << std::endl;
                return;
            }
            delete __instance;
            __instance = nullptr;
        }
    
        Mesh *Mesh::get(void) {
            if (__instance == nullptr) {
                logger::fatal << "Mesh resource required but not initialized" << std::endl;
            }
            return __instance;
        }
    
        Mesh::Mesh(void) :
        __impl(std::make_unique<__Impl>())
        {
    
        }
    
        Mesh::~Mesh() = default;
    } // namespace resource
} // namespace rhi
