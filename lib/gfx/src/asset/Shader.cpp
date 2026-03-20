#include "asset/Shader.hpp"

#include <rhi/def/ShaderType.hpp>
#include <rhi/def/Uniform.hpp>
#include <logger/logger.hpp>
#include <fs/InFile.hpp>
#include <parseop/parseop.hpp>

#include <vector>
#include <string>

#include <glad/glad.h>

namespace gfx {
    namespace asset {
        class Shader::__Impl {
            private:
    
                static std::string __readGLSLSource(const fs::Path &path) {
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
    
                static std::string __findVersionDefinitionLine(const std::vector<std::string> &tokenizedSource) {
                    for (std::string line : tokenizedSource) {
                        if (parseop::startsWith(line, "#version")) return line;
                    }
                    return "";
                }
    
                static std::string __readTypedShaderSource(
                    const std::vector<std::string> &tokenizedSource,
                    rhi::def::ShaderType shaderType,
                    const std::string &versionDefinition
                ) {
                    std::string shaderTypeDefinition = "#ifdef " + rhi::def::toStr(shaderType);
                    std::vector<std::string> rawRes{};
    
                    for (size_t i = 0; i < tokenizedSource.size(); i++) {
                        if (tokenizedSource[i] == shaderTypeDefinition) {
                            while (i++ < tokenizedSource.size() && parseop::startsWith(tokenizedSource[i], "#endif") == false) {
                                rawRes.push_back(tokenizedSource[i]);
                            }
                            break;
                        }
                    }
                    if (rawRes.empty()) return "";
                    rawRes.insert(rawRes.begin(), versionDefinition);
                    return parseop::join(rawRes, "\n");
                }
    
                static uint32_t __compileShaderSource(const std::string &source, rhi::def::ShaderType type) {
                    // 1. Check if source is empty
                    if (source.empty()) {
                        logger::debug << "Source is empty for this shader type, nothing to compile" << std::endl;
                        return 0;
                    }
                    const char *sourceCStr = source.c_str();
                    uint32_t shader = glCreateShader(rhi::def::toGLenum(type));
                    glShaderSource(shader, 1, &sourceCStr, NULL);
                    glCompileShader(shader);
                    int success = 0;
                    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                    if (!success) {
                        char infoLog[512];
                        glGetShaderInfoLog(shader, 512, NULL, infoLog);
                        logger::error << "Failed to compile " << rhi::def::toStr(type) << " shader:\n" <<
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
                    uint32_t vertexShader = __compileShaderSource(vertexSource, rhi::def::ShaderType::VERTEX);
                    logger::debug << "Compiling GEOMETRY shader" << std::endl;
                    uint32_t geometryShader = __compileShaderSource(geometrySource, rhi::def::ShaderType::GEOMETRY);
                    logger::debug << "Compiling FRAGMENT shader" << std::endl;
                    uint32_t fragmentShader = __compileShaderSource(fragmentSource, rhi::def::ShaderType::FRAGMENT);
                    logger::debug << "Compiling COMPUTE shader" << std::endl;
                    uint32_t computeShader = __compileShaderSource(computeSource, rhi::def::ShaderType::COMPUTE);
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
    
                static std::vector<rhi::def::Uniform> __loadUniforms(uint32_t handle) {
                    GLint count;
                    glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &count);
                    GLint maxLength;
                    glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLength);
                    std::vector<char> nameBuffer(maxLength);
                    std::vector<rhi::def::Uniform> uniforms{};
    
                    for (GLint i = 0; i < count; i++) {
                        GLint size = 0;
                        GLenum type = 0;
                        GLint length = 0;
                        glGetActiveUniform(handle, i, maxLength, &length, &size, &type, nameBuffer.data());
                        std::string name(nameBuffer.data(), length);
                        GLint location = glGetUniformLocation(handle, name.c_str());
                        if (location != -1) {
                            uniforms.push_back(rhi::def::Uniform(name, location, type));
                        }
                    }
                    uniforms.shrink_to_fit();
                    return uniforms;
                }
    
                // Engine part
                fs::Path __path;
                std::string __vertexSource;
                std::string __geometrySource;
                std::string __fragmentSource;
                std::string __computeSource;
                std::vector<rhi::def::Uniform> __uniforms; // tihs depends on __glHandle
                bool __loaded;
                // OpenGL part
                uint32_t __glHandle;
    
            public:
                __Impl(void) :
                __path(),
                __vertexSource(""),
                __geometrySource(""),
                __fragmentSource(""),
                __computeSource(""),
                __uniforms{},
                __loaded(false),
                __glHandle(0)
                {
                    
                }
    
                ~__Impl() {
                    if (this->__glHandle) glDeleteProgram(this->__glHandle);
                    this->__uniforms.clear();
                }
    
                Status load(const fs::Path &path) {
                    // Engine part
                    fs::Path absolutePath(path);
                    absolutePath.toAbsolute();
                    absolutePath.clean();
                    this->__path = absolutePath;
                    logger::debug << "Loading shader from: " << absolutePath.asStr() << std::endl;
                    // 1. Read source
                    std::string fullSource = __readGLSLSource(absolutePath);
                    if (fullSource.empty()) {
                        logger::error << "Shader source is empty: " << absolutePath.asStr() << std::endl;
                        return Status::E_FILE_CONTENT;
                    }                
                    std::vector<std::string> tokenizedSource = parseop::tokenize(fullSource, '\n');
                    // 2. Find location of version definition ("#version xxx")
                    std::string versionDefinition = __findVersionDefinitionLine(tokenizedSource);
                    if (versionDefinition.empty()) {
                        logger::error << "No version definition found in GLSL source: " << absolutePath.asStr() << std::endl;
                        return Status::E_FILE_CONTENT;
                    }
                    this->__vertexSource = __readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::VERTEX, versionDefinition);
                    this->__geometrySource = __readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::GEOMETRY, versionDefinition);
                    this->__fragmentSource = __readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::FRAGMENT, versionDefinition);
                    this->__computeSource = __readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::COMPUTE, versionDefinition);
                    // OpenGL part
                    // 3. Load program
                    this->__glHandle = __loadProgram(this->__vertexSource, this->__geometrySource, this->__fragmentSource, this->__computeSource);
                    // 4. Load uniforms infos from program
                    this->__uniforms = __loadUniforms(this->__glHandle);
                    this->__loaded = true;
                    return Status::OK;
                }
    
                bool isLoaded(void) const { return this->__loaded; }

                void use(void) const {
                    glUseProgram(this->__glHandle);
                }
        };
    
        Shader::Shader(void) : __impl(std::make_unique<__Impl>()) {}
        Shader::~Shader() = default;
    
        Status Shader::load(const fs::Path &path) { return this->__impl->load(path); }
        bool Shader::isLoaded(void) const { return this->__impl->isLoaded(); }
        void Shader::use(void) const { this->__impl->use(); }
    } // namespace asset
} // namespace gfx
