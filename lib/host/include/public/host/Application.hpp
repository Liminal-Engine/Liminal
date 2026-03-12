#ifndef __LIMINAL__LIB__HOST__INCLUDE__APPLICATION_HPP__
#define __LIMINAL__LIB__HOST__INCLUDE__APPLICATION_HPP__

#include <memory>

namespace host {
    class Application {
        public:
            Application(void);
            ~Application();

        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace host


#endif // __LIMINAL__LIB__HOST__INCLUDE__APPLICATION_HPP__