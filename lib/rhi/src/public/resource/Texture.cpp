#include "resource/Texture.hpp"

#include <logger/logger.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <glad/glad.h>

namespace rhi {
    namespace resource {
        
        class Texture::__Impl {
            private:

                struct __ImageData {
                    __ImageData(void) :
                    width(0),
                    height(0),
                    nChannels(0),
                    bytes(nullptr)
                    {}

                    int width;
                    int height;
                    int nChannels;
                    unsigned char *bytes;
                };
            
                static __ImageData __loadImageData(const fs::Path &path) {
                    __ImageData data;
                    data.bytes = stbi_load(path.asStr().c_str(), &data.width, &data.height, &data.nChannels, 0);
                    return data;
                }

                static uint32_t __loadTexture(const fs::Path &path) {
                    fs::Path absolutePath(path);
                    absolutePath.toAbsolute();
                    absolutePath.clean();
                    logger::debug << "Loading texture: " << absolutePath.asStr() << std::endl;
                    __ImageData data = __loadImageData(absolutePath);
                    if (data.bytes == nullptr) {
                        logger::error << "Failed to load image: " << absolutePath.asStr() << std::endl;
                        return 0;
                    }

                    GLenum format = GL_RGB;
                    GLenum internalFormat = GL_RGB8;
                    if (data.nChannels == 1) {
                        format = GL_RED;
                        internalFormat = GL_R8;
                    } else if (data.nChannels == 3) {
                        format = GL_RGB;
                        internalFormat = GL_RGB8;
                    } else if (data.nChannels == 4) {
                        format = GL_RGBA;
                        internalFormat = GL_RGBA8;
                    } else {
                        logger::error << "Unknown number of channels, cannot load texture: " << absolutePath.asStr() << std::endl;
                        return 0;
                    }

                    // create gl object
                    uint32_t glTexture = 0;
                    glGenTextures(1, &glTexture);
                    glBindTexture(GL_TEXTURE_2D, glTexture);
                    // define wrapping and filtering
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    // bind image to texture and generate mipmap
                    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
                    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, data.width, data.height, 0, format, GL_UNSIGNED_BYTE, data.bytes);
                    glGenerateMipmap(GL_TEXTURE_2D);
                    stbi_image_free(data.bytes);
                    return glTexture;
                }
                
                uint32_t __handle;

            public:
                __Impl(const fs::Path &path) :
                __handle(__loadTexture(path))
                {
                    
                }

                ~__Impl() {
                    glDeleteTextures(1, &this->__handle);
                }
        };
    
        Texture::Texture(const fs::Path &path) :
        __impl(std::make_unique<__Impl>(path))
        {
    
        }
    
        Texture::~Texture() = default;
    } // namespace resource
} // namespace rhi
