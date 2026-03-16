#include "__private/__asset/__Shader.hpp"

#include <rhi/def/ShaderType.hpp>
#include <logger/logger.hpp>
#include <fs/InFile.hpp>
#include <parseop/parseop.hpp>

#include <unordered_map>
#include <string>

namespace gfx {
    namespace __private {
        namespace __asset {
            class __Shader::__Impl {
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

                    static std::string __generateVersionDefinitionLine(const std::vector<std::string> &tokenizedSource) {
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

                    rhi::def::Handle __RHIHandle;
                    std::unordered_map<std::string, int> __uniformLocations;
                    std::string __vertexSource;
                    std::string __geometrySource;
                    std::string __fragmentSource;
                    std::string __computeSource;

                public:
                    __Impl(void) :
                    __RHIHandle(rhi::def::NULL_HANDLE),
                    __uniformLocations(),
                    __vertexSource(""),
                    __geometrySource(""),
                    __fragmentSource(""),
                    __computeSource("")
                    {

                    }

                    Status copy(const __Impl &other) {
                        this->__RHIHandle = other.__RHIHandle;
                        this->__uniformLocations = other.__uniformLocations;
                        return Status::OK;
                    }

                    Status load(const fs::Path &path) {
                        // 1. Create absolute path (mainly for log purposes)
                        fs::Path absolutePath(path);
                        absolutePath.toAbsolute();
                        absolutePath.clean();
                        std::string absolutePathStr(absolutePath.asStr());
                        logger::debug << "Creating shader asset for: " << absolutePathStr << std::endl;
                        // 2. Read source
                        std::string fullSource = __readGLSLSource(absolutePath);
                        if (fullSource.empty()) {
                            logger::debug << "Shader source is empty: " << absolutePathStr << std::endl;
                            return Status::E_FILE_EMPTY;
                        }
                        std::vector<std::string> tokenizedSource = parseop::tokenize(fullSource, '\n');
                        // 2.1 Find location of version definition
                        std::string versionDefinition = __generateVersionDefinitionLine(tokenizedSource);
                        if (versionDefinition.empty()) {
                            logger::error << "No version definition in " << absolutePathStr << std::endl;
                            return Status::E_FILE_CONTENT;
                        }
                        this->__vertexSource = __readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::VERTEX, versionDefinition);
                        this->__geometrySource = __readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::GEOMETRY, versionDefinition);
                        this->__fragmentSource = __readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::FRAGMENT, versionDefinition);
                        this->__computeSource = __readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::COMPUTE, versionDefinition);
                        return Status::OK;
                    }

                    Status setRHIHandle(rhi::def::Handle RHIHandle) {
                        this->__RHIHandle = RHIHandle;
                        return Status::OK;
                    }

                    rhi::def::Handle getRHIHandle(void) const { return this->__RHIHandle; }

                    const std::string &getSource(rhi::def::ShaderType type) const {
                        switch (type) {
                            case rhi::def::ShaderType::VERTEX: return this->__vertexSource;
                            case rhi::def::ShaderType::GEOMETRY: return this->__geometrySource;
                            case rhi::def::ShaderType::FRAGMENT: return this->__fragmentSource;
                            case rhi::def::ShaderType::COMPUTE: return this->__computeSource;
                        }
                        return "";
                    }
            };


            __Shader::__Shader(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Shader::~__Shader() = default;

            Status __Shader::copy(const __Shader &other) { return this->__impl->copy(*other.__impl); }

            Status __Shader::load(const fs::Path &path) { return this->__impl->load(path); }

            Status __Shader::setRHIHandle(rhi::def::Handle RHIHandle) { return this->__impl->setRHIHandle(RHIHandle); }
            rhi::def::Handle __Shader::getRHIHandle(void) const { return this->__impl->getRHIHandle(); }

            const std::string &__Shader::getSource(rhi::def::ShaderType type) const { return this->__impl->getSource(type); }
        } // namespace __aset
    } // namespace __private
} // namespace gfx
