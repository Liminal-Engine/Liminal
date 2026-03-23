#ifndef __LIMINAL__LIB__GFX__RENDERER_HPP__
#define __LIMINAL__LIB__GFX__RENDERER_HPP__

#include <memory>

/// forward declarations
namespace rhi {
    class Context;
}
/// end of forward declarations

namespace gfx {
    class Renderer {
        public:
            Renderer(const rhi::Context &rhiContext);
            ~Renderer();

            void draw(void) const;
        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__RENDERER_HPP__