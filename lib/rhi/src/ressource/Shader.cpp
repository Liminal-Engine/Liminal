#include "resource/Shader.hpp"

#include <logger/logger.hpp>

namespace rhi {
    namespace resource {
        
        Shader *Shader::__instance = nullptr;
    
        class Shader::__Impl {
            private:
                uint32_t __handle;
    
            public:
                __Impl(void) :
                __handle(0)
                {
                    
                }
        };
    
        void Shader::init(void) {
            if (__instance != nullptr) {
                logger::error << "Shader ressource already intialized, nothing to do" << std::endl;
                return;
            }
            __instance = new Shader();
        }
    
        void Shader::destroy(void) {
            if (__instance == nullptr) {
                logger::error << "Shader ressource not initialized or already destroyed, nothing to do" << std::endl;
                return;
            }
            delete __instance;
            __instance = nullptr;
        }
    
        Shader *Shader::get(void) {
            if (__instance == nullptr) {
                logger::fatal << "Shader ressource required but not initialized" << std::endl;
            }
            return __instance;
        }
    
        Shader::Shader(void) :
        __impl(std::make_unique<__Impl>())
        {
    
        }
    
        Shader::~Shader() = default;
    } // namespace resource
} // namespace rhi
