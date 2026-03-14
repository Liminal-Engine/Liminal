#include "__private/__registry/__Texture.hpp"
#include "__private/__config.hpp"

#include <logger/logger.hpp>

#include <unordered_map>
#include <vector>

namespace rhi {
    namespace __private {
        namespace __registry {
            class __Texture::__Impl {
                private:
                    std::vector<std::unique_ptr<resource::Texture>> __data;
                    std::unordered_map<std::string, resource::Handle> __lookupTable;

                public:
                    __Impl(void) :
                    __data{},
                    __lookupTable{}
                    {

                    }

                    ~__Impl() {
                        this->__data.clear();
                        this->__lookupTable.clear();
                    }

                    Status init(void) {
                        // logger::info << "Initializing texture registry" << std::endl;
                        // std::vector<fs::Path> children = __private::__config::DEFAULT_TEXTURE_PATH.getChildren();
                        // for (const fs::Path &child : children) {
                        //     fs::Entry entry = child.getEntry();
                        //     if (
                        //         entry.getType() == fs::Entry::Type::REGULAR_FILE &&
                        //         (
                        //             entry.getExtension() == "png" ||
                        //             entry.getExtension() == "jpg" ||
                        //             entry.getExtension() == "jpeg"
                        //         )
                        //     ) {
                        //         // this->__data.emplace(entry.getName(), std::make_unique<resource::Texture>(child));
                        //     }
                        // }
                        return Status::OK;

                    }

                    Status destroy(void) {
                        this->__data.clear();
                        this->__lookupTable.clear();
                        return Status::OK;
                    }

                    const resource::Handle getHandle(const std::string &name) const {
                        if (this->exists(name) == false) {
                            logger::error << "Failed to find RHI texture with name: " << name << std::endl;
                            return resource::NULL_HANDLE;
                        }
                        return this->__lookupTable.at(name);
                    }

                    const resource::Texture *getResource(resource::Handle handle) const {
                        if (handle >= this->__data.size()) [[unlikely]] {
                            logger::error << "Failed to find RHI texture with handle: " << handle << std::endl;
                            return nullptr;
                        }
                        return this->__data[handle].get();
                    }

                    bool exists(const std::string &name) const {
                        return this->__lookupTable.find(name) != this->__lookupTable.end();
                    }

                    Status add(const std::string &name, const unsigned char* data, const glm::ivec2 &size, const int &nChannels) {
                        if (this->exists(name)) {
                            logger::error << "Failed to add texture ressource: \"" << name << "\" already exists" << std::endl;
                            return Status::E_ALREADY_EXISTS;
                        }
                        if (data == nullptr || size.x <= 0 || size.y <= 0 || nChannels <= 0) {
                            logger::error << "Failed to add texture resource: invalid image data for \"" << name << "\"" << std::endl;
                            return Status::N_OK;
                        }
                        this->__data.push_back(std::make_unique<resource::Texture>(data, size, nChannels));
                        this->__lookupTable[name] = static_cast<resource::Handle>(this->__data.size()) - 1;
                        return Status::OK;
                    }
            };

            __Texture::__Texture(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Texture::~__Texture() = default;

            Status __Texture::init(void) { return this->__impl->init(); }
            Status __Texture::destroy(void) { return this->__impl->destroy(); }
            const resource::Handle __Texture::getHandle(const std::string &name) const { return this->__impl->getHandle(name); }
            const resource::Texture *__Texture::getResource(resource::Handle handle) const { return this->__impl->getResource(handle); }
            Status __Texture::add(const std::string &name, const unsigned char* data, const glm::ivec2 &size, const int &nChannels) { return this->__impl->add(name, data, size, nChannels); }
        } // namespace __registry
    } // namespace __private
} // namespace rhi
