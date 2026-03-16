#include "def/Uniform.hpp"

namespace rhi {
    namespace def {
        Uniform::Uniform(const std::string &name, GLint location, GLenum type) :
        name(name),
        location(location),
        type(type)
        {}
    } // namespace def
    
} // namespace rhi
