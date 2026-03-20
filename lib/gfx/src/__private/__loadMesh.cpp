#include "__private/__loadMesh.hpp"

#include <logger/logger.hpp>
#include <rhi/Status.hpp>
#include <rhi/Registry.hpp>
#include <rhi/def/Vertex.hpp>

namespace gfx {
    namespace __private {
        Status __loadMesh(const fs::Path &path) {
            // 1. Create name
            std::string name(path.asStr());
            logger::debug << "GFX loading mesh " << name << std::endl;
            // 2. Check whether resource exists
            if (rhi::Registry::exists(name)) {
                logger::error << "Failed to add mesh: resource " << name << " already exists" << std::endl;
                return Status::E_ALREADY_EXISTS;
            }
            // 3. Load data
            rhi::def::Vertex v1(glm::vec3(0.0f, 0.5f, 0.0f));
            rhi::def::Vertex v2(glm::vec3(0.5f, -0.5f, 0.0f));
            rhi::def::Vertex v3(glm::vec3(-0.5f, -0.5f, 0.0f));
            std::vector<rhi::def::Vertex> vertices{v1, v2, v3};
            std::vector<uint32_t> indices{0, 1, 2};
            // 4. Request to add resource
            if (
                rhi::Status loadStatus = rhi::Status::N_OK;
                (loadStatus = rhi::Registry::loadMesh(name, vertices, indices)) != rhi::Status::OK
            ) {
                logger::error << "Failed to add new mesh, status=" << rhi::toStr(loadStatus) << std::endl;
                return Status::E_LOAD;
            }
            return Status::OK;
        }      
    } // namespace __private
} // namespace gfx
