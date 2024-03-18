/**
 * @file Array.cpp
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

        class Array::_ArrayImpl: public _private::_complex_value::_IComplexValue {
            public:
                _ArrayImpl(const _private::_JsonValue &arrayAsJsonValue) :
                _internalArray{_createInternalArray(arrayAsJsonValue)}
                {}

                _ArrayImpl(const _ArrayImpl &other) :
                _internalArray{other._internalArray}
                {}

                _ArrayImpl &operator=(const _ArrayImpl &other) {
                    if (this != &other) {
                        this->_internalArray = other._internalArray;
                    }
                    return *this;
                }

                bool hasNestedComplexValues(void) const {
                    for (const auto &value : this->_internalArray) {
                    if (value.hasComplexType()) {
                        return true;
                        }
                    }
                    return false;
                }

                std::vector<std::size_t> getNestedComplexValuesIndices(void) const {
                    std::vector<std::size_t> res{};

                    for (size_t i = 0; i < this->_internalArray.size(); i++) {
                        if (this->_internalArray[i].hasComplexType()) {
                            res.push_back(i);
                        }
                    }
                    return res;
                }

                template<typename T>
                requires is_in_variant_v<T, types::SimpleTypes_t>
                std::optional<T> get(const std::size_t &index) const {
                    std::optional<T> res{};

                    if (index >= this->_internalArray.size()) {
                        std::cerr << "Invalid index, not in array : " << index << std::endl;
                        return std::optional<T>{};
                    }
                    _private::_JsonValue tmpJsonValue{this->_internalArray[index]};
                    if (tmpJsonValue.hasComplexType()) {
                        std::cerr << "Value is marked as a complex type : " << tmpJsonValue.getTypeAsStr() << std::endl;
                        return std::optional<T>{};
                    }
                    _private::_parsing::_types::_Any_t tmpAnyValue = tmpJsonValue.getValue();
                    T *valuePtr = std::get_if<T>(&tmpAnyValue);
                    if (valuePtr != nullptr) {
                        res.emplace(*valuePtr);
                    }
                    return res;
                }

                std::size_t getLen(void) const { return this->_internalArray.size(); };

            private:
                std::vector<_private::_JsonValue> _internalArray;
                
                static std::vector<_private::_JsonValue> _createInternalArray(
                    const _private::_JsonValue &arrayAsJsonValue
                ) {
                    if (arrayAsJsonValue.getType() != _private::_JsonValueTypes::_ARRAY) {
                        throw std::runtime_error("Invalid type requested.");
                    }
                    std::vector<_private::_JsonValue> array{};
                    _private::_parsing::_types::_Any_t tmpAnyValue = arrayAsJsonValue.getValue();
                    _private::_parsing::_types::_Array_t *parsingArrayPtr = std::get_if<_private::_parsing::_types::_Array_t>(&tmpAnyValue);
                    if (parsingArrayPtr == nullptr) {
                        throw std::runtime_error("Invalid type requested.");
                    }
                    for (const auto &value : (*parsingArrayPtr)) {
                        array.push_back(_private::_JsonValue(*(value.get())));
                    }
                    return array;
                }
        };


        Array::Array(const _private::_JsonValue &arrayAsJsonValue) :
        _arrayImpl{std::make_unique<_ArrayImpl>(arrayAsJsonValue)}
        {}

        Array::Array(const Array &other) :
        _arrayImpl{std::make_unique<_ArrayImpl>(*other._arrayImpl)}
        {}

        Array::~Array() = default;

        Array &Array::operator=(const Array &other) {
            if (this != &other) {
                this->_arrayImpl = std::make_unique<_ArrayImpl>(*other._arrayImpl);
            }
            return *this;
        }

        //Complex value methods re declaration
        bool Array::hasNestedComplexValues(void) const { return this->_arrayImpl->hasNestedComplexValues(); }
        std::vector<std::size_t> Array::getNestedComplexValuesIndices(void) const { return this->_arrayImpl->getNestedComplexValuesIndices(); }

        // Own methods :
        template <typename T>
        requires is_in_variant_v<T, types::SimpleTypes_t>
        std::optional<T> Array::get(const std::size_t &index) const {
            return this->_arrayImpl->get<T>(index);
        }

        #define instantiate_template_function(type)\
            template std::optional<type> Array::get(const std::size_t &) const;

        instantiate_template_function(String_t)
        instantiate_template_function(IntNum_t)
        instantiate_template_function(FloatNum_t)
        instantiate_template_function(Bool_t)
        instantiate_template_function(Null_t)

        #undef instantiate_template_function

        std::size_t Array::getLen(void) const { return this->_arrayImpl->getLen(); };

    } // namespace types

} // namespace liminal_json_io
