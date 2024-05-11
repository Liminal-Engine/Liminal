/**
 * @file User.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-27
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "User.hpp"

#include <limits>
#include <pwd.h>

namespace fs {


    class User::_Pimpl {
        private:
            using _c_user_t = struct passwd;

            std::string _name = "";
            unsigned int _id = std::numeric_limits<unsigned int>::max();
            unsigned int _groupId = std::numeric_limits<unsigned int>::max();
            bool _exists = false;

            void __initFromCUserT(const _c_user_t *c_user) {
                if (!c_user) this->_exists = false;
                else {
                    this->_name = std::string(c_user->pw_name);
                    this->_id = c_user->pw_uid;
                    this->_groupId = c_user->pw_gid;
                    this->_exists = true;
                }
            }

        public:
            _Pimpl(void)
            {}

            _Pimpl(const std::string &name)
            {
                __initFromCUserT(getpwnam(name.c_str()));
            }

            _Pimpl(const unsigned int &id)
            {
                __initFromCUserT(getpwuid(id));
            }

            bool operator==(const _Pimpl &other) {
                return (
                    this->_name == other._name &&
                    this->_id == other._id &&
                    this->_groupId == other._groupId &&
                    this->_exists == other._exists
                );
            }

            std::string getName(void) const noexcept { return this->_name; };
            unsigned int getId(void) const noexcept { return _id; };
            unsigned int getGroupId(void) const noexcept { return this->_groupId; };
            bool doesExist(void) const noexcept { return this->_exists; };

    };

    User::User(void):
    _impl(std::make_unique<User::_Pimpl>())
    {}

    
    User::User(const std::string &name):
    _impl(std::make_unique<User::_Pimpl>(name))
    {}

    User::User(const unsigned int &uid):
    _impl(std::make_unique<User::_Pimpl>(uid))
    {}

    User::User(const User &other):
    _impl(std::make_unique<User::_Pimpl>(other._impl->getId()))
    {}

    User::~User() = default;

    bool User::operator==(const User &other) const noexcept { return this->_impl->operator==(*other._impl); }

    std::string User::getName(void) const noexcept { return this->_impl->getName(); };
    unsigned int User::getId(void) const noexcept { return this->_impl->getId(); };
    unsigned int User::getGroupId(void) const noexcept { return this->_impl->getGroupId(); };
    bool User::doesExist(void) const noexcept { return this->_impl->doesExist(); };

} // namespace time_
