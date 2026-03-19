#include "def/Uniform.hpp"
#include <new>

namespace rhi {
    namespace def {
        Uniform::Uniform(const std::string &name, GLint location, GLenum type) :
        name(name),
        location(location),
        type(type)
        {}

        Uniform &Uniform::operator=(const Uniform &other) {
            if (this != &other) {
                this->~Uniform();
                new (this) Uniform(other); // new (ptr) T() allocate to a ALREADY ALLOCATED memory so no leak with this method
            }
            return *this;
        }
    } // namespace def
    
} // namespace rhi
