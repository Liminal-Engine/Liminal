#include "resource/Mesh.hpp"

#include <glad/glad.h>

namespace rhi {
    namespace resource {
        class Mesh::__Impl {
            private:
                uint32_t __VAO;
                uint32_t __EBO;
                uint32_t __VBO;
                uint32_t __count;

            public:
                __Impl(const std::vector<def::Vertex> &vertices, const std::vector<uint32_t> &indices):
                __VAO(0),
                __EBO(0),
                __VBO(0),
                __count(0)
                {
                    // 1. Generate VAO
                    glGenVertexArrays(1, &this->__VAO);
                    glBindVertexArray(this->__VAO);
                    // 2. Generate EBO
                    glGenBuffers(1, &this->__EBO);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->__EBO);
                    // 3. Fill up EBO
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
                    // 4. Generate VBO
                    glGenBuffers(1, &this->__VBO);
                    glBindBuffer(GL_ARRAY_BUFFER, this->__VBO);
                    // 5. Fill up VBO
                    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(rhi::def::Vertex), vertices.data(), GL_STATIC_DRAW);
                    // 6. Configure VAO attributes
                    // 6.1 Position
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(rhi::def::Vertex), (void*)offsetof(rhi::def::Vertex, position));
                    glEnableVertexAttribArray(0);
                    // 6.2 Normal
                    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(rhi::def::Vertex), (void*)offsetof(rhi::def::Vertex, normal));
                    glEnableVertexAttribArray(1);
                    // 6.3 UV
                    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(rhi::def::Vertex), (void*)offsetof(rhi::def::Vertex, uv));
                    glEnableVertexAttribArray(2);
                    // 7. Unbind
                    glBindVertexArray(0);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                    this->__count = static_cast<uint32_t>(indices.size());
                }
                ~__Impl() {
                    if (this->__VAO) glDeleteVertexArrays(1, &this->__VAO);
                    if (this->__VBO) glDeleteBuffers(1, &this->__VBO);
                    if (this->__EBO) glDeleteBuffers(1, &this->__EBO);
                }

                void draw(void) const {
                    glBindVertexArray(this->__VAO);
                    glDrawElements(GL_TRIANGLES, this->__count, GL_UNSIGNED_INT, nullptr);
                }
        };

        Mesh::Mesh(const std::vector<def::Vertex> &vertices, const std::vector<uint32_t> &indices) : __impl(std::make_unique<__Impl>(vertices, indices)) {}
        Mesh::~Mesh() = default;
        Mesh::Mesh(Mesh&&) noexcept = default;
        Mesh& Mesh::operator=(Mesh&&) noexcept = default;

        void Mesh::draw(void) const { this->__impl->draw(); }
    } // namespace resource
} // namespace rhi
