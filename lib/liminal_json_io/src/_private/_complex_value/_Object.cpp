/**
 * @file _Object.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-01
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "_private/_complex_value/_Object.hpp"

namespace liminal_json_io {
    namespace _private {
        namespace _complex_value {

            _Object::_Object(const _private::_JsonValue &complexObjectAsJsonValue) :
            _internalObject{_createInternalObject(complexObjectAsJsonValue)}
            {
            }

            //Private :
            std::unordered_map<types::Key_t, _private::_JsonValue> _Object::_createInternalObject( //TODO : limit the object creation to simple typs values only
                const _private::_JsonValue &complexObjectAsJsonValue
            ) {
                if (complexObjectAsJsonValue.getType() != _private::_JsonValueTypes::_OBJECT) {
                    throw std::runtime_error("Invalid type requested.");
                }
                std::unordered_map<types::Key_t, _private::_JsonValue> object{};
                _private::_parsing::_types::_Any_t tmpAnyValue = complexObjectAsJsonValue.getValue();
                _private::_parsing::_types::_Object_t *parsingObjectPtr = std::get_if<_private::_parsing::_types::_Object_t>(&tmpAnyValue);
                if (parsingObjectPtr == nullptr) {
                    throw std::runtime_error("Invalid type requested.");
                }
                for (const auto &[key, value] : (*parsingObjectPtr)) {
                    object.insert({key, _private::_JsonValue(*(value.get()))});
                }
                return object;
            }

            bool _Object::hasNestedComplexValues(void) const {
                for (const auto &[key, value] : this->_internalObject) {
                    if (value.hasComplexType()) {
                        return true;
                    }
                }
                return false;
            }

            inline std::vector<types::Key_t> _Object::getNestedComplexValuesKeys(void) const {
                std::vector<types::Key_t> res{};

                for (const auto &[key, value] : this->_internalObject) {
                    if (value.hasComplexType()) {
                        res.push_back(key);
                    }
                }
                return res;
            }

        } // namespace _complex_value
    } // _private
} // liminal_json_io
