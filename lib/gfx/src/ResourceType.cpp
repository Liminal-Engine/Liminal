#include "ResourceType.hpp"

namespace gfx {
    std::string toStr(const ResourceType &resourceType) noexcept {
        switch (resourceType) {
            case ResourceType::MESH: return "MESH";
            case ResourceType::SHADER: return "SHADER";
        }
        return "UNKNOWN";
    }
} // namespace gfx
