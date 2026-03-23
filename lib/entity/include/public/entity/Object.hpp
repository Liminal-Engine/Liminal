// #ifndef __LIMINAL__LIB__ENTITY__OBJECT_HPP__
// #define __LIMINAL__LIB__ENTITY__OBJECT_HPP__

// #include "AEntity.hpp"
// #include "component/Geometry.hpp"
// #include "component/Transform.hpp"
// #include "component/Material.hpp"

// #include <gfx/def/Handle.hpp>

// namespace entity {
//     class Object : public AEntity {
//         public:
//             Object(gfx::def::Handle meshHandle);
//             virtual ~Object();
//             Object(const Object &) = delete;
//             Object &operator=(const Object &) = delete;
//             Object(Object &&other) noexcept;
//             Object &operator=(Object &&other) noexcept;

//             component::Geometry geometry;
//             component::Transform transform;
//             component::Material material;
//     };
// } // namespace entity


// #endif // __LIMINAL__LIB__ENTITY__OBJECT_HPP__