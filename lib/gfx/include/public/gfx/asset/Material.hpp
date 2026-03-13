#ifndef __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__
#define __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__

#include "../Status.hpp" // FIXME

#include <memory>

#include <glm/glm.hpp>

namespace gfx {
    namespace asset {
        class Material {
            public:
                Material(void);
                ~Material();

                Material(const Material &) = delete;
                Material &operator=(const Material &) = delete;
                Material(Material &&) noexcept;
                Material &operator=(Material &&) noexcept;

                [[nodiscard]] Status setColor(const glm::vec3 &color);

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace asset
} // namespace gfx


#endif // __LIMINAL__LIB__GFX__INCLUDE__PUBLIC__ASSET__MATERIAL_HPP__