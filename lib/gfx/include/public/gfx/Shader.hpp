#ifndef __LIMINAL__LIB__GFX__SHADER_HPP__
#define __LIMINAL__LIB__GFX__SHADER_HPP__

#include <fs/Path.hpp>

#include <memory>

namespace gfx {
    class Shader {
        public:
            Shader(const fs::Path &path);
            ~Shader();
        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__SHADER_HPP__