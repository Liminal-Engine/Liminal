#include "resource/Shader.hpp"
#include "def/ShaderType.hpp"
#include "def/Uniform.hpp"

#include <glad/glad.h>
#include <logger/logger.hpp>

#include <unordered_map>

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

                static std::unordered_map<std::string, size_t> __loadUniformsLookuptTable(const std::vector<def::Uniform> &uniforms) {
                    std::unordered_map<std::string, size_t> lookupTable{};
                    for (size_t i = 0; i < uniforms.size(); i++) {
                        if (lookupTable.contains(uniforms[i].name)) logger::error << "Several uniforms with the same name: " << uniforms[i].name << std::endl;
                        lookupTable[uniforms[i].name] = i;
                    }
                    return lookupTable;
                }

                uint32_t __glProgramHandle;
                mutable std::vector<def::Uniform> __uniforms;
                std::unordered_map<std::string, size_t> __uniformsLookupTable;
            
            public:
                __Impl(
                    const std::string &vertexSource,
                    const std::string &geometrySource,
                    const std::string &fragmentSource,
                    const std::string &computeSource
                ) :
                __glProgramHandle(__loadProgram(vertexSource, geometrySource, fragmentSource, computeSource)),
                __uniforms(__loadUniforms(this->__glProgramHandle)),
                __uniformsLookupTable(__loadUniformsLookuptTable(this->__uniforms))
                {}

                ~__Impl() {
                    if (this->__glProgramHandle) glDeleteProgram(this->__glProgramHandle);
                }

                void use(void) const {
                    glUseProgram(this->__glProgramHandle);
                }

                void setUniform(const std::string &name, def::UniformValue value) const {
                    if (this->__uniformsLookupTable.contains(name) == false) {
                        logger::error << "Failed to set uniform: \"" << name << "\" does not exists" << std::endl;
                        return;
                    }
                    size_t index(this->__uniformsLookupTable.at(name));
                    this->__uniforms[index].value = value;
                    const GLint location = this->__uniforms[index].location;

                    std::visit([location](auto &&typedValue) {
                        using T = std::decay_t<decltype(typedValue)>;
                        if constexpr (std::is_same_v<T, int>) glUniform1i(location, typedValue);
                        else if constexpr (std::is_same_v<T, float>) glUniform1f(location, typedValue);
                        else if constexpr (std::is_same_v<T, glm::vec3>) glUniform3fv(location, 1, &typedValue[0]);
                        else logger::error << "Unsupported uniform type";
                    }, value);
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

        void Shader::setUniform(const std::string &name, def::UniformValue value) const { this->__impl->setUniform(name, value); }


    } // namespace resource
} // namespace rhi
