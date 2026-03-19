#include "__private/__registry/__AssetRegistry.hpp"
#include "asset/Mesh.hpp"
#include "asset/Material.hpp"
#include "__private/__asset/__Shader.hpp"
#include "__private/__asset/__Texture.hpp"

#include <logger/logger.hpp>

#include <unordered_map>

namespace gfx {
    namespace __private {
        namespace __registry {

            template<typename T>
            class __AssetRegistry<T>::__Impl {
                private:
                    std::unordered_map<std::string, std::unique_ptr<T>> __data;

                public:
                    __Impl(void) :
                    __data{}
                    {

                    }

                    ~__Impl() {
                        this->__data.clear();
                    }

                    Status add(const std::string &name, T &&asset) {
                        if (this->exists(name)) {
                            logger::error << "Failed to add asset: \"" << name << "\" already exists" << std::endl;
                            return Status::E_ALREADY_EXISTS;
                        }
                        this->__data[name] = std::make_unique<T>(std::move(asset));
                        return Status::OK;
                    }

                    bool exists(const std::string &name) const { return this->__data.contains(name); }

                    bool exists(const fs::Path &path) const {
                        return this->get(path) != nullptr ? true : false;
                    }
                    
                    const T *get(const std::string &name) const {
                        if (this->exists(name) == false) {
                            logger::error << "Failed to get asset: name \"" << name << "\" does not exist" << std::endl;
                            return nullptr;
                        }
                        return this->__data.at(name).get();
                    }

                    const T *get(const fs::Path &path) const {
                        for (const auto &[name, asset] : this->__data) {
                            if (asset->getPath() == path) return asset.get();
                        }
                        return nullptr;
                    }
            };

            template<typename T>
            __AssetRegistry<T>::__AssetRegistry() : __impl(std::make_unique<__Impl>()) {}

            template<typename T>
            __AssetRegistry<T>::~__AssetRegistry() = default;

            template<typename T>
            Status __AssetRegistry<T>::add(const std::string &name, T &&asset) { return this->__impl->add(name, std::move(asset)); }

            template<typename T>
            bool __AssetRegistry<T>::exists(const std::string &name) const { return this->__impl->exists(name); }

            template<typename T>
            bool __AssetRegistry<T>::exists(const fs::Path &path) const { return this->__impl->exists(path); }

            template<typename T>
            const T *__AssetRegistry<T>::get(const std::string &name) const { return this->__impl->get(name); }

            template<typename T>
            const T *__AssetRegistry<T>::get(const fs::Path &path) const { return this->__impl->get(path); }
        } // namespace __registry
    } // namespace __private
} // namespace gfx

// template instanciation
template class gfx::__private::__registry::__AssetRegistry<gfx::asset::Mesh>;
template class gfx::__private::__registry::__AssetRegistry<gfx::asset::Material>;
template class gfx::__private::__registry::__AssetRegistry<gfx::__private::__asset::__Shader>;
template class gfx::__private::__registry::__AssetRegistry<gfx::__private::__asset::__Texture>;