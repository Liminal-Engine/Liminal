/**
 * @file Base.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-04
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "error.hpp"

#include <logger/logger.hpp>

#include <sstream>
#include <vector>

namespace error {

    class Base::_BaseImpl {

        private:
            const std::string _msg;
            const std::string _debugInfo;

        public:

            _BaseImpl(const std::experimental::source_location &loc, const char *prettyFunction, const std::string &msg) :
            _msg{msg.empty() ? DEFAULT_ERR_MSG : msg},
            _debugInfo{__loadDebugInfo(loc, prettyFunction)}
            {
                logger::debug << this->_debugInfo << std::endl;
            }
            std::string __loadDebugInfo(const std::experimental::source_location &loc, const char *prettyFunction) {
                // TODO : load only this if debug mode (from env var ?)
                std::stringstream ss;
                ss << "An error was thrown in " << loc.file_name() << ":" << loc.line() << ":" << loc.column() <<
                " in function " << loc.function_name() << " : " << prettyFunction << " -> " << this->_msg;
                return ss.str();
            };

            void log(void) const {
                logger::error << this->_msg << std::endl;
            }

    };


    Base::Base(const std::experimental::source_location &loc, const char *prettyFunction, const char *format, ...) { // Cannot use initializer list here because of va args
        constexpr int initialBufferSize = DEFAULT_ERR_BUFF_SIZE; // Initial buffer size
        std::vector<char> buffer(initialBufferSize);

        va_list args;
        va_start(args, format);
        std::size_t length = vsnprintf(buffer.data(), buffer.size(), format, args);
        va_end(args);

        if (length >= buffer.size()) {
            // Resize the buffer and try again
            buffer.resize(length + 1); // +1 for null terminator
            va_list args;
            va_start(args, format);
            vsnprintf(buffer.data(), buffer.size(), format, args);
            va_end(args);
        }

        std::cout << std::string(buffer.data()) << std::endl;
        this->_impl = std::make_unique<_BaseImpl>(loc, prettyFunction, buffer.data()); // assign impl here
    }

    Base::~Base() = default;

    void Base::log(void) const { return this->_impl->log(); }
} // namespace error
