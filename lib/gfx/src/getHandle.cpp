#include "gfx.hpp"

#include <rhi/Registry.hpp>
#include <logger/logger.hpp>

namespace gfx {
    def::Handle getHandle(const std::string &name) {
        rhi::def::Handle rhiHandle = rhi::Registry::getHandle(name);

        if (rhiHandle == rhi::def::NULL_HANDLE) {
            logger::error << "GFX failed to find RHI handle for name: " << name << std::endl;
            return def::NULL_HANDLE;
        }
        return static_cast<def::Handle>(rhiHandle);
    }
} // namespace gfx
