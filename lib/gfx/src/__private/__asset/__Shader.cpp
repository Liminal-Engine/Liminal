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

                    static std::string __getGLSLSource(const fs::Path &path) {
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

                    static std::string __getVersionDefinitionLine(const std::vector<std::string> &tokenizedSource) {
                        for (std::string line : tokenizedSource) {
                            if (parseop::startsWith(line, "#version")) return line;
                        }
                        return "";
                    }

                    static std::string __getShaderSource(
                        const std::vector<std::string> &tokenizedSource,
                        const rhi::def::ShaderType &shaderType,
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
                        std::string fullSource = __getGLSLSource(absolutePath);
                        if (fullSource.empty()) {
                            logger::debug << "Shader source is empty: " << absolutePathStr << std::endl;
                            return Status::E_FILE_EMPTY;
                        }
                        std::vector<std::string> tokenizedSource = parseop::tokenize(fullSource, '\n');
                        // 2.1 Find location of version definition
                        std::string versionDefinition = __getVersionDefinitionLine(tokenizedSource);
                        if (versionDefinition.empty()) {
                            logger::error << "No version definition in " << absolutePathStr << std::endl;
                            return Status::E_FILE_CONTENT;
                        }
                        this->__vertexSource = __getShaderSource(tokenizedSource, rhi::def::ShaderType::VERTEX, versionDefinition);
                        this->__geometrySource = __getShaderSource(tokenizedSource, rhi::def::ShaderType::GEOMETRY, versionDefinition);
                        this->__fragmentSource = __getShaderSource(tokenizedSource, rhi::def::ShaderType::FRAGMENT, versionDefinition);
                        this->__computeSource = __getShaderSource(tokenizedSource, rhi::def::ShaderType::COMPUTE, versionDefinition);
                        return Status::OK;
                    }

                    Status setRHIHandle(const rhi::def::Handle &RHIHandle) {
                        this->__RHIHandle = RHIHandle;
                        return Status::OK;
                    }

                    const rhi::def::Handle &getRHIHandle(void) const { return this->__RHIHandle; }

                    const std::string &getVertexSource(void) const { return this->__vertexSource; }
                    const std::string &getGeometrySource(void) const { return this->__geometrySource; }
                    const std::string &getFragmentSource(void) const { return this->__fragmentSource; }
                    const std::string &getComputeSource(void) const { return this->__computeSource; }
            };


            __Shader::__Shader(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Shader::~__Shader() = default;

            Status __Shader::copy(const __Shader &other) { return this->__impl->copy(*other.__impl); }

            Status __Shader::load(const fs::Path &path) { return this->__impl->load(path); }

            Status __Shader::setRHIHandle(const rhi::def::Handle &RHIHandle) { return this->__impl->setRHIHandle(RHIHandle); }
            const rhi::def::Handle &__Shader::getRHIHandle(void) const { return this->__impl->getRHIHandle(); }

            const std::string &__Shader::getVertexSource(void) const { return this->__impl->getVertexSource(); }
            const std::string &__Shader::getGeometrySource(void) const { return this->__impl->getGeometrySource(); }
            const std::string &__Shader::getFragmentSource(void) const { return this->__impl->getFragmentSource(); }
            const std::string &__Shader::getComputeSource(void) const { return this->__impl->getComputeSource(); }
        } // namespace __aset
    } // namespace __private
} // namespace gfx
