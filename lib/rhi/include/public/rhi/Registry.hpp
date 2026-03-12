#ifndef __LIMINAL__LIB__RHI__REGISTRY_HPP__
#define __LIMINAL__LIB__RHI__REGISTRY_HPP__

#include <memory>
#include "Status.hpp"

namespace rhi {
    class Registry {
        public:
            Registry(void);
            ~Registry();

            Status init(void);

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace rhi


#endif // __LIMINAL__LIB__RHI__REGISTRY_HPP__