#include "__private/__asset/__Shader.hpp"

#include <rhi/resource/Shader.hpp>

#include <unordered_map>
#include <string>

namespace gfx {
    namespace __private {
        namespace __asset {
            class __Shader::__Impl {
                private:
                    rhi::resource::Shader *__resource;
                    std::unordered_map<std::string, int> __uniformLocations;

                public:
                    __Impl(void) :
                    __resource(nullptr),
                    __uniformLocations()
                    {

                    }
            };


            __Shader::__Shader(void) :
            __impl(std::make_unique<__Impl>())
            {}

            __Shader::~__Shader() = default;

            
        } // namespace __aset
    } // namespace __private
} // namespace gfx
