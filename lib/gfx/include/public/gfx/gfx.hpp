#ifndef __LIMINAL__GFX__LAOD_HPP__
#define __LIMINAL__GFX__LAOD_HPP__

#include "Status.hpp"
#include "def/ResourceType.hpp"
#include "def/Handle.hpp"

#include <fs/Path.hpp>

#include <string>

namespace gfx {
    Status load(def::ResourceType resourceType, const fs::Path &path);
    def::Handle getHandle(const std::string &name);
} // namespace gfx


#endif // __LIMINAL__GFX__LAOD_HPP__