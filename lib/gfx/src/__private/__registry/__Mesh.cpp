#include "__private/__registry/__Mesh.hpp"

#include <logger/logger.hpp>

#include <unordered_map>
#include <utility>

namespace gfx {
    namespace __private {
        namespace __registry {         
            class __Mesh::__Impl {
                private:
                    std::unordered_map<std::string, std::unique_ptr<asset::Mesh>> __data;

                public:
                    __Impl(void) :
                    __data{}
                    {}

                    ~__Impl() = default;

                    Status add(const std::string &name, asset::Mesh &&mesh) {
                        auto it = this->__data.find(name);
                        if (it != this->__data.end()) {
                            logger::error << "Failed to add mesh gfx asset: " << name << " already exists" << std::endl;
                            return Status::E_ALREADY_EXISTS;
                        }
                        this->__data[name] = std::make_unique<asset::Mesh>(std::move(mesh));
                        return Status::OK;
                    }

                    bool exists(const std::string &name) const {
                        return this->__data.find(name) != this->__data.end();
                    }

                    const gfx::asset::Mesh *getByPath(const fs::Path &path) {
                        for (auto &meshAsset : this->__data) {
                            if (meshAsset.second->getPath() == path) return meshAsset.second.get();
                        }
                        return nullptr;
                    }

                    const gfx::asset::Mesh *get(const std::string &name) const {
                        if (this->exists(name) == false) {
                            logger::error << "Mesh asset registry cannot find asset with name: " << name << std::endl;
                            return nullptr;
                        }
                        return this->__data.at(name).get();
                    }
            };

            __Mesh::__Mesh(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Mesh::~__Mesh() = default;

            bool __Mesh::exists(const std::string &name) const { return this->__impl->exists(name); }
            Status __Mesh::add(const std::string &name, asset::Mesh &&mesh) { return this->__impl->add(name, std::move(mesh)); }
            const gfx::asset::Mesh *__Mesh::getByPath(const fs::Path &path) { return this->__impl->getByPath(path); }
            const gfx::asset::Mesh *__Mesh::get(const std::string &name) const { return this->__impl->get(name); }

        } // namespace __registry
    } // namespace __private
} // namespace gfx
