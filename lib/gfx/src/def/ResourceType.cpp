#include "def/ResourceType.hpp"

namespace gfx {
    std::string toStr(def::ResourceType resourceType) noexcept {
        switch (resourceType) {
            case def::ResourceType::MESH: return "MESH";
            case def::ResourceType::SHADER: return "SHADER";
        }
        return "UNKNOWN";
    }
} // namespace gfx
