#ifndef __LIMINAL__LIB__HOST__INCLUDE__PUBLIC__ENGINE_HPP__
#define __LIMINAL__LIB__HOST__INCLUDE__PUBLIC__ENGINE_HPP__

#include "Application.hpp"

#include <memory>

namespace host {
    class Engine {
        public:
            Engine(Application &application);
            ~Engine();

            int run(void);

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace host


#endif // __LIMINAL__LIB__HOST__INCLUDE__PUBLIC__ENGINE_HPP__  