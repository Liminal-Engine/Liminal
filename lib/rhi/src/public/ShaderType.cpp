#include "ShaderType.hpp"

namespace rhi {

    std::string toStr(const ShaderType &type) noexcept {
        switch (type) {
            case ShaderType::VERTEX:   return "VERTEX";
            case ShaderType::GEOMETRY: return "GEOMETRY";
            case ShaderType::FRAGMENT: return "FRAGMENT";
            case ShaderType::COMPUTE:  return "COMPUTE";
        }
        return "UNKNOWN";
    }

    GLenum toGLenum(const ShaderType &type) noexcept {
        switch (type) {
            case ShaderType::VERTEX: return GL_VERTEX_SHADER;
            case ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER;
            case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
            case ShaderType::COMPUTE: return GL_COMPUTE_SHADER;
        }
        return GL_ZERO;
    }

} // namespace rhi
