#include "Texture.hpp"

#include <rhi/def/TextureFiltering.hpp>
#include <rhi/def/TextureWrapping.hpp>
#include <logger/logger.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>
#include <glad/glad.h>

namespace gfx {
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
            // OpenGL part
            uint32_t __glHandle;

        public:
            __Impl(const fs::Path &path) :
            __data(nullptr),
            __size(0.0f),
            __nChannels(0),
            __glHandle(0)
            {
                // 1. Store path, will be used for hashing
                fs::Path absolutePath(path);
                absolutePath.toAbsolute();
                absolutePath.clean();
                this->__path = absolutePath;
                logger::debug << "Loading texture from: " << absolutePath.asStr() << std::endl;
                this->__data = stbi_load(absolutePath.asStr().c_str(), &this->__size.x, &this->__size.y, &this->__nChannels, 0);
                if (this->__data == nullptr) {
                    logger::error << "Failed to load texture image: " << absolutePath.asStr() << std::endl;
                    return;
                }
                this->__textureWrapping = rhi::def::TextureWrapping::REPEAT;
                this->__textureFiltering = rhi::def::TextureFiltering::LINEAR;
                this->__hasMipmap = true;
                this->__glHandle = __loadTexture(this->__data, this->__size, this->__nChannels, this->__hasMipmap);
            }

            ~__Impl() {
                if (this->__data) stbi_image_free(this->__data);
                if (this->__glHandle) glDeleteTextures(1, &this->__glHandle);
            }
    };

    Texture::Texture(const fs::Path &path) : __impl(std::make_unique<__Impl>(path)) {}
    Texture::~Texture() = default;
} // namespace gfx
