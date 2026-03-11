#include "__private/__asset/__Texture.hpp"

#include <rhi/resource/Texture.hpp>
#include <rhi/sampler/TextureFiltering.hpp>
#include <rhi/sampler/TextureWrapping.hpp>
#include <fs/Path.hpp>

#include <unordered_map>
#include <string>

#include <glm/glm.hpp>

namespace gfx {
    namespace __private {
        namespace __asset {
            class __Texture::__Impl {
                private:
                    rhi::resource::Texture *__resource;
                    fs::Path __path;
                    glm::vec2 __size;
                    rhi::sampler::TextureWrapping __wrapping;
                    rhi::sampler::TextureFiltering __filtering;
                    bool __hasMipMap;

                public:
                    __Impl(void) :
                    __resource(nullptr),
                    __path(),
                    __size(),
                    __wrapping(),
                    __filtering(),
                    __hasMipMap()
                    {

                    }
            };


            __Texture::__Texture(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Texture::~__Texture() = default;

            
        } // namespace __aset
    } // namespace __private
} // namespace gfx
