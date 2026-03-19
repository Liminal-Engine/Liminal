#include "resource/Mesh.hpp"

#include <logger/logger.hpp>

#include <glad/glad.h>

namespace rhi {
    namespace resource {
    
        class Mesh::__Impl {
            private:
                const def::Handle __rhiHandle;
                uint32_t __VAO;
                uint32_t __EBO;
                uint32_t __VBO;
                uint32_t __count;
    
            public:
                __Impl(
                    const std::vector<def::Vertex> &vertices,
                    const std::vector<uint32_t> &indices,
                    def::Handle handle
                ) :
                __rhiHandle(handle),
                __VAO(0),
                __EBO(0),
                __VBO(0),
                __count(static_cast<uint32_t>(indices.size()))
                {
                    // 1. Generate VAO
                    glGenVertexArrays(1, &this->__VAO);
                    glBindVertexArray(this->__VAO);
                    // 2. Generate EBO
                    glGenBuffers(1, &this->__EBO);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->__EBO);
                    // 2.1 Fill EBO
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
                    // Generate VBO
                    glGenBuffers(1, &this->__VBO);
                    glBindBuffer(GL_ARRAY_BUFFER, this->__VBO);
                    // 2.2 Fill up VBO
                    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(def::Vertex), vertices.data(), GL_STATIC_DRAW);
                    // 3. Configure VAO attributes
                    // 3.1 position
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(def::Vertex), (void*)offsetof(def::Vertex, position));
                    glEnableVertexAttribArray(0);
                    // 3.2 UV
                    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(def::Vertex), (void*)offsetof(def::Vertex, uv));
                    glEnableVertexAttribArray(1);
                    // 3.3 normal
                    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(def::Vertex), (void*)offsetof(def::Vertex, normal));
                    glEnableVertexAttribArray(2);
                    // 4. Unbind
                    glBindVertexArray(0);
                    glBindBuffer(GL_ARRAY_BUFFER, 0);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                }

                ~__Impl() {
                    if (this->__VAO) glDeleteVertexArrays(1, &this->__VAO);
                    if (this->__VBO) glDeleteBuffers(1, &this->__VBO);
                    if (this->__EBO) glDeleteBuffers(1, &this->__EBO);
                };

                void draw_DELETE_ME_I_AM_NOT_SUPPOSED_TO_DRAW_MYSELF(void) const {
                    glBindVertexArray(this->__VAO);
                    glDrawElements(GL_TRIANGLES, this->__count, GL_UNSIGNED_INT, nullptr);
                }

                def::Handle getRHIHandle(void) const { return this->__rhiHandle; }
        };
    
        
    
        Mesh::Mesh(
            const std::vector<def::Vertex> &vertices,
            const std::vector<uint32_t> &indices,
            def::Handle handle
        ) :
        __impl(std::make_unique<__Impl>(vertices, indices, handle))
        {
    
        }
    
        Mesh::~Mesh() = default;

        void Mesh::draw_DELETE_ME_I_AM_NOT_SUPPOSED_TO_DRAW_MYSELF(void) const { this->__impl->draw_DELETE_ME_I_AM_NOT_SUPPOSED_TO_DRAW_MYSELF();}

        def::Handle Mesh::getRHIHandle(void) const { return this->__impl->getRHIHandle(); }
    } // namespace resource
} // namespace rhi
