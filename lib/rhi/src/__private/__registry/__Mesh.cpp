#include "__private/__registry/__Mesh.hpp"

#include <logger/logger.hpp>

#include <unordered_map>

namespace rhi {
    namespace __private {
        namespace __registry {
            class __Mesh::__Impl {
                private:
                    // std::unordered_map<std::string, std::unique_ptr<resource::Mesh>> __data;
                    std::vector<std::unique_ptr<resource::Mesh>> __data;
                    std::unordered_map<std::string, def::Handle> __lookupTable;

                public:
                    __Impl(void) :
                    __data{}
                    {}

                    ~__Impl() = default;

                    Status init(void) {
                        // logger::info << "Initializing mesh registry" << std::endl;
                        // // top
                        // resource::Vertex v1;
                        // v1.position = glm::vec3(0.0f, 0.5f, 0.0f);
                        // v1.uv = glm::vec2(0.0f);
                        // v1.normal = glm::vec3(0.0f);
                        // // bottom left
                        // resource::Vertex v2;
                        // v2.position = glm::vec3(0.5f, -0.5f, 0.0f);
                        // v2.uv = glm::vec2(0.0f);
                        // v2.normal = glm::vec3(0.0f);
                        // // bottom right
                        // resource::Vertex v3;
                        // v3.position = glm::vec3(-0.5f, -0.5f, 0.0f);
                        // v3.uv = glm::vec2(0.0f);
                        // v3.normal = glm::vec3(0.0f);

                        // std::vector<resource::Vertex> verices{v1, v2, v3};
                        // std::vector<uint32_t> indices = {0, 1, 2};

                        // this->__data.emplace("TRIANGLE_MESH", std::make_unique<resource::Mesh>(verices, indices));
                        return Status::OK;
                    }

                    Status destroy(void) {
                        this->__data.clear();
                        return Status::OK;
                    };

                    const def::Handle getHandle(const std::string &name) const {
                        if (this->exists(name) == false) {
                            logger::error << "Failed to find RHI mesh with name: " << name << std::endl;
                            return def::NULL_HANDLE;
                        }
                        return this->__lookupTable.at(name);
                    }

                    const resource::Mesh *getResource(def::Handle handle) const {
                        if (handle >= this->__data.size()) [[unlikely]] {
                            logger::error << "Failed to find RHI mesh with handle: " << handle << std::endl;
                            return nullptr;
                        }
                        return this->__data[handle].get();
                    }

                    bool exists(const std::string &name) const {
                        return this->__lookupTable.find(name) != this->__lookupTable.end();
                    }

                    Status add(const std::string &name, const std::vector<def::Vertex> &vertices, const std::vector<uint32_t> &indices) {
                        if (this->exists(name)) {
                            logger::error << "\"" << name << "\" already exists in RHI mesh registry" << std::endl;
                            return Status::E_ALREADY_EXISTS;
                        }
                        this->__data.push_back(std::make_unique<resource::Mesh>(vertices, indices));
                        this->__lookupTable[name] = static_cast<def::Handle>(this->__data.size()) - 1;
                        return Status::OK;
                    }

            };

            __Mesh::__Mesh(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Mesh::~__Mesh() = default;

            Status __Mesh::init(void) { return this->__impl->init(); }
            Status __Mesh::destroy(void) { return this->__impl->destroy(); }
            const def::Handle __Mesh::getHandle(const std::string &name) const { return this->__impl->getHandle(name); }
            const resource::Mesh *__Mesh::getResource(def::Handle handle) const { return this->__impl->getResource(handle); }
            bool __Mesh::exists(const std::string &name) const { return this->__impl->exists(name); }
            Status __Mesh::add(const std::string &name, const std::vector<def::Vertex> &vertices, const std::vector<uint32_t> &indices) { return this->__impl->add(name, vertices, indices); }
        } // namespace __registry
    } // namespace __private
} // namespace rhi
