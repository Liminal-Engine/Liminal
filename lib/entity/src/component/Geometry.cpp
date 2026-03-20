#include "component/Geometry.hpp"

namespace entity {
    namespace component {
        class Geometry::__Impl {
            private:
                gfx::def::Handle __meshHandle;

            public:
                __Impl(gfx::def::Handle meshHandle) :
                __meshHandle(meshHandle)
                {}
                ~__Impl() = default;

                gfx::def::Handle getMeshHandle(void) const { return this->__meshHandle; }
        };

        Geometry::Geometry(gfx::def::Handle meshHandle) : __impl(std::make_unique<__Impl>(meshHandle)) {}
        Geometry::~Geometry() = default;
        Geometry::Geometry(Geometry &&other) noexcept = default;
        Geometry &Geometry::operator=(Geometry &&other) noexcept = default;

        gfx::def::Handle Geometry::getMeshHandle(void) const { return this->__impl->getMeshHandle(); }
    } // namespace component
} // namespace entity
