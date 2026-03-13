#ifndef __LIMINAL__LIB__HOST__INCLUDE__APPLICATION_HPP__
#define __LIMINAL__LIB__HOST__INCLUDE__APPLICATION_HPP__

#include "Status.hpp"

#include <gfx/Registry.hpp>
#include <entity/Registry.hpp>


#include <memory>

namespace host {
    class Application {
        public:
            Application(void);
            ~Application();

            Status init(gfx::Registry &assetRegistry, entity::Registry &entityRegistry) const;

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace host


#endif // __LIMINAL__LIB__HOST__INCLUDE__APPLICATION_HPP__