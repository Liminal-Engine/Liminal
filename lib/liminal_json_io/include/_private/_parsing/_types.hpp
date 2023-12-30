/**
 * @file _types.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-30
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__PARSING__TYPES_HPP_
#define LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__PARSING__TYPES_HPP_

#include <unordered_map>
#include <memory>
#include <string>
#include <cstddef>
#include <vector>
#include <variant>
#include <cstdint>

namespace liminal_json_io {
    namespace _private {
        
        class _JsonValue; // Forward declaration
    
        namespace _parsing {
            namespace _types {


                using _String_t     =   std::string;
                using _IntNum_t     =   intmax_t;
                using _FloatNum_t   =   long double;
                using _Null_t       =   std::nullptr_t;
                using _Bool_t       =   bool;

                using _Key_t        =   _String_t;
                
                using _Array_t      =   std::vector<std::shared_ptr<class _JsonValue>>;
                using _Object_t     =   std::unordered_map<_Key_t, std::shared_ptr<class _JsonValue>>;

                using _AnyType_t    =   std::variant<
                                            _String_t,
                                            _IntNum_t,
                                            _FloatNum_t,
                                            _Bool_t,
                                            _Null_t,
                                            _Array_t,
                                            _Object_t,
                                            std::shared_ptr<class _JsonValue>
                                        >;


            } // namespace _types 
        } // namespace _parsing
    } // namespace _private
} // namespace liminal_json_io



#endif // LIMINAL_LIB_LIMINAL_JSON_IO__PRIVATE__PARSING__TYPES_HPP_