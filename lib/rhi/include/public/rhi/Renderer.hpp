#ifndef __LIMINAL__LIB__RHI__RENDERER_HPP__
#define __LIMINAL__LIB__RHI__RENDERER_HPP__

#include "Registry.hpp"

#include <memory>

namespace rhi {
    class Renderer {
        public:
            Renderer();
            ~Renderer();

            void draw(void) const;
        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__RENDERER_HPP__