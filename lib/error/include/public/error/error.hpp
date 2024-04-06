/**
 * @file error.hpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-04
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#ifndef LIMINAL_LIB_ERROR_ERROR_HPP_
#define LIMINAL_LIB_ERROR_ERROR_HPP_

#include <stdexcept>
#include <experimental/source_location>
#include <string>
#include <memory>
#include <cstdarg>


#include <stdio.h>

// Always use this macro to throw errors, never instanciate error classes without it !
#define DEFAULT_ERR_MSG "NO MESSAGE PROVIDED"
#define NO_MESSAGE DEFAULT_ERR_MSG
#define DEFAULT_ERR_BUFF_SIZE 2048

#define THROW(type, ...) \
    throw type(std::experimental::source_location::current(), __PRETTY_FUNCTION__, __VA_ARGS__);


#define DEFINE_ERROR_CLASS(type) \
        class type : public error::Base {\
        public:\
            type(const std::experimental::source_location &l, const char *p, const char *f, ...):\
            error::Base(l, p, f)\
            {}\
    };

namespace error {

    class Base : std::exception {
        public:

            // TODO, use va args here instead :
            Base(const std::experimental::source_location &loc, const char *prettyFunction, const char *format, ...);
            virtual ~Base();

            // Re declaration
            virtual void log(void) const;

        private:
            class _BaseImpl;
            std::unique_ptr<_BaseImpl> _impl;
    };
    
} // namespace error


#endif // LIMINAL_LIB_ERROR_ERROR_HPP_