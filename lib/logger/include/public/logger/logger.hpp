#ifndef LIMINAL_LIB_LOGGER_HPP_
#define LIMINAL_LIB_LOGGER_HPP_

#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <memory>

namespace liminal {

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

        void setLevel(const Level &level);

        class Logger {
            private:
                class _LoggerImpl;
                std::unique_ptr<_LoggerImpl> _loggerImpl;
                
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
        };        
        
        // Use those instances
        extern Logger trace;
        extern Logger debug;
        extern Logger info;
        extern Logger warn;
        extern Logger error;
        extern Logger fatal;

    } // namespace logger
    

} // namespace liminal

#endif // LIMINAL_LIB_LOGGER_HPP_