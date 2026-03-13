#include "__private/__asset/__Texture.hpp"

#include <rhi/resource/Texture.hpp>
#include <rhi/sampler/TextureFiltering.hpp>
#include <rhi/sampler/TextureWrapping.hpp>
#include <fs/Path.hpp>
#include <logger/logger.hpp>

#include <unordered_map>
#include <string>
#include <cstring>
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include <glm/glm.hpp>

namespace gfx {
    namespace __private {
        namespace __asset {
            class __Texture::__Impl {
                private:
                    const rhi::resource::Texture *__resource;
                    fs::Path __path;
                    unsigned char *__data;
                    glm::ivec2 __size;
                    int __nChannels;
                    rhi::sampler::TextureWrapping __wrapping;
                    rhi::sampler::TextureFiltering __filtering;
                    bool __hasMipMap;

                public:
                    __Impl(void) :
                    __resource(nullptr),
                    __path(),
                    __data(nullptr),
                    __size(0.0f),
                    __nChannels(0),
                    __wrapping(),
                    __filtering(),
                    __hasMipMap()
                    {

                    }

                    ~__Impl() {
                        if (this->__data) stbi_image_free(this->__data);
                    }

                    Status load(const fs::Path &path) {
                        logger::debug << "Loading texture from image: " << path.asStr() << std::endl;
                        // Avoid leaking previous decoded image if load() is called multiple times.
                        if (this->__data != nullptr) {
                            stbi_image_free(this->__data);
                            this->__data = nullptr;
                        }
                        this->__data = stbi_load(path.asStr().c_str(), &this->__size.x, &this->__size.y, &this->__nChannels, 0);
                        if (this->__data == nullptr) {
                            logger::error << "Failed to load texture image: " << path.asStr() << std::endl;
                            return Status::N_OK;
                        }
                        this->__wrapping = rhi::sampler::TextureWrapping::REPEAT;
                        this->__filtering = rhi::sampler::TextureFiltering::LINEAR;
                        this->__hasMipMap = true;
                        this->__path = path;
                        return Status::OK;
                    }

                    const unsigned char *getData(void) const { return this->__data; }
                    const glm::ivec2 &getSize(void) const { return this->__size; }
                    const int &getNChannels(void) const { return this->__nChannels; }

                    Status setResource(const rhi::resource::Texture *resource) {
                        this->__resource = resource;
                        return Status::OK;
                    }

                    Status copy(const __Impl &other) {
                        this->__resource = other.__resource;
                        this->__path = other.__path;
                        this->__size = other.__size;
                        this->__nChannels = other.__nChannels;
                        this->__wrapping = other.__wrapping;
                        this->__filtering = other.__filtering;
                        this->__hasMipMap = other.__hasMipMap;

                        // Deep-copy pixel buffer to avoid double-free and dangling pointers.
                        if (this->__data != nullptr) {
                            stbi_image_free(this->__data);
                            this->__data = nullptr;
                        }
                        const std::size_t dataSize = static_cast<std::size_t>(this->__size.x) * static_cast<std::size_t>(this->__size.y) * static_cast<std::size_t>(this->__nChannels);
                        if (other.__data != nullptr && dataSize > 0) {
                            this->__data = static_cast<unsigned char *>(std::malloc(dataSize));
                            if (this->__data == nullptr) {
                                logger::error << "Failed to allocate texture copy buffer" << std::endl;
                                return Status::N_OK;
                            }
                            std::memcpy(this->__data, other.__data, dataSize);
                        }
                        return Status::OK;
                    }
            };


            __Texture::__Texture(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Texture::~__Texture() = default;

            Status __Texture::load(const fs::Path &path) { return this->__impl->load(path); }
            const unsigned char *__Texture::getData(void) const { return this->__impl->getData(); }
            const glm::ivec2 &__Texture::getSize(void) const { return this->__impl->getSize(); }
            const int &__Texture::getNChannels(void) const { return this->__impl->getNChannels(); }

            Status __Texture::setResource(const rhi::resource::Texture *resource) { return this->__impl->setResource(resource); }

            Status __Texture::copy(const __Texture &other) { return this->__impl->copy(*other.__impl); }
        } // namespace __aset
    } // namespace __private
} // namespace gfx
