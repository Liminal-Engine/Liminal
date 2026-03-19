#include "Mesh.hpp"

#include <rhi/def/Vertex.hpp>
#include <logger/logger.hpp>

#include <glad/glad.h>

#include <vector>
#include <cstdint>

namespace gfx {
    class Mesh::__Impl {
        private:
            // Engine part
            fs::Path __path;
            std::vector<rhi::def::Vertex> __vertices;
            std::vector<uint32_t> __indices;
            // OpenGL part
            uint32_t __VAO;
            uint32_t __EBO;
            uint32_t __VBO;
            uint32_t __count;

        public:
            __Impl(const fs::Path &path) {
                fs::Path absolutePath(path);
                absolutePath.toAbsolute();
                absolutePath.clean();
                logger::debug << "Loading mesh from: " << path.asStr() << std::endl;
                // 1. Generate vertices (hardcoded triangle for now)
                rhi::def::Vertex v1(glm::vec3(0.0f, 0.5f, 0.0f));
                rhi::def::Vertex v2(glm::vec3(0.5f, -0.5f, 0.0f));
                rhi::def::Vertex v3(glm::vec3(-0.5f, -0.5f, 0.0f));                
                this->__vertices = {v1, v2, v3};
                // 2. Generate indices
                this->__indices = {0, 1, 2};
                // 3. Generate path (will be used for hasing)
                this->__path = absolutePath;
                // 4. Generate VAO
                glGenVertexArrays(1, &this->__VAO);
                glBindVertexArray(this->__VAO);
                // 5. Generate EBO
                glGenBuffers(1, &this->__EBO);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->__EBO);
                // 6. Fill up EBO
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->__indices.size() * sizeof(uint32_t), this->__indices.data(), GL_STATIC_DRAW);
                // 7. Generate VBO
                glGenBuffers(1, &this->__VBO);
                glBindBuffer(GL_ARRAY_BUFFER, this->__VBO);
                // 8. Fill up VBO
                glBufferData(GL_ARRAY_BUFFER, this->__vertices.size() * sizeof(rhi::def::Vertex), this->__vertices.data(), GL_STATIC_DRAW);
                // 9. Configure VAO attributes
                // 9.1 Position
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(rhi::def::Vertex), (void*)offsetof(rhi::def::Vertex, position));
                glEnableVertexAttribArray(0);
                // 9.2 Normal
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(rhi::def::Vertex), (void*)offsetof(rhi::def::Vertex, normal));
                glEnableVertexAttribArray(1);
                // 9.3 UV
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(rhi::def::Vertex), (void*)offsetof(rhi::def::Vertex, uv));
                glEnableVertexAttribArray(2);
                // 10. Unbind
                glBindVertexArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            }

            ~__Impl() {
                if (this->__VAO) glDeleteVertexArrays(1, &this->__VAO);
                if (this->__VBO) glDeleteBuffers(1, &this->__VBO);
                if (this->__EBO) glDeleteBuffers(1, &this->__EBO);
            }
    };

    Mesh::Mesh(const fs::Path &path) : __impl(std::make_unique<__Impl>(path)) {}
    Mesh::~Mesh() = default;
}