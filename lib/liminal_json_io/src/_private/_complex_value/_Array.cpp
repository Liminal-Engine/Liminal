/**
 * @file _Array.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_complex_value/_Array.hpp"

namespace liminal_json_io {
    namespace _private {
        namespace _complex_value {

            _Array::_Array(const _private::_JsonValue &complexArrayAsJsonValue) :
            _internalArray{_createInternalArray(complexArrayAsJsonValue)}
            {

            }

            inline bool _Array::hasNestedComplexValues(void) const {
                for (const auto &value : this->_internalArray) {
                    if (value.hasComplexType()) {
                        return true;
                    }
                }
                return false;
            }

            inline std::vector<std::size_t> _Array::getNestedComplexValuesIndices(void) const {
                std::vector<std::size_t> res{};

                for (size_t i = 0; i < this->_internalArray.size(); i++) {
                    if (this->_internalArray[i].hasComplexType()) {
                        res.push_back(i);
                    }
                }
                return res;
            }

            // Private:
            std::vector<_private::_JsonValue> _Array::_createInternalArray(
                const _private::_JsonValue &complexArrayAsJsonValue
            ) {
                if (complexArrayAsJsonValue.getType() != _private::_JsonValueTypes::_ARRAY) {
                    throw std::runtime_error("Invalid type requested.");
                }
                std::vector<_private::_JsonValue> array{};
                _private::_parsing::_types::_AnyType_t tmpAnyValue = complexArrayAsJsonValue.getValue();
                _private::_parsing::_types::_Array_t *parsingArrayPtr = std::get_if<_private::_parsing::_types::_Array_t>(&tmpAnyValue);
                if (parsingArrayPtr == nullptr) {
                    throw std::runtime_error("Invalid type requested.");
                }
                for (const auto &value : (*parsingArrayPtr)) {
                    array.push_back(_private::_JsonValue(*(value.get())));
                }
                return array;
            }

        } // namespace _complex_value
    } // _private
} // namespace liminal_json_io
