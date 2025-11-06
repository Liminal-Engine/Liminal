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

            _BaseImpl(const std::experimental::source_location &loc, const char* prettyFunction, const std::string &msg) :
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

    Base::Base(void) noexcept = default;

    Base::~Base() noexcept = default;

    void Base::init(
        const std::experimental::source_location &loc,
        const char *prettyFunction,
        const char *format,
        va_list args
    ) {
        std::vector<char> buffer(DEFAULT_ERR_BUFF_SIZE, 0);
        vsnprintf(buffer.data(), buffer.size(), format, args);
        this->_impl = std::make_unique<Base::_BaseImpl>(loc, prettyFunction,  std::string{buffer.data()});
    }


    void Base::log(void) const { return this->_impl->log(); }
} // namespace error
