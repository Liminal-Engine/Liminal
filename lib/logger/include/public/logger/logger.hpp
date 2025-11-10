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

            template<size_t N>
            Logger &operator<<(const char (&message)[N]) { return *this << std::string(message); }

            Logger &operator<<(std::ostream& (*manipulator)(std::ostream&));

            // Getters:
            std::ostream &getOutput(void) const;

            static void startWorker(void);
            static void stopWorker(void);
            static void flushOnCrash(int signal); // call automatically with signal

        private:
            class _LoggerImpl;
            std::unique_ptr<_LoggerImpl> _loggerImpl;
    };


    // Use those instances
    extern Logger &info;
    extern Logger &warn;
    extern Logger &error;
    extern Logger &fatal;
    extern Logger &trace;
    extern Logger &debug;
    


} // namespace logger
    

#endif // _LIMINAL_LIB_LOGGER_HPP_