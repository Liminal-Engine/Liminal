#ifndef __LIMINAL__LIB__RHI__INCLUDE__RENDERER_HPP__
#define __LIMINAL__LIB__RHI__INCLUDE__RENDERER_HPP__

#include "Registry.hpp"

#include <entity/Registry.hpp>

#include <vector>
#include <memory>

namespace rhi {
    class Renderer {
        public:

            static void init(const Registry &RHIRegistry);
            static void destroy(void);
        
            static Renderer *get(void);            

            Renderer(const Renderer&) = delete;            // No copy
            Renderer& operator=(const Renderer&) = delete; // No affectation
            Renderer(Renderer&&) = delete;                 // No move
            Renderer& operator=(Renderer&&) = delete;      // No affectation by moving

            void draw(const entity::Registry &entityRegistry);

        private:
            Renderer(const Registry &RHIRegistry);
            ~Renderer();

            static Renderer *__instance;
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__INCLUDE__RENDERER_HPP__