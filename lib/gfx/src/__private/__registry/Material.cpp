#include "__private/__registry/__Material.hpp"
#include "asset/Material.hpp"

#include <logger/logger.hpp>

#include <utility>
#include <unordered_map>

namespace gfx {
    namespace __private {
        namespace __registry {
            class __Material::__Impl {
                private:
                    std::unordered_map<std::string, std::unique_ptr<asset::Material>> __data;
                
                public:
                    __Impl(void) :
                    __data{}
                    {}

                    ~__Impl() {
                        this->__data.clear();
                    }

                    Status add(const std::string &name, asset::Material &&material) {
                        auto it = this->__data.find(name);
                        if (it != this->__data.end()) {
                            logger::error << "Failed to add material gfx asset: " << name << " already exists" << std::endl;
                            return Status::E_ALREADY_EXISTS;
                        }
                        this->__data[name] = std::make_unique<asset::Material>(std::move(material));
                        return Status::OK;
                    }
            };

            __Material::__Material(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Material::~__Material() = default;

            Status __Material::add(const std::string &name, asset::Material &&material) { return this->__impl->add(name, std::move(material)); }
        } // namespace __registry
    } // namespace __private
} // namespace gfx
