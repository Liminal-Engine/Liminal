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
                    std::unordered_map<std::string, std::unique_ptr<resource::Texture>> __data;
                    bool __initialized;

                public:
                    __Impl(void) :
                    __data{},
                    __initialized(false)
                    {

                    }

                    ~__Impl() = default;

                    Status init(void) {
                        if (this->__initialized == true) {
                            logger::warn << "Texture registry already initialized" << std::endl;
                            return Status::E_ALREADY_INIT;
                        }
                        logger::info << "Initializing texture registry" << std::endl;
                        std::vector<fs::Path> children = __private::__config::DEFAULT_TEXTURE_PATH.getChildren();
                        for (const fs::Path &child : children) {
                            fs::Entry entry = child.getEntry();
                            if (
                                entry.getType() == fs::Entry::Type::REGULAR_FILE &&
                                (
                                    entry.getExtension() == "png" ||
                                    entry.getExtension() == "jpg" ||
                                    entry.getExtension() == "jpeg"
                                )
                            ) {
                                this->__data.emplace(entry.getName(), std::make_unique<resource::Texture>(child));
                            }
                        }
                        this->__initialized = true;
                        return Status::OK;

                    }
            };

            __Texture::__Texture(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Texture::~__Texture() = default;

            Status __Texture::init(void) { return this->__impl->init(); }
        } // namespace __registry
    } // namespace __private
} // namespace rhi
