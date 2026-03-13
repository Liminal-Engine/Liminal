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
                    std::unordered_map<std::string, std::unique_ptr<resource::Shader>> __data;

                public:
                    __Impl(void) :
                    __data{}
                    {

                    }

                    ~__Impl() {
                        this->__data.clear();
                    }


                    Status init(void) {
                        // if (this->__initialized == true) {
                        //     logger::warn << "Shader ressource registry already initialized" << std::endl;
                        //     return Status::E_ALREADY_INIT;
                        // }
                        // logger::info << "Initializing shader registry" << std::endl;
                        // // 1. Get all sub entries (e.g. children) of the shader dir
                        // std::vector<fs::Path> children = __private::__config::DEFAULT_SHADER_PATH.getChildren();
                        // // 2. Filter with only directories that are not include
                        // std::vector<fs::Path> categoryDirs{};
                        // for (const fs::Path &child : children) {
                        //     fs::Entry tmpEntry(child.getEntry());
                        //     if (
                        //         tmpEntry.getType() == fs::Entry::Type::DIRECTORY &&
                        //         tmpEntry.getName() != "include"
                        //     ) {
                        //         categoryDirs.push_back(child);
                        //     }
                        // }
                        // // Create categories, names and shaders
                        // for (const fs::Path &categoryDir : categoryDirs) {
                        //     std::string categoryStr = categoryDir.getEntry().getName();
                        //     ShaderCategory category = __strToShaderCategory(categoryStr);
                        //     children = categoryDir.getChildren();
                        //     for (const fs::Path &child : children) {
                        //         fs::Entry tmpEntry(child.getEntry());
                        //         if (
                        //             tmpEntry.getType() == fs::Entry::Type::REGULAR_FILE &&
                        //             tmpEntry.getExtension() == "glsl"
                        //         ) {
                        //             std::string name(tmpEntry.getName());
                        //             logger::debug << "Creating shader ressource CATGORY=" << categoryStr << ",NAME=" << name << std::endl;
                        //             this->__data.emplace(__Key(category, name), std::make_unique<resource::Shader>(child));
                        //         }
                        //     }
                        // }
                        // this->__initialized = true;
                        // return Status::OK;
                    }

                    Status destroy(void) {
                        this->__data.clear();
                        return Status::OK;
                    }

                    bool exists(const std::string &name) const {
                        return this->__data.find(name) != this->__data.end();
                    }

                    const resource::Shader *get(const std::string &name) const {
                       if (this->exists(name) == false) {
                            logger::error << "Failed to find shader with name: " << name << std::endl;
                            return nullptr;
                        }
                        return this->__data.at(name).get();
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
                        this->__data[name] = std::make_unique<resource::Shader>(vertexSource, geometrySource, fragmentSource, computeSource);
                        return Status::OK;
                    }
            };

            __Shader::__Shader(void) :
            __impl(std::make_unique<__Impl>())
            {

            }

            __Shader::~__Shader() = default;

            Status __Shader::init(void) { return this->__impl->init(); }
            Status __Shader::destroy(void) { return this->__impl->destroy(); }
            const resource::Shader *__Shader::get(const std::string &name) const { return this->__impl->get(name); }
            bool __Shader::exists(const std::string &name) const { return this->exists(name); }
            Status __Shader::add(const std::string &name, const std::string &vertexSource, const std::string &geometrySource, const std::string &fragmentSource, const std::string &computeSource) { return this->__impl->add(name, vertexSource, geometrySource, fragmentSource, computeSource); }
        } // namespace __registry
    } // namespace __private
} // namespace rhi


