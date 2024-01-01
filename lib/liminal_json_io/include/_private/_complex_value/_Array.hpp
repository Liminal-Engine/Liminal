/**
 * @file _Array.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__COMPLEX_VALUE__ARRAY_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__COMPLEX_VALUE__ARRAY_HPP_

#include "_private/_complex_value/_IComplexValue.hpp"
#include "_private/_is_in_variant.hpp"
#include "_private/_types/_SimpleTypes.hpp"

#include <optional>
#include <iostream>

namespace liminal_json_io {
    namespace _private {
        namespace _complex_value {

            class _Array : public _IComplexValue {
                public:
                    _Array(const _private::_JsonValue &complexObjectAsJsonValue);
                    
                    inline bool hasNestedComplexValues(void) const;
                    inline std::vector<std::size_t> getNestedComplexValuesIndices(void) const;

                    template<typename T>
                    requires _private::_is_in_variant_v<T, types::SimpleTypes_t>
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
                
                private:
                    std::vector<_private::_JsonValue> _internalArray;
                    static std::vector<_private::_JsonValue> _createInternalArray(const _private::_JsonValue &complexObjectAsJsonValue);
            };

        } // namespace _complex_value
    } // _private
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__COMPLEX_VALUE__ARRAY_HPP_