#ifndef __LIMINAL__LIB__LEH__CONNECTOR_HPP__
#define __LIMINAL__LIB__LEH__CONNECTOR_HPP__

#include <functional>
#include <vector>
#include <memory>

namespace leh {
    
    // FIXME: use ipp or inl file
    template<typename... Args>
    class Connector {

        struct Slot {
            std::weak_ptr<void> owner;
            std::function<void(Args...)> callback;
        };

        public:

            template<typename T>
            void subscribe(const std::shared_ptr<T> &instance, const std::function<void(Args...)> &callback) {
                this->__subscribers.push_back({instance, callback});
            }

            void notify(Args... args) {
                for (auto it = this->__subscribers.begin(); it != this->__subscribers.end();) {
                    // we try to lock() the weak_ptr -> transform it in shared_ptr and give ownership
                    // since it's a shared_ptr, we need to keep it in a variable
                    if (auto pinned = it->owner.lock()) {
                        it->callback(args...); // call the function
                        ++it;
                    } else { // otherwise, delete it
                        it = this->__subscribers.erase(it); 
                    }
                }
            }

        private:
            std::vector<Slot> __subscribers;
    };
} // namespace leh


#endif // __LIMINAL__LIB__LEH__CONNECTOR_HPP__