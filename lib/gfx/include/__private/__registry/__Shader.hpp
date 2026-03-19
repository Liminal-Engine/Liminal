#ifndef __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__SHADER_HPP__
#define __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__SHADER_HPP__

#include "Status.hpp"
#include "__private/__asset/__Shader/hpp"

#include <fs/Path.hpp>

#include <memory>

namespace gfx {
    namespace __private {
        namespace __registry {
            class __Shader {
                public:
                    __Shader(void);
                    ~__Shader();

                    Status add(const std::string &name, __private::__asset::__Shader &&shader);
                    bool exists(const std::string &name) const;
                    const gfx::asset::__Shader *getByPath(const fs::Path &path);
                    const gfx::asset::__Shader *get(const std::string &name) const;
                private:
                    class __Impl;
                    std::unique_ptr<__Impl> __impl;
            };         
        } // namespace __registry
    } // namespace __private
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__PRIVATE__REGISTRY__SHADER_HPP__