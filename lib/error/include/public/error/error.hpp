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

#ifndef _LIMINAL_LIB_ERROR_ERROR_HPP_
#define _LIMINAL_LIB_ERROR_ERROR_HPP_

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
    class type : public error::Base { \
        public: \
            type(const std::experimental::source_location &l, const char *p, const char *f, ...): \
            error::Base() { \
                va_list a; \
                va_start(a, f); \
                this->init(l, p, f, a); \
                va_end(a); \
            } \
    };

namespace error {

    class Base : std::exception {
        public:            

            Base(void);
            virtual ~Base();

            void init(const std::experimental::source_location &loc, const char *prettyFunction, const char *format, va_list args);

            // Re declaration
            virtual void log(void) const;

        private:
            class _BaseImpl;
            std::unique_ptr<_BaseImpl> _impl;
    };
    
} // namespace error


#endif // _LIMINAL_LIB_ERROR_ERROR_HPP_