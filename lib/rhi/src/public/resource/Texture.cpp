#include "resource/Texture.hpp"

#include <logger/logger.hpp>

#include <glad/glad.h>

namespace rhi {
    namespace resource {
        
        class Texture::__Impl {
            private:

                static uint32_t __loadTexture(
                    const unsigned char *data,
                    const glm::ivec2 &size,
                    const int &nChannels
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
                    glGenerateMipmap(GL_TEXTURE_2D); // FIXME: as of now, this is automatic instead of coming from the asset
                    return glTexture;
                }
                
                const uint32_t __glHandle;

            public:
                __Impl(
                    const unsigned char *data,
                    const glm::ivec2 &size,
                    const int &nChannels
                ) :
                __glHandle(__loadTexture(data, size, nChannels))
                {
                    
                }

                ~__Impl() {
                    glDeleteTextures(1, &this->__glHandle);
                }
        };
    
        Texture::Texture(
            const unsigned char *data,
            const glm::ivec2 &size,
            const int &nChannels
        ) :
        __impl(std::make_unique<__Impl>(data, size, nChannels))
        {
    
        }
    
        Texture::~Texture() = default;
    } // namespace resource
} // namespace rhi
