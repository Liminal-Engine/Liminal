#include "__private/__registry/__Shader.hpp"
#include "__private/__config.hpp"

#include <logger/logger.hpp>
#include <fs/Path.hpp>

#include <unordered_map>
#include <tuple>
#include <string>

namespace rhi {
    namespace __private {
        namespace __registry {
            class __Shader::__Impl {
                private:
                    std::vector<std::unique_ptr<resource::Shader>> __data;
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


                    bool exists(const std::string &name) const {
                        return this->__lookupTable.find(name) != this->__lookupTable.end();
                    }

                    const def::Handle getHandle(const std::string &name) const {
                       if (this->exists(name) == false) {
                            logger::error << "Failed to find RHI shader with name: " << name << std::endl;
                            return def::NULL_HANDLE;
                        }                        
                        return this->__lookupTable.at(name);
                    }

                    const resource::Shader *getResource(def::Handle handle) const {
                        if (handle >= this->__data.size()) [[unlikely]] {
                            logger::error << "Failed to find RHI shader with handle: " << handle << std::endl;
                            return nullptr;
                        }
                        return this->__data[handle].get();
                    }

                    Status add(
                        const std::string &name,
                        const std::string &vertexSource,
                        const std::string &geometrySource,
                        const std::string &fragmentSource,
                        const std::string &computeSource
                    ) {
                        if (this->exists(name)) {
                            logger::error << "RHI shader \"" << name << "\" already exists" << std::endl;
                            return Status::E_ALREADY_EXISTS;
                        }
                        this->__data.push_back(std::make_unique<resource::Shader>(vertexSource, geometrySource, fragmentSource, computeSource));
                        this->__lookupTable[name] = static_cast<def::Handle>(this->__data.size()) - 1;
                        return Status::OK;
                    }
            };

            __Shader::__Shader(void) :
            __impl(std::make_unique<__Impl>())
            {

            }

            __Shader::~__Shader() = default;

            const def::Handle __Shader::getHandle(const std::string &name) const { return this->__impl->getHandle(name); }
            const resource::Shader *__Shader::getResource(def::Handle handle) const { return this->__impl->getResource(handle); }
            bool __Shader::exists(const std::string &name) const { return this->__impl->exists(name); }
            Status __Shader::add(const std::string &name, const std::string &vertexSource, const std::string &geometrySource, const std::string &fragmentSource, const std::string &computeSource) { return this->__impl->add(name, vertexSource, geometrySource, fragmentSource, computeSource); }
        } // namespace __registry
    } // namespace __private
} // namespace rhi


