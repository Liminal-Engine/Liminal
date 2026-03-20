#include "__private/__loadShader.hpp"

#include <rhi/Registry.hpp>
#include <parseop/parseop.hpp>
#include <logger/logger.hpp>
#include <fs/InFile.hpp>

namespace gfx {
    namespace __private {

        std::string __readGLSLSource(const fs::Path &path) {
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

        std::string __findVersionDefinitionLine(const std::vector<std::string> &tokenizedSource) {
            for (std::string line : tokenizedSource) {
                if (parseop::startsWith(line, "#version")) return line;
            }
            return "";
        }

        std::string __readTypedShaderSource(
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

        Status __loadShader(const fs::Path &path) {
            // 1. Create name
            std::string name(path.asStr());
            // 2. Check whether resource exists
            if (rhi::Registry::exists(name)) {
                logger::error << "Failed to add shader: resource " << name << " already exists" << std::endl;
                return Status::E_ALREADY_EXISTS;
            }
            // 3. Load data
            // 3.1 Read full source
            std::string fullSource(__readGLSLSource(path));
            if (fullSource.empty()) {
                logger::error << "Shader source is empty: " << path.asStr() << std::endl;
                return Status::E_FILE_CONTENT;
            }
            std::vector<std::string> tokenizedSource = parseop::tokenize(fullSource, '\n');
            // 3.2 Find version definition line ("#version xxx")
            std::string versionDefinition = __findVersionDefinitionLine(tokenizedSource);
            if (versionDefinition.empty()) {
                logger::error << "No version definition found in GLSL source: " << path.asStr() << std::endl;
                return Status::E_FILE_CONTENT;
            }
            // 3.3 Create separate sources
            std::string vertexSource(__readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::VERTEX, versionDefinition));
            std::string geometrySource(__readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::GEOMETRY, versionDefinition));
            std::string fragmentSource(__readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::FRAGMENT, versionDefinition));
            std::string computeSource(__readTypedShaderSource(tokenizedSource, rhi::def::ShaderType::COMPUTE, versionDefinition));
            // 4. Request to add resource
            if (
                rhi::Status loadStatus = rhi::Status::N_OK;
                (loadStatus = rhi::Registry::loadShader(name, vertexSource, geometrySource, fragmentSource, computeSource)) != rhi::Status::OK
            ) {
                logger::error << "Failed to add new shader, status=" << rhi::toStr(loadStatus) << std::endl;
                return Status::E_LOAD;
            }
            return Status::OK;
        }

    } // namespace __private
} // namespace gfx