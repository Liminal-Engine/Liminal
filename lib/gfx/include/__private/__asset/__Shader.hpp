#ifndef __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__SHADER_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__SHADER_HPP__

#include <memory>

namespace gfx {
    namespace __private {
        namespace __asset {
            class __Shader {
                public:
                    __Shader(void);
                    ~__Shader();

                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;   
            };     
        } // namespace __asset
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__INCLUDE__PRIVATE__ASSET__SHADER_HPP__