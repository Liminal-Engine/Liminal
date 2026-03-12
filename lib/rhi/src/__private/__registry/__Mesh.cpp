#include "__private/__registry/__Mesh.hpp"

#include <logger/logger.hpp>

#include <unordered_map>

namespace rhi {
    namespace __private {
        namespace __registry {
            class __Mesh::__Impl {
                private:
                    std::unordered_map<std::string, std::unique_ptr<resource::Mesh>> __data;
                    bool __initialized;

                public:
                    __Impl(void) :
                    __data{},
                    __initialized(false)
                    {}

                    ~__Impl() = default;

                    Status init(void) {
                        // top
                        resource::Vertex v1;
                        v1.position = glm::vec3(0.0f, 0.5f, 0.0f);
                        v1.uv = glm::vec2(0.0f);
                        v1.normal = glm::vec3(0.0f);
                        // bottom left
                        resource::Vertex v2;
                        v2.position = glm::vec3(0.5f, -0.5f, 0.0f);
                        v2.uv = glm::vec2(0.0f);
                        v2.normal = glm::vec3(0.0f);
                        // bottom right
                        resource::Vertex v3;
                        v2.position = glm::vec3(-0.5f, -0.5f, 0.0f);
                        v2.uv = glm::vec2(0.0f);
                        v2.normal = glm::vec3(0.0f);

                        std::vector<resource::Vertex> verices{v1, v2, v3};
                        std::vector<uint32_t> indices = {0, 1, 2};

                        this->__data.emplace("TRIANGLE", std::make_unique<resource::Mesh>(verices, indices));
                        this->__initialized = true;
                        return Status::OK;
                    }

                    Status destroy(void) {
                        if (this->__initialized == false) {
                            logger::error << "Failed to destory mesh registry: not initliazed" << std::endl;
                            return Status::E_NOT_INIT;
                        }
                        this->__data.clear();
                        this->__initialized = false;
                        return Status::OK;
                    };
            };

            __Mesh::__Mesh(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Mesh::~__Mesh() = default;

            Status __Mesh::init(void) { return this->__impl->init(); }
            Status __Mesh::destroy(void) { return this->__impl->destroy(); }
        } // namespace __registry
    } // namespace __private
} // namespace rhi
