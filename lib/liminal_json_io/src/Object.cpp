/**
 * @file Object.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "types.hpp"
#include "is_in_variant_v.hpp"
#include "_private/_complex_value/_IComplexValue.hpp"
#include "_private/_JsonValue.hpp"

#include <unordered_map>
#include <vector>


namespace liminal_json_io {
    
    namespace types {

        class Object::_ObjectImpl : public _private::_complex_value::_IComplexValue {
            public:
                _ObjectImpl(const _private::_JsonValue &objectAsJsonValue) :
                _internalObject{_createInternalObject(objectAsJsonValue)}
                {}

                _ObjectImpl(const _ObjectImpl &other) :
                _internalObject{other._internalObject}
                {}

                _ObjectImpl &operator=(const _ObjectImpl &other) {
                    if (this != &other) {
                        this->_internalObject = other._internalObject;
                    }
                    return *this;
                }

                bool hasNestedComplexValues(void) const {
                    for (const auto &[key, value] : this->_internalObject) {
                        if (value.hasComplexType()) {
                            return true;
                        }
                    }
                    return false;
                }

                std::vector<types::Key_t> getNestedComplexValuesKeys(void) const {
                    std::vector<types::Key_t> res{};

                    for (const auto &[key, value] : this->_internalObject) {
                        if (value.hasComplexType()) {
                            res.push_back(key);
                        }
                    }
                    return res;
                }

                template<typename T>
                requires is_in_variant_v<T, types::SimpleTypes_t>
                std::optional<T> get(const types::Key_t &key) const {
                    std::optional<T> res{};

                    auto it = this->_internalObject.find(key);
                    if (it != this->_internalObject.end()) {
                        if (it->second.hasComplexType()) {
                            std::cerr << "Value is marked as a complex type : " << it->second.getTypeAsStr() << std::endl;
                            return std::optional<T>{};
                        }
                        _private::_parsing::_types::_Any_t tmpAnyValue = it->second.getValue();
                        T *valuePtr = std::get_if<T>(&tmpAnyValue);
                        if (valuePtr != nullptr) {
                            res.emplace(*valuePtr);
                        }
                    }
                    return res;
                }

            private:
                std::unordered_map<types::Key_t, _private::_JsonValue> _internalObject;
                
                static std::unordered_map<types::Key_t, _private::_JsonValue> _createInternalObject(
                    const _private::_JsonValue &objectAsJsonValue
                ) {
                    if (objectAsJsonValue.getType() != _private::_JsonValueTypes::_OBJECT) {
                        throw std::runtime_error("Invalid type requested.");
                    }
                    std::unordered_map<types::Key_t, _private::_JsonValue> object{};
                    _private::_parsing::_types::_Any_t tmpAnyValue = objectAsJsonValue.getValue();
                    _private::_parsing::_types::_Object_t *parsingObjectPtr = std::get_if<_private::_parsing::_types::_Object_t>(&tmpAnyValue);
                    if (parsingObjectPtr == nullptr) {
                        throw std::runtime_error("Invalid type requested.");
                    }
                    for (const auto &[key, value] : (*parsingObjectPtr)) {
                        object.insert({key, _private::_JsonValue(*(value.get()))});
                    }
                    return object;
                }
        };


        Object::Object(const _private::_JsonValue &objectAsJsonValue) :
        _objectImpl{std::make_unique<_ObjectImpl>(objectAsJsonValue)}
        {}

        Object::Object(const Object &other) :
        _objectImpl{std::make_unique<_ObjectImpl>(*other._objectImpl)}
        {}

        Object::~Object() = default;

        Object &Object::operator=(const Object &other) {
            if (this != &other) {
                this->_objectImpl = std::make_unique<_ObjectImpl>(*other._objectImpl);
            }
            return *this;
        }

        //Complex value methods re declaration
        bool Object::hasNestedComplexValues(void) const { return this->_objectImpl->hasNestedComplexValues(); }
        std::vector<types::Key_t> Object::getNestedComplexValuesKeys(void) const { return this->_objectImpl->getNestedComplexValuesKeys(); }

        // Own methods :
        template <typename T>
        requires is_in_variant_v<T, types::SimpleTypes_t>
        std::optional<T> Object::get(const types::Key_t &key) const {
            return this->_objectImpl->get<T>(key);
        }

        #define instantiate_template_function(type)\
            template std::optional<type> Object::get(const types::Key_t &) const;

        instantiate_template_function(String_t)
        instantiate_template_function(IntNum_t)
        instantiate_template_function(FloatNum_t)
        instantiate_template_function(Bool_t)
        instantiate_template_function(Null_t)

        #undef instantiate_template_function

    } // namespace types

} // namespace liminal_json_io
