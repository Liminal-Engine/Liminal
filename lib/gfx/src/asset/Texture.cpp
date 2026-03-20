#include "asset/Texture.hpp"

#include <rhi/def/TextureFiltering.hpp>
#include <rhi/def/TextureWrapping.hpp>
#include <logger/logger.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace gfx {
    namespace asset {
        
        class Texture::__Impl {
            private:
    
                static uint32_t __loadTexture(
                    const unsigned char *data,
                    const glm::ivec2 &size,
                    int nChannels,
                    bool generateMipmap
                ) {
                    GLenum format = GL_RGB;
                    GLenum internalFormat = GL_RGB8;
                    if (nChannels == 1) {
                        format = GL_RED;
                        internalFormat = GL_R8;
                    } else if (nChannels == 3) {
                        format = GL_RGB;
                        internalFormat = GL_RGB8;
                    } else if (nChannels == 4) {
                        format = GL_RGBA;
                        internalFormat = GL_RGBA8;
                    } else {
                        logger::error << "Unknown number of channels, cannot load texture" << std::endl;
                        return 0;
                    }
    
                    // create gl object
                    uint32_t glTexture = 0;
                    glGenTextures(1, &glTexture);
                    glBindTexture(GL_TEXTURE_2D, glTexture);
                    // define wrapping and filtering
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // FIXME: as of now we don't take into account texturewrap and filtering comming from asset
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    // bind image to texture and generate mipmap
                    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // FIXME: as of now, this is automatic instead of coming from the asset
                    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, data);
                    if (generateMipmap) glGenerateMipmap(GL_TEXTURE_2D); // FIXME: as of now, this is automatic instead of coming from the asset
                    return glTexture;
                }
    
                // Engine part
                fs::Path __path;
                unsigned char *__data;
                glm::ivec2 __size;
                int __nChannels;
                rhi::def::TextureWrapping __textureWrapping;
                rhi::def::TextureFiltering __textureFiltering;
                bool __hasMipmap;
                bool __loaded;
                // OpenGL part
                uint32_t __glHandle;
    
            public:
                __Impl(void) :
                __path(),
                __data(nullptr),
                __size(0.0f),
                __nChannels(0),
                __textureWrapping(rhi::def::TextureWrapping::REPEAT),
                __textureFiltering(rhi::def::TextureFiltering::LINEAR),
                __hasMipmap(false),
                __loaded(false),
                __glHandle(0)
                {
                }  
    
                ~__Impl() {
                    if (this->__data) stbi_image_free(this->__data);
                    if (this->__glHandle) glDeleteTextures(1, &this->__glHandle);
                }
    
                Status load(const fs::Path &path) {
                    this->__loaded = false;
                    // 1. Store path, will be used for hashing
                    fs::Path absolutePath(path);
                    absolutePath.toAbsolute();
                    absolutePath.clean();
                    this->__path = absolutePath;
                    logger::debug << "Loading texture from: " << absolutePath.asStr() << std::endl;
                    this->__data = stbi_load(absolutePath.asStr().c_str(), &this->__size.x, &this->__size.y, &this->__nChannels, 0);
                    if (this->__data == nullptr) {
                        logger::error << "Failed to load texture image: " << absolutePath.asStr() << std::endl;
                        return Status::E_FILE_CONTENT;
                    }
                    this->__textureWrapping = rhi::def::TextureWrapping::REPEAT;
                    this->__textureFiltering = rhi::def::TextureFiltering::LINEAR;
                    this->__hasMipmap = true;
                    this->__glHandle = __loadTexture(this->__data, this->__size, this->__nChannels, this->__hasMipmap);
                    if (this->__glHandle == 0) {
                        logger::error << "Failed to create GL texture for: " << absolutePath.asStr() << std::endl;
                        return Status::E_GL;
                    }
                    this->__loaded = true;
                    return Status::OK;
                }
    
                bool isLoaded(void) const { return this->__loaded; }
        };
    
        Texture::Texture(void) : __impl(std::make_unique<__Impl>()) {}
        Texture::~Texture() = default;
    
        Status Texture::load(const fs::Path &path) { return this->__impl->load(path); }
        bool Texture::isLoaded(void) const { return this->__impl->isLoaded(); }
    } // namespace asset
    
} // namespace gfx
