#include "gfx.hpp"
#include "__private/__loadMesh.hpp"
#include "__private/__loadShader.hpp"

#include <rhi/Registry.hpp>
#include <logger/logger.hpp>
#include <rhi/def/Vertex.hpp>

#include <vector>
#include <cstdint>

namespace gfx {
    Status load(ResourceType resourceType, const fs::Path &path) {
        switch (resourceType) {
            case ResourceType::MESH: return __private::__loadMesh(path);
            case ResourceType::SHADER: return __private::__loadShader(path);
        }
        return Status::E_UNKNOWN_RESOURCE_TYPE;
    }
} // namespace gfx
