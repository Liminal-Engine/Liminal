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
            // Pyramide (tétraèdre)
            rhi::def::Vertex apex(glm::vec3(0.0f, 0.5f, 0.0f));
            rhi::def::Vertex base1(glm::vec3(0.5f, -0.5f, 0.5f));
            rhi::def::Vertex base2(glm::vec3(-0.5f, -0.5f, 0.5f));
            rhi::def::Vertex base3(glm::vec3(0.0f, -0.5f, -0.5f));
            std::vector<rhi::def::Vertex> vertices{apex, base1, base2, base3};
            // 4 faces triangulaires
            std::vector<uint32_t> indices{
                0, 1, 2, // Face 1
                0, 2, 3, // Face 2
                0, 3, 1, // Face 3
                1, 3, 2  // Base
            };
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
