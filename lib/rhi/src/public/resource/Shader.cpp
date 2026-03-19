#include "resource/Shader.hpp"
#include "__private/__config.hpp"
#include "def/ShaderType.hpp"

#include <logger/logger.hpp>
#include <fs/InFile.hpp>

#include <glad/glad.h>

namespace rhi {
    namespace resource {
        
        class Shader::__Impl {
            private:
                const def::Handle __rhiHandle;
                const uint32_t __glHandle;
                const std::vector<def::Uniform> __uniforms;


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
                        char infoLog[__private::__config::OPENGL_INFO_LOG_LENGTH];
                        glGetProgramInfoLog(program, __private::__config::OPENGL_INFO_LOG_LENGTH, NULL, infoLog);
                        logger::error << "Failed to link program:\n" << std::string(infoLog) << std::endl;
                        glDeleteProgram(program);
                        return 0;
                    }
                    return program;
                }
    
                static std::vector<def::Uniform> __loadUniforms(uint32_t handle) {
                    GLint count;
                    glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &count);
                    GLint maxLength;
                    glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
                    std::vector<char> nameBuffer(maxLength);
                    std::vector<def::Uniform> uniforms{};

                    for (GLint i = 0; i < count; i++) {
                        GLint size = 0;
                        GLenum type = 0;
                        GLint length = 0;
                        glGetActiveUniform(handle, i, maxLength, &length, &size, &type, nameBuffer.data());
                        std::string name(nameBuffer.data(), length);
                        GLint location = glGetUniformLocation(handle, name.c_str());
                        if (location != -1) {
                            uniforms.push_back(def::Uniform(name, location, type));
                        }
                    }
                    uniforms.shrink_to_fit();
                    return uniforms;
                }

            public:
                __Impl(
                    const std::string &vertexSource,
                    const std::string &geometrySource,
                    const std::string &fragmentSource,
                    const std::string &computeSource,
                    def::Handle handle
                ) :
                __rhiHandle(handle),
                __glHandle(__loadProgram(vertexSource, geometrySource, fragmentSource, computeSource)),
                __uniforms(__loadUniforms(this->__glHandle))
                {
                    
                }

                ~__Impl() {
                    if (this->__glHandle) glDeleteProgram(this->__glHandle);
                }

                void use(const std::vector<def::Uniform> &uniforms = {}) const {
                    glUseProgram(this->__glHandle);
                    for (const def::Uniform &uniform : uniforms) {
                        if (const int *value = std::get_if<int>(&uniform.value)) {
                            glUniform1i(uniform.location, *value);
                        } else if (const float *value = std::get_if<float>(&uniform.value)) {
                            glUniform1f(uniform.location, *value);
                        } else if (const glm::vec3* value = std::get_if<glm::vec3>(&uniform.value)) {
                            glUniform3f(uniform.location, value->x, value->y, value->z);
                        }
                    }
                }

                const std::vector<def::Uniform> &getUniforms(void) const { return this->__uniforms; }

                def::Handle getRHIHandle(void) const { return this->__rhiHandle; }
        };
    
        Shader::Shader(
            const std::string &vertexSource,
            const std::string &geometrySource,
            const std::string &fragmentSource,
            const std::string &computeSource,
            def::Handle handle
        ) :
        __impl(std::make_unique<__Impl>(vertexSource, geometrySource, fragmentSource, computeSource, handle))
        {
    
        }
    
        Shader::~Shader() = default;

        void Shader::use(const std::vector<def::Uniform> &uniforms) const { this->__impl->use(uniforms); }
        const std::vector<def::Uniform> &Shader::getUniforms(void) const { return this->__impl->getUniforms(); }
        def::Handle Shader::getRHIHandle(void) const { return this->__impl->getRHIHandle(); }
    } // namespace resource
} // namespace rhi
