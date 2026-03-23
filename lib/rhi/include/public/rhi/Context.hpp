#ifndef __LIMINAL__LIB__RHI__CONTEXT_HPP__
#define __LIMINAL__LIB__RHI__CONTEXT_HPP__

#include "Status.hpp"

#include <glm/glm.hpp>

#include <memory>

namespace rhi {
    class Context {
        public:
            Context(void);
            ~Context();

            Status init(void) noexcept;
            bool isInit(void) const noexcept;

            Status setViewport(int left, int top, size_t width, size_t height) const noexcept;
            Status setClearColor(const glm::vec4 &color) const noexcept;
            Status enableDepthTesting(void) const noexcept;
            Status enableBlending(void) const noexcept;
            void clear(void) const noexcept;

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__CONTEXT_HPP__