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
                    std::unordered_map<std::string, def::Handle> __lookupTable;

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

                    def::Handle getHandle(const std::string &name) const {
                        if (this->exists(name) == false) {
                            logger::error << "Failed to find RHI texture with name: " << name << std::endl;
                            return def::NULL_HANDLE;
                        }
                        return this->__lookupTable.at(name);
                    }

                    const resource::Texture *getResource(def::Handle handle) const {
                        if (handle >= this->__data.size()) [[unlikely]] {
                            logger::error << "Failed to find RHI texture with handle: " << handle << std::endl;
                            return nullptr;
                        }
                        return this->__data[handle].get();
                    }

                    bool exists(const std::string &name) const {
                        return this->__lookupTable.find(name) != this->__lookupTable.end();
                    }

                    Status add(const std::string &name, const unsigned char* data, const glm::ivec2 &size, int nChannels) {
                        if (this->exists(name)) {
                            logger::error << "Failed to add texture ressource: \"" << name << "\" already exists" << std::endl;
                            return Status::E_ALREADY_EXISTS;
                        }
                        if (data == nullptr || size.x <= 0 || size.y <= 0 || nChannels <= 0) {
                            logger::error << "Failed to add texture resource: invalid image data for \"" << name << "\"" << std::endl;
                            return Status::N_OK;
                        }
                        def::Handle handle(this->__data.size());
                        this->__data.push_back(std::make_unique<resource::Texture>(data, size, nChannels, handle));
                        this->__lookupTable[name] = handle;
                        return Status::OK;
                    }
            };

            __Texture::__Texture(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Texture::~__Texture() = default;

            def::Handle __Texture::getHandle(const std::string &name) const { return this->__impl->getHandle(name); }
            const resource::Texture *__Texture::getResource(def::Handle handle) const { return this->__impl->getResource(handle); }
            Status __Texture::add(const std::string &name, const unsigned char* data, const glm::ivec2 &size, int nChannels) { return this->__impl->add(name, data, size, nChannels); }
        } // namespace __registry
    } // namespace __private
} // namespace rhi
