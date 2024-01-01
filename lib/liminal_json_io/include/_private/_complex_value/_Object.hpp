/**
 * @file _Object.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-31
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__COMPLEX_VALUE__OBJECT_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__COMPLEX_VALUE__OBJECT_HPP_

#include "_private/_complex_value/_IComplexValue.hpp"
#include "_private/_is_in_variant.hpp"
#include "types/SimpleTypes.hpp"

#include <optional>
#include <iostream>

namespace liminal_json_io {
    namespace _private {
        namespace _complex_value {

            class _Object : public _IComplexValue {
                public:
                    _Object(const _private::_JsonValue &complexObjectAsJsonValue);

                    template<typename T>
                    requires _private::_is_in_variant_v<T, types::SimpleTypes_t>
                    std::optional<T> get(const types::Key_t &key) const {
                        std::optional<T> res{};

                        auto it = this->_internalObject.find(key);
                        if (it != this->_internalObject.end()) {
                            if (it->second.hasComplexType()) {
                                std::cerr << "Value is marked as a complex type : " << it->second.getTypeAsStr() << std::endl;
                                return std::optional<T>{};
                            }
                            _private::_parsing::_types::_AnyType_t tmpAnyValue = it->second.getValue();
                            T *valuePtr = std::get_if<T>(&tmpAnyValue);
                            if (valuePtr != nullptr) {
                                res.emplace(*valuePtr);
                            }
                        }
                        return res;
                    }

                    bool hasNestedComplexValues(void) const;
                    inline std::vector<types::Key_t> getNestedComplexValuesKeys(void) const;

                private:
                    std::unordered_map<types::Key_t, _private::_JsonValue> _internalObject;
                    static std::unordered_map<types::Key_t, _private::_JsonValue> _createInternalObject(
                        const _private::_JsonValue &complexObjectAsJsonValue
                    );
            };

        } // namespace _complex_value
    } // _private
} // liminal_json_io

#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__COMPLEX_VALUE__OBJECT_HPP_