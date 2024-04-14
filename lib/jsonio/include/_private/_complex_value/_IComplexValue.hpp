/**
 * @file _IComplexValue.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-31
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef LIMINAL_LIB_jsonio__PRIVATE__COMPLEX_VALUE__ICOMPLEXVALUE_HPP_
#define LIMINAL_LIB_jsonio__PRIVATE__COMPLEX_VALUE__ICOMPLEXVALUE_HPP_

#include "_private/_JsonValue.hpp"
#include "_private/_parsing/_types.hpp"

namespace jsonio {
    namespace types {
        using Key_t = _private::_parsing::_types::_Key_t; //Forward declaration
    }
    namespace _private {
        namespace _complex_value {

            class _IComplexValue {
                public:
                    virtual bool hasNestedComplexValues(void) const = 0;
                    virtual ~_IComplexValue() = default ;
            };
        } // namespace _complex_value
    } // _private
} // namespace jsonio



#endif // LIMINAL_LIB_jsonio__PRIVATE__COMPLEX_VALUE__ICOMPLEXVALUE_HPP_