#ifndef __LIMINAL__LIB__HOST__INCLUDE__APPLICATION_HPP__
#define __LIMINAL__LIB__HOST__INCLUDE__APPLICATION_HPP__

#include "Status.hpp"

#include <entity/Registry.hpp>


#include <memory>

namespace host {
    class Application {
        public:
            Application(void);
            ~Application();

            Status init(void) const;
            void update(float deltaTime);

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace host


#endif // __LIMINAL__LIB__HOST__INCLUDE__APPLICATION_HPP__