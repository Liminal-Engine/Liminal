#ifndef _LIMINAL_LIB_LOGGER_HPP_
#define _LIMINAL_LIB_LOGGER_HPP_

#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <memory>

namespace logger {

    namespace _private {
        enum class _Color;
    }

    enum class Level {
        TRACE,
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    Level setLevel(const Level &level);

    class Logger {

        public:
            Logger(
                std::ostream &stream,
                const Level &level,
                const _private::_Color &color
            );
            ~Logger() = default;

            template<typename T>
            Logger &operator<<(const T &message);

            //MAX IS 2048
            template<size_t N>
            Logger &operator<<(const char (&message)[N]);

            Logger &operator<<(std::ostream& (*manipulator)(std::ostream&));

            // TODO : implement this ?
            // /usr/bin/ld: CMakeFiles/LiminalUnitTests.dir/src/logger/logger.test.cpp.o: in function `LoggerTest_ComplexFormatting_using_logger_trace_Test::TestBody()':
            // /home/matteo/Projects/Liminal/tests/src/logger/logger.test.cpp:186: undefined reference to `logger::Logger& logger::Logger::operator<< <std::_Setw>(std::_Setw const&)'

            // Getters:
            std::ostream &getOutput(void) const;

        private:
            class _LoggerImpl;
            std::unique_ptr<_LoggerImpl> _loggerImpl;
    };
    
    // Use those instances
    extern Logger trace;
    extern Logger debug;
    extern Logger info;
    extern Logger warn;
    extern Logger error;
    extern Logger fatal;

} // namespace logger
    

#endif // _LIMINAL_LIB_LOGGER_HPP_