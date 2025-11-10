/**
 * @file template_instanciator.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-23
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef _LIMINAL_LIB_LOGGER__PRIVATE__TEMPLATE_INSTANCES_HPP_
#define _LIMINAL_LIB_LOGGER__PRIVATE__TEMPLATE_INSTANCES_HPP_

#include "logger.hpp"

namespace logger {

    template Logger &Logger::operator<<(char const * const &);
    
    #define instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(type)\
        template Logger &Logger::operator<<(const type &message);

            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(char)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(unsigned char)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(int)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(unsigned int)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(unsigned long)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(float)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(double)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(bool)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(short)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(unsigned short)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(long)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(long long)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(std::string)
            instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types(std::nullptr_t)

    #undef instantiate_template_logger_lib_logger_class_left_shift_op_with_simple_types

} // namespace logger
   

#endif // _LIMINAL_LIB_LOGGER__PRIVATE__TEMPLATE_INSTANCES_HPP_
