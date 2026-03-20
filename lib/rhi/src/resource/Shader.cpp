#include "resource/Shader.hpp"
#include "def/ShaderType.hpp"

#include <glad/glad.h>
#include <logger/logger.hpp>

namespace rhi {
    namespace resource {
        class Shader::__Impl {
            private:

                static uint32_t __compileShaderSource(const std::string &source, def::ShaderType type) {
                    // 1. Check if source is empty
                    if (source.empty()) {
                        logger::debug << "Source is empty for this shader type, nothing to compile" << std::endl;
                        return 0;
                    }
                    const char *sourceCStr = source.c_str();
                    uint32_t shader = glCreateShader(def::toGLenum(type));
                    glShaderSource(shader, 1, &sourceCStr, NULL);
                    glCompileShader(shader);
                    int success = 0;
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                    if (!success) {
                        char infoLog[512];
                        glGetShaderInfoLog(shader, 512, NULL, infoLog);
                        logger::error << "Failed to compile " << def::toStr(type) << " shader:\n" <<
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
                    uint32_t vertexShader = __compileShaderSource(vertexSource, def::ShaderType::VERTEX);
                    logger::debug << "Compiling GEOMETRY shader" << std::endl;
                    uint32_t geometryShader = __compileShaderSource(geometrySource, def::ShaderType::GEOMETRY);
                    logger::debug << "Compiling FRAGMENT shader" << std::endl;
                    uint32_t fragmentShader = __compileShaderSource(fragmentSource, def::ShaderType::FRAGMENT);
                    logger::debug << "Compiling COMPUTE shader" << std::endl;
                    uint32_t computeShader = __compileShaderSource(computeSource, def::ShaderType::COMPUTE);
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
                        char infoLog[512];
                        glGetProgramInfoLog(program, 512, NULL, infoLog);
                        logger::error << "Failed to link program:\n" << std::string(infoLog) << std::endl;
                        glDeleteProgram(program);
                        return 0;
                    }
                    return program;
                }

                uint32_t __glProgramHandle;
            
            public:
                __Impl(
                    const std::string &vertexSource,
                    const std::string &geometrySource,
                    const std::string &fragmentSource,
                    const std::string &computeSource
                ) :
                __glProgramHandle(__loadProgram(vertexSource, geometrySource, fragmentSource, computeSource))
                {}

                ~__Impl() {
                    if (this->__glProgramHandle) glDeleteProgram(this->__glProgramHandle);
                }

                void use(void) const {
                    glUseProgram(this->__glProgramHandle);
                }
        };

        Shader::Shader(
            const std::string &vertexSource,
            const std::string &geometrySource,
            const std::string &fragmentSource,
            const std::string &computeSource
        ) : __impl(std::make_unique<__Impl>(vertexSource, geometrySource, fragmentSource, computeSource)) {}
        Shader::~Shader() = default;
        Shader::Shader(Shader&&) noexcept = default;
        Shader& Shader::operator=(Shader&&) noexcept = default;
        
        void Shader::use(void) const { this->__impl->use(); }


    } // namespace resource
} // namespace rhi
