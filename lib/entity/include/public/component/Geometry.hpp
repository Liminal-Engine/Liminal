#ifndef __LIMINAL__ENTITY__COMPONENT__GEOMETRY_HPP__
#define __LIMINAL__ENTITY__COMPONENT__GEOMETRY_HPP__

#include <memory>

#include <gfx/def/Handle.hpp>

namespace entity {
    namespace component {
        class Geometry {
            public:
                Geometry(gfx::def::Handle meshHandle);
                ~Geometry();
        
                Geometry(const Geometry &) = delete;
                Geometry &operator=(const Geometry &) = delete;
                Geometry(Geometry &&other) noexcept;
                Geometry &operator=(Geometry &&other) noexcept;

                gfx::def::Handle getMeshHandle(void) const;

            private:
                class __Impl;
                std::unique_ptr<__Impl> __impl;
        };     
    } // namespace component
} // namespace entity


#endif // __LIMINAL__ENTITY__COMPONENT__GEOMETRY_HPP__