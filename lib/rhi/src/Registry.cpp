#include "Registry.hpp"
#include "resource/ResourceType.hpp"
#include "resource/Mesh.hpp"

#include <logger/logger.hpp>

#include <unordered_map>
#include <vector>

namespace rhi {
    class Registry::__Impl {
        private:
            std::vector<resource::ResourceType> __data;
            std::unordered_map<std::string, def::Handle> __lookupTable;

        public:
            __Impl(void) :
            __data{},
            __lookupTable{}
            {}

            ~__Impl() {
                if (this->clear() != Status::OK) {
                    logger::error << "Failed to clear RHI reistry" << std::endl;
                }
            }

            bool exists(const std::string &name) const { return this->__lookupTable.contains(name); }
            
            def::Handle getHandle(const std::string &name) const {
                if (this->exists(name) == false) {
                    logger::error << "Failed to get handle: " << name << " does not exists" << std::endl;
                    return def::NULL_HANDLE;
                }
                return this->__lookupTable.at(name);
            }

            const resource::Mesh *getMesh(def::Handle handle) const {
                if (handle >= static_cast<def::Handle>(this->__data.size())) { // ça fonctionnera pas si plusieurs vector de resource, ou alors il faut combiner toutes les resources dans le même vector
                    logger::error << "Failed to find mesh with given handle: " << handle << std::endl;
                    return nullptr;
                }
                const resource::Mesh *mesh = std::get_if<resource::Mesh>(&this->__data.at(handle));
                if (!mesh) {
                    logger::error << "Resource at handle " << handle << " is not a Mesh" << std::endl;
                    return nullptr;
                }
                return mesh;
            }

            const resource::Shader *getShader(def::Handle handle) const {
                if (handle >= static_cast<def::Handle>(this->__data.size())) { // ça fonctionnera pas si plusieurs vector de resource, ou alors il faut combiner toutes les resources dans le même vector
                    logger::error << "Failed to find shader with given handle: " << handle << std::endl;
                    return nullptr;
                }
                const resource::Shader *shader = std::get_if<resource::Shader>(&this->__data.at(handle));
                if (!shader) {
                    logger::error << "Resource at handle " << handle << " is not a Shader" << std::endl;
                    return nullptr;
                }
                return shader;
            }

            Status loadMesh(
                const std::string &name, 
                const std::vector<def::Vertex> &vertices,
                const std::vector<uint32_t> &indices
            ) {
                logger::debug << "RHI adding mesh resource \"" << name << "\"" << std::endl;
                if (this->exists(name)) [[unlikely]] {
                    logger::error << "Failed to add mesh, resource already exists: \"" << name << "\"" << std::endl;
                    return Status::E_ALREADY_EXISTS;
                }
                this->__data.emplace_back(resource::Mesh(vertices, indices));
                def::Handle handle = static_cast<def::Handle>(this->__data.size() - 1);
                this->__lookupTable[name] = handle;
                return Status::OK;
            }

            Status loadShader(
                const std::string &name,
                const std::string &vertexSource,
                const std::string &geometrySource,
                const std::string &fragmentSource,
                const std::string &computeSource
            ) {
                logger::debug << "RHI adding shader resource \"" << name << "\"" << std::endl;
                if (this->exists(name)) [[unlikely]] {
                    logger::error << "Failed to add shader, resource already exists: \"" << name << "\"" << std::endl;
                    return Status::E_ALREADY_EXISTS;
                }
                this->__data.emplace_back(resource::Shader(vertexSource, geometrySource, fragmentSource, computeSource));
                def::Handle handle = static_cast<def::Handle>(this->__data.size() - 1);
                this->__lookupTable[name] = handle;
                return Status::OK;
            }

            Status clear(void) {
                this->__data.clear();
                this->__lookupTable.clear();
                return Status::OK;
            }

    };

    Registry::Registry(void) : __impl(std::make_unique<__Impl>()) {}
    Registry::~Registry() = default;
    Registry &Registry::__instance(void) {
        static Registry instance;
        return instance;
    }

    bool Registry::exists(const std::string &name) { return __instance().__impl->exists(name); }
    def::Handle Registry::getHandle(const std::string &name) { return __instance().__impl->getHandle(name); }
    const resource::Mesh *Registry::getMesh(def::Handle handle) { return __instance().__impl->getMesh(handle); }
    const resource::Shader *Registry::getShader(def::Handle handle) { return __instance().__impl->getShader(handle); }
    Status Registry::clear(void) { return __instance().__impl->clear(); }
    Status Registry::loadMesh(const std::string &name, const std::vector<def::Vertex> &vertices, const std::vector<uint32_t> &indices) { return __instance().__impl->loadMesh(name, vertices, indices); }
    Status Registry::loadShader(const std::string &name, const std::string &vertexSource, const std::string &geometrySource, const std::string &fragmentSource, const std::string &computeSource) { return __instance().__impl->loadShader(name, vertexSource, geometrySource, fragmentSource, computeSource); }
} // namespace rhi
