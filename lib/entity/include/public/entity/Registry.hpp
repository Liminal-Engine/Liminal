#ifndef __LIMINAL__LIB__ENTITY__REGISTRY_HPP__
#define __LIMINAL__LIB__ENTITY__REGISTRY_HPP__

#include "Status.hpp"
#include "AEntity.hpp"

#include <memory>
#include <vector>

namespace entity {
    class Registry {
        public:
            Registry(void);
            ~Registry();

            Status add(const std::string &name, AEntity &&entity);
            bool exists(const std::string &name) const;
            std::vector<const AEntity *> getAll(void) const; // FIXME: this must absolutly disapear later
        
        private:
            class __Impl;
            std::unique_ptr<__Impl> __impl;
    };
} // namespace entity


#endif // __LIMINAL__LIB__ENTITY__REGISTRY_HPP__