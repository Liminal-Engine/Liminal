/**
 * @file types.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-31
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "types.hpp"

namespace liminal_json_io {
    namespace types {

        Object::Object(const _private::_JsonValue &objectAsJsonValue) :
        __internalObject{this->__createInternalObject(objectAsJsonValue)},
        __complexKeysComputed{false},
        __complexKeys{std::vector<Key_t>{}}
        {

        }

        inline bool Object::hasComplexValues(void) {
            if (this->__complexKeysComputed == false) {
                this->__computeComplexKeys();
            }
            return this->__complexKeys.size() > 0;
        }

        inline std::vector<Key_t> Object::getComplexKeys(void) {
            if (this->__complexKeysComputed == false) {
                this->__computeComplexKeys();
            }
            return this->__complexKeys;
        }

        // Private :
        void Object::__computeComplexKeys(void) {
            for (const auto &[key, value] : this->__internalObject) {
                if (value.hasComplexType()) {
                    this->__complexKeys.push_back(key);
                }
            }
            this->__complexKeysComputed = true;
        }

        std::unordered_map<Key_t, _private::_JsonValue> Object::__createInternalObject(
            const _private::_JsonValue &objectAsJsonValue
        ) {
            if (objectAsJsonValue.getType() != _private::_JsonValueTypes::_OBJECT) {
                throw std::runtime_error("Invalid type requested.");
            }
            std::unordered_map<Key_t, _private::_JsonValue> object{};
            _private::_parsing::_types::_AnyType_t tmpAnyValue = objectAsJsonValue.getValue();
            _private::_parsing::_types::_Object_t *parsingObjectPtr = std::get_if<_private::_parsing::_types::_Object_t>(&tmpAnyValue);
            if (parsingObjectPtr == nullptr) {
                throw std::runtime_error("Invalid type requested.");
            }
            for (const auto &[key, value] : (*parsingObjectPtr)) {
                object.insert({key, _private::_JsonValue(*(value.get()))});
            }
            return object;
        }

    } // namespace types
} // namespace liminal_json_io
