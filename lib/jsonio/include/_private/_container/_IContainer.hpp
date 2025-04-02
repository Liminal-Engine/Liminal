/**
 * @file _IContainer.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-12-31
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#ifndef _LIMINAL_LIB_JSONIO__PRIVATE__CONTAINER__ICONTAINER_HPP_
#define _LIMINAL_LIB_JSONIO__PRIVATE__CONTAINER__ICONTAINER_HPP_

#include "_private/_JsonValue.hpp"
#include "_private/_parsing/_types.hpp"

namespace jsonio {
    namespace types {
        using Key_t = _private::_parsing::_types::_Key_t; //Forward declaration
    }
    namespace _private {
        namespace _container {

            class _IContainer {
                public:
                    virtual bool hasNestedContainers(void) const = 0;
                    virtual ~_IContainer() = default ;
            };
        } // namespace _container
    } // _private
} // namespace jsonio



#endif // _LIMINAL_LIB_JSONIO__PRIVATE__CONTAINER__ICONTAINER_HPP_