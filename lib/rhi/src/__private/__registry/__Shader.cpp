#include "__private/__registry/__Shader.hpp"
#include "__private/__config.hpp"

#include <logger/logger.hpp>
#include <fs/Path.hpp>

#include <unordered_map>
#include <tuple>

namespace rhi {
    namespace __private {
        namespace __registry {
            class __Shader::__Impl {
                private:
                    struct __Key {
                        ShaderCategory category;
                        std::string name;

                        __Key(const ShaderCategory &category, const std::string &name) :
                        category(category),
                        name(name)
                        {}
                        bool operator==(const __Key& other) const { return this->category == other.category && this->name == other.name; }
                    };

                    struct __Hasher {
                        size_t operator()(const __Key &key) const {
                            size_t h1 = std::hash<int>{}(static_cast<int>(key.category));
                            size_t h2 = std::hash<std::string>{}(key.name);
                            return h1 ^ (h2 << 1);
                        }
                    };

                    static ShaderCategory __strToShaderCategory(const std::string &str) {
                        std::string upperStr = str;
                        for (char &c : upperStr) c = ::toupper(c);
                        if (upperStr == "CORE") return ShaderCategory::CORE;
                        if (upperStr == "DEBUG") return ShaderCategory::DEBUG;
                        if (upperStr == "POST_PROCESS") return ShaderCategory::POST_PROCESS;
                        return ShaderCategory::UNKNOWN;

                    }

                    static std::string __categoryToStr(const ShaderCategory &category) {
                        switch (category) {
                            case ShaderCategory::CORE: return "CORE";
                            case ShaderCategory::DEBUG: return "DEBUG";
                            case ShaderCategory::POST_PROCESS: return "POST_PROCESS";
                            case ShaderCategory::UNKNOWN: return "UNKNOWN";
                            default: return "UNKNOWN";
                        }
                        return "UNKNOWN";
                    }
                    
                    std::unordered_map<__Key, std::unique_ptr<resource::Shader>, __Hasher> __data;
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
                            logger::warn << "Shader ressource registry already initialized" << std::endl;
                            return Status::E_ALREADY_INIT;
                        }
                        logger::info << "Initializing shader registry" << std::endl;
                        // 1. Get all sub entries (e.g. children) of the shader dir
                        std::vector<fs::Path> children = __private::__config::DEFAULT_SHADER_PATH.getChildren();
                        // 2. Filter with only directories that are not include
                        std::vector<fs::Path> categoryDirs{};
                        for (const fs::Path &child : children) {
                            fs::Entry tmpEntry(child.getEntry());
                            if (
                                tmpEntry.getType() == fs::Entry::Type::DIRECTORY &&
                                tmpEntry.getName() != "include"
                            ) {
                                categoryDirs.push_back(child);
                            }
                        }
                        // Create categories, names and shaders
                        for (const fs::Path &categoryDir : categoryDirs) {
                            std::string categoryStr = categoryDir.getEntry().getName();
                            ShaderCategory category = __strToShaderCategory(categoryStr);
                            children = categoryDir.getChildren();
                            for (const fs::Path &child : children) {
                                fs::Entry tmpEntry(child.getEntry());
                                if (
                                    tmpEntry.getType() == fs::Entry::Type::REGULAR_FILE &&
                                    tmpEntry.getExtension() == "glsl"
                                ) {
                                    std::string name(tmpEntry.getName());
                                    logger::debug << "Creating shader ressource CATGORY=" << categoryStr << ",NAME=" << name << std::endl;
                                    this->__data.emplace(__Key(category, name), std::make_unique<resource::Shader>(child));
                                }
                            }
                        }
                        this->__initialized = true;
                        return Status::OK;
                    }

                    Status destroy(void) {
                        if (this->__initialized == false) {
                            logger::error << "Failed to destory shader registry: not initialized" << std::endl;
                            return Status::E_NOT_INIT;
                        }
                        this->__data.clear();
                        this->__initialized = false;
                        return Status::OK;
                    }

                    const resource::Shader *get(const ShaderCategory &category, const std::string &name) const {
                        __Key key(category, name);
                        auto it = this->__data.find(key);

                        if (it == this->__data.end()) {
                            logger::error << "Shader not found: CATEGORY=" << __categoryToStr(category) << ",NAME=" << name << std::endl;
                            return nullptr; // FIXME : return default shader instead
                        }
                        return it->second.get();
                    }
            };

            __Shader::__Shader(void) :
            __impl(std::make_unique<__Impl>())
            {

            }

            __Shader::~__Shader() = default;

            Status __Shader::init(void) { return this->__impl->init(); }
            Status __Shader::destroy(void) { return this->__impl->destroy(); }
            const resource::Shader *__Shader::get(const ShaderCategory &category, const std::string &name) const { return this->__impl->get(category, name); }
        } // namespace __registry
    } // namespace __private
} // namespace rhi


