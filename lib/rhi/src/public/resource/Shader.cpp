#include "resource/Shader.hpp"
#include "__private/__config.hpp"
#include "ShaderType.hpp"

#include <logger/logger.hpp>
#include <fs/InFile.hpp>

#include <glad/glad.h>

namespace rhi {
    namespace resource {
        
        class Shader::__Impl {
            private:
                uint32_t __handle;        


                // static std::string __getShaderSource(const fs::Path &path) {
                //     fs::InFile shaderFile(path);
                //     if (shaderFile.open() != fs::Status::OK) {
                //         logger::error << "Failed to open shader file: " << path.asStr() << std::endl;
                //         return "";
                //     }
                //     if (shaderFile.read() != fs::Status::OK) {
                //         logger::error << "Failed to read shader file: " << path.asStr() << std::endl;
                //         return "";
                //     }
                //     if (shaderFile.close() != fs::Status::OK) {
                //         logger::error << "Failed to close shader file: " << path.asStr() << std::endl;
                //     }
                //     return shaderFile.getContent();
                // }

                static uint32_t __compileShaderSource(const std::string &source, const ShaderType &type) {
                    // 1. Check if source is empty
                    if (source.empty()) {
                        logger::error << "Source is empty, nothing to compile" << std::endl;
                        return 0;
                    }
                    const char *sourceCStr = source.c_str();
                    uint32_t shader = glCreateShader(toGLenum(type));
                    glShaderSource(shader, 1, &sourceCStr, NULL);
                    glCompileShader(shader);
                    int success = 0;
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                    if (!success) {
                        char infoLog[__private::__config::OPENGL_INFO_LOG_LENGTH];
                        glGetShaderInfoLog(shader, __private::__config::OPENGL_INFO_LOG_LENGTH, NULL, infoLog);
                        logger::error << "Failed to compile " << toStr(type) << " shader:\n" <<
                        std::string(infoLog) << std::endl;
                        glDeleteShader(shader);
                        return 0;
                    }
                    return shader;
                }

                static uint32_t __loadProgram(
                    const std::string &vertexSource,
                    const std::string &geometrySource,
                    const std::string &fragmentSource,
                    const std::string &computeSource
                ) {
                    // 1. Create cleaned absolute path
                    logger::debug << "Compiling VERTEX shader" << std::endl;
                    uint32_t vertexShader = __compileShaderSource(vertexSource, ShaderType::VERTEX);
                    logger::debug << "Compiling GEOMETRY shader" << std::endl;
                    uint32_t geometryShader = __compileShaderSource(geometrySource, ShaderType::GEOMETRY);
                    logger::debug << "Compiling FRAGMENT shader" << std::endl;
                    uint32_t fragmentShader = __compileShaderSource(fragmentSource, ShaderType::FRAGMENT);
                    logger::debug << "Compiling COMPUTE shader" << std::endl;
                    uint32_t computeShader = __compileShaderSource(computeSource, ShaderType::COMPUTE);
                    // 4. Link
                    const uint32_t program = glCreateProgram();
                    if (vertexShader != 0) glAttachShader(program, vertexShader);
                    if (geometryShader != 0) glAttachShader(program, geometryShader);
                    if (fragmentShader != 0) glAttachShader(program, fragmentShader);
                    if (computeShader != 0) glAttachShader(program, computeShader);
                    glLinkProgram(program);

                    // Shader objects are only needed for linking; free them afterwards.
                    if (vertexShader != 0) glDeleteShader(vertexShader);
                    if (geometryShader != 0) glDeleteShader(geometryShader);
                    if (fragmentShader != 0) glDeleteShader(fragmentShader);
                    if (computeShader != 0) glDeleteShader(computeShader);

                    int success = 0;
                    glGetProgramiv(program, GL_LINK_STATUS, &success);
                    if (!success) {
                        char infoLog[__private::__config::OPENGL_INFO_LOG_LENGTH];
                        glGetProgramInfoLog(program, __private::__config::OPENGL_INFO_LOG_LENGTH, NULL, infoLog);
                        logger::error << "Failed to link program:\n" << std::string(infoLog) << std::endl;
                        glDeleteProgram(program);
                        return 0;
                    }
                    return program;
                }
    
            public:
                __Impl(
                    const std::string &vertexSource,
                    const std::string &geometrySource,
                    const std::string &fragmentSource,
                    const std::string &computeSource
                ) :
                __handle(__loadProgram(vertexSource, geometrySource, fragmentSource, computeSource))
                {
                    
                }

                ~__Impl() {
                    if (this->__handle) glDeleteProgram(this->__handle);
                }

                void use(void) const {
                    glUseProgram(this->__handle);
                }
        };
    
        Shader::Shader(
            const std::string &vertexSource,
            const std::string &geometrySource,
            const std::string &fragmentSource,
            const std::string &computeSource
        ) :
        __impl(std::make_unique<__Impl>(vertexSource, geometrySource, fragmentSource, computeSource))
        {
    
        }
    
        Shader::~Shader() = default;

        void Shader::use(void) const { this->__impl->use(); }
    } // namespace resource
} // namespace rhi
