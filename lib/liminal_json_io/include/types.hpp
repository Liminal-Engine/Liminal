/**
 * @file types.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_

#include "_private/_parsing/_types.hpp"
#include "_private/_JsonValue.hpp"
#include "_private/_is_in_variant.hpp"

#include <optional>
#include <iostream>

namespace liminal_json_io {
    namespace types {



        using String_t      =   _private::_parsing::_types::_String_t;
        using IntNum_t      =   _private::_parsing::_types::_IntNum_t;
        using FloatNum_t    =   _private::_parsing::_types::_FloatNum_t;
        using Null_t        =   _private::_parsing::_types::_Null_t;
        using Bool_t        =   _private::_parsing::_types::_Bool_t;

        using Key_t         =   _private::_parsing::_types::_Key_t;

        using SimpleTypes_t =   std::variant<String_t, IntNum_t, FloatNum_t, Null_t, Bool_t>;


        class Object {
            public:
                Object(const _private::_JsonValue &objectAsJsonValue);

                template<typename T>
                requires _private::_is_in_variant_v<T, SimpleTypes_t>
                std::optional<T> get(const Key_t &key) const {
                    std::optional<T> res{};

                    auto it = this->__internalObject.find(key);
                    if (it != this->__internalObject.end()) {
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
    
                inline bool hasComplexValues(void);
                inline std::vector<Key_t> getComplexKeys(void);

            private:
                std::unordered_map<Key_t, _private::_JsonValue> __internalObject;
                bool __complexKeysComputed;
                std::vector<Key_t> __complexKeys;
                
                void __computeComplexKeys(void);
            
                static std::unordered_map<Key_t, _private::_JsonValue> __createInternalObject(
                    const _private::_JsonValue &objectAsJsonValue
                );
        };

        class Array {
            std::vector<_private::_JsonValue> _internalData;
        };

        using Object_t         =    class Object;
        // using Array_t           

        // using Object_t      =   std::unordered_map<Key_t, _private::_JsonValue>;
        using Array_t       =   std::vector<_private::_JsonValue>;

        using AnyType_t     =   std::variant<
                                    String_t,
                                    IntNum_t,
                                    FloatNum_t,
                                    Bool_t,
                                    Null_t,
                                    Array_t,
                                    Object_t
                                >;

    } // namespace types
} // namespace liminal_json_io


#endif // LIMINAL_LIB_LIMINAL_JSON_IO_TYPES_HPP_