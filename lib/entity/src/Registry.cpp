#include "Registry.hpp"

#include <logger/logger.hpp>

#include <unordered_map>

namespace entity {
    class Registry::__Impl {
        private:
            std::unordered_map<std::string, std::unique_ptr<AEntity>> __data;

        public:
            __Impl(void) :
            __data{}
            {}

            ~__Impl() {
                this->__data.clear();
            }

            bool exists(const std::string &name) const {
                return this->__data.find(name) != this->__data.end();
            }

            Status add(const std::string &name, AEntity &&entity) {
                if (this->exists(name)) {
                    logger::error << "Failed to add entity: \"" << name << "\" already exists" << std::endl;
                    return Status::E_ALREADY_EXISTS;
                }
                this->__data[name] = std::make_unique<AEntity>(std::move(entity)); // this will need to change, signature must take pointer directly in order to accept derived class
                return Status::OK;
            }

            std::vector<AEntity *> getAll(void) const {
                std::vector<AEntity *> entities;
                entities.reserve(this->__data.size());
                for (auto const & [name, entity] : this->__data) {
                    entities.push_back(entity.get());
                }
                return entities;
            }
    };

    Registry::Registry(void) :
    __impl(std::make_unique<__Impl>())
    {}

    Registry::~Registry() = default;

    bool Registry::exists(const std::string &name) const { return this->__impl->exists(name); }
    Status Registry::add(const std::string &name, AEntity &&entity) { return this->__impl->add(name, std::move(entity)); }
    std::vector<AEntity *> Registry::getAll(void) const { return this->__impl->getAll(); }
} // namespace entity
