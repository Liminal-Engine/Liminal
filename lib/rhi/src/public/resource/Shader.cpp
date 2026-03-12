#include "resource/Shader.hpp"
#include "ShaderType.hpp"
#include "__private/__config.hpp"

#include <logger/logger.hpp>
#include <fs/InFile.hpp>

#include <glad/glad.h>

namespace rhi {
    namespace resource {
        
        class Shader::__Impl {
            private:
                uint32_t __handle;                

                static std::string __shaderTypeToStr(const ShaderType &type) {
                    switch (type) {
                        case ShaderType::VERTEX: return "VERTEX";
                        case ShaderType::GEOMETRY: return "GEOMETRY";
                        case ShaderType::FRAGMENT: return "FRAGMENT";
                        case ShaderType::COMPUTE: return "COMPUTE";
                        default: return "UNKNOWN";
                    }
                    return "UNKNOWN";
                }

                static GLenum __shaderTypeToGLenum(const ShaderType &type) {
                    switch (type) {
                        case ShaderType::VERTEX: return GL_VERTEX_SHADER;
                        case ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER;
                        case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
                        case ShaderType::COMPUTE: return GL_COMPUTE_SHADER;            
                        default: return GL_ZERO;
                    }
                    return GL_ZERO;
                }

                static std::string __getShaderSource(const fs::Path &path) {
                    fs::InFile shaderFile(path);
                    if (shaderFile.open() != fs::Status::OK) {
                        logger::error << "Failed to open shader file: " << path.asStr() << std::endl;
                        return "";
                    }
                    if (shaderFile.read() != fs::Status::OK) {
                        logger::error << "Failed to read shader file: " << path.asStr() << std::endl;
                        return "";
                    }
                    if (shaderFile.close() != fs::Status::OK) {
                        logger::error << "Failed to close shader file: " << path.asStr() << std::endl;
                    }
                    return shaderFile.getContent();
                }

                static uint32_t __compileShaderSource(const std::string &source, const ShaderType &type) {
                    // 1. Check if source is empty
                    if (source.empty()) {
                        logger::error << "Source is empty, nothing to compile" << std::endl;
                        return 0;
                    }
                    // 2. Check if source contains the wanted shader type, most shaders does not contains all categories
                    std::string typeStr(__shaderTypeToStr(type));
                    if (source.find("#ifdef " + typeStr) == std::string::npos) {
                        logger::debug << typeStr << " not defined in shader source, nothing to compile for the shader type: " << typeStr << std::endl;
                        return 0;
                    }
                    // 3. Find the #version definition in the source
                    std::string sourceCpy(source); // create a modifyable copy
                    size_t versionPos = sourceCpy.find("#version");
                    if (versionPos == std::string::npos) {
                        logger::error << "Version definition not find in source, aborting compilation..." << std::endl;
                        return 0;
                    }
                    size_t endOfVersionLine = sourceCpy.find('\n', versionPos);
                    if (endOfVersionLine == std::string::npos) {
                        logger::error << "No new line found after version definition, aborting comilation..." << std::endl;
                        return 0;
                    }
                    // 4. Insert the shader type definition in the source modifyable copy
                    sourceCpy.insert(endOfVersionLine + 1, "#define " + typeStr + "\n");
                    // 5. Compile
                    const char *sourceCpyCStr = sourceCpy.c_str();
                    uint32_t shader = glCreateShader(__shaderTypeToGLenum(type));
                    glShaderSource(shader, 1, &sourceCpyCStr, NULL);
                    glCompileShader(shader);
                    int success = 0;
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                    if (!success) {
                        char infoLog[__private::__config::OPENGL_INFO_LOG_LENGTH];
                        glGetShaderInfoLog(shader, __private::__config::OPENGL_INFO_LOG_LENGTH, NULL, infoLog);
                        logger::error << "Failed to compile " << typeStr << " shader:\n" <<
                        std::string(infoLog) << std::endl;
                        return 0;
                    }
                    return shader;
                }

                static uint32_t __loadProgram(const fs::Path &path) {
                    // 1. Create cleaned absolute path
                    fs::Path absolutePath(path);
                    absolutePath.toAbsolute();
                    absolutePath.clean();
                    std::string absolutePathStr(absolutePath.asStr());
                    // 2. Read shader file source
                    std::string source = __getShaderSource(absolutePath);
                    // 3. Compile
                    logger::debug << "Compiling VERTEX shader for " << absolutePathStr << std::endl;
                    uint32_t vertexShader = __compileShaderSource(source, ShaderType::VERTEX);
                    logger::debug << "Compiling GEOMETRY shader for " << absolutePathStr << std::endl;
                    uint32_t geometryShader = __compileShaderSource(source, ShaderType::GEOMETRY);
                    logger::debug << "Compiling FRAGMENT shader for " << absolutePathStr << std::endl;
                    uint32_t fragmentShader = __compileShaderSource(source, ShaderType::FRAGMENT);
                    logger::debug << "Compiling COMPUTE shader for " << absolutePathStr << std::endl;
                    uint32_t computeShader = __compileShaderSource(source, ShaderType::COMPUTE);
                    // 4. Link
                    const uint32_t program = glCreateProgram();
                    if (vertexShader != 0) glAttachShader(program, vertexShader);
                    if (geometryShader != 0) glAttachShader(program, geometryShader);
                    if (fragmentShader != 0) glAttachShader(program, fragmentShader);
                    if (computeShader != 0) glAttachShader(program, computeShader);
                    glLinkProgram(program);
                    int success = 0;
                    glGetProgramiv(program, GL_LINK_STATUS, &success);
                    if (!success) {
                        char infoLog[__private::__config::OPENGL_INFO_LOG_LENGTH];
                        glGetProgramInfoLog(program, __private::__config::OPENGL_INFO_LOG_LENGTH, NULL, infoLog);
                        logger::error << "Failed to link program for shader " << absolutePathStr << " :\n" <<
                        std::string(infoLog) << std::endl;
                        return 0;
                    }
                    return program;
                }
    
            public:
                __Impl(const fs::Path &path) :
                __handle(__loadProgram(path))
                {
                    
                }

                ~__Impl() {
                    if (this->__handle) glDeleteProgram(this->__handle);
                }

                void use(void) const {
                    glUseProgram(this->__handle);
                }
        };
    
        Shader::Shader(const fs::Path &path) :
        __impl(std::make_unique<__Impl>(path))
        {
    
        }
    
        Shader::~Shader() = default;

        void Shader::use(void) const { this->__impl->use(); }
    } // namespace resource
} // namespace rhi
