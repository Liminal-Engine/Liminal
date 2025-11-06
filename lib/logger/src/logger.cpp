/**
 * @file logger.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-24
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include "fs/OutFile.hpp"
#include "fs/Path.hpp"

#include "logger.hpp"
#include "_private/_template_instances.hpp"

#include <time/Date.hpp>

#include <fstream>
#include <type_traits>

namespace logger {

    #define MAX_BUFFER_SIZE 2048

    namespace _private {

        static Level _level = Level::DEBUG; // TODO init depending on config file

        enum class _Color {
            RESET,
            BLACK,
            RED,
            GREEN,
            YELLOW,
            BLUE,
            MAGENTA,
            CYAN,
            ORANGE,
            WHITE
        };

        std::string _levelToStr(const Level &level) {
            switch (level) {
                case Level::TRACE:      return "TRACE";
                case Level::DEBUG:      return "DEBUG";
                case Level::INFO:       return "INFO";
                case Level::WARNING:    return "WARNING";
                case Level::ERROR:      return "ERROR";
                case Level::FATAL:      return "FATAL";
                default:                return "UNKNOWN";
            }
        };

        std::string _getFormatedDate(void) {
            return time_::Date::now().asStr("%Y-%m-%dT%H:%M:%SZ.%{ms}");
            // auto now = std::chrono::system_clock::now();
            // std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
            // std::stringstream date;
            // date << std::put_time(std::gmtime(&now_time_t), "%Y-%m-%dT%H:%M:%SZ");
            // auto duration = now.time_since_epoch();
            // auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
            // date << "." << std::setw(3) << std::setfill('0') << millis;
            // return date.str();
            // return time_::Date{}.toFormat("%Y-%m-%dT%H:%M:%SZ");

            // return time_::Date::now().asStr("%Y-%m-%dT%H:%M:%SZ"); // FIXME : find a waya to keep milliseconds
        };

    } // namespace private

    class Logger::_LoggerImpl {

        private:

            std::ostringstream _buffer;
            std::ostream &_stream;
            const Level _level;
            const std::string _strLevel;
            const std::string _ansiColor;


            static bool _firstLog;
            static fs::OutFile _file;

            static std::string _colorToAnsi(const _private::_Color &color) {
                switch (color) {
                    case _private::_Color::RESET:   return "\033[0m";
                    case _private::_Color::BLACK:   return "\033[30m";
                    case _private::_Color::RED:     return "\033[31m";
                    case _private::_Color::GREEN:   return "\033[32m";
                    case _private::_Color::YELLOW:  return "\033[33m";
                    case _private::_Color::BLUE:    return "\033[34m";
                    case _private::_Color::MAGENTA: return "\033[35m";
                    case _private::_Color::CYAN:    return "\033[36m";
                    case _private::_Color::ORANGE:  return "\033[38;5;208m";
                    case _private::_Color::WHITE:   return "\033[37m";
                    default:                        return "UNKNOWN_COLOR";
                }
            };

            std::string _getFormatedLogLevel(void) const {
                std::stringstream level;
                level << std::setw(11) << std::left << " [" + this->_strLevel + "]" << "> ";

                return level.str();
            };

        public:
            _LoggerImpl(
                std::ostream &stream,
                const Level &level,
                const _private::_Color &color
            ) :
            _buffer(),
            _stream(stream),
            _level(level),
            _strLevel(_private::_levelToStr(this->_level)),
            _ansiColor(this->_colorToAnsi(color))
            {
                if ( !Logger::_LoggerImpl::_file.isOpen() ) Logger::_LoggerImpl::_file.open();
                this->_buffer << std::boolalpha;
            }

            ~_LoggerImpl() {
                if (Logger::_LoggerImpl::_file.isOpen()) Logger::_LoggerImpl::_file.close();
            }

            void log(void) {
                if (this->_level >= _private::_level) {
                    std::string prefix{_private::_getFormatedDate() + " " + this->_getFormatedLogLevel()};
                    std::string bufferStr{this->_buffer.str() + "\n"};

                    _LoggerImpl::_file.write(prefix + bufferStr);
                    this->_stream << this->_ansiColor << prefix << bufferStr <<
                    this->_colorToAnsi(_private::_Color::RESET) << std::flush;
                    _LoggerImpl::_firstLog = false;
                    this->_buffer.str(""); // reset buffer;
                }
            };

            template<typename T>
            void bufferize(const T &message) {
                std::ostringstream tmp{this->_buffer.str()};
                tmp << message;

                if (tmp.str().size() < MAX_BUFFER_SIZE) {
                    this->_buffer << message;
                } else //should never happen since temlated compile with max 2048
                    std::cerr << _private::_levelToStr(Level::WARNING) << _private::_getFormatedDate() << "[WARNING] > Logger buffer size exceeded, message may not be printed";
            }

            std::ostream &getOutput(void) const { return this->_stream; };
    };

    Logger::Logger(
        std::ostream &stream,
        const Level &level,
        const _private::_Color &color
    ) :
    _loggerImpl{std::make_unique<Logger::_LoggerImpl>(stream, level, color)}
    {}


    template<typename T>
    Logger &Logger::operator<<(const T &message) {
        this->_loggerImpl->bufferize(message);
        return *this;
    }

    template<size_t N>
    Logger &Logger::operator<<(const char (&message)[N]) {
        this->_loggerImpl->bufferize(std::string(message));
        return *this;
    }

    Logger &Logger::operator<<(std::ostream& (*manipulator)(std::ostream&)) {
        if (manipulator == static_cast<std::ostream& (*)(std::ostream&)>(std::endl))
            this->_loggerImpl->log();
        else
            this->_loggerImpl->bufferize(manipulator);
        return *this;
    }

    std::ostream &Logger::getOutput(void) const { return this->_loggerImpl->getOutput(); }

    Level setLevel(const Level & level) { 
        // TOOD : show this no matter the old log level so that this info is always dislpayed ?
        info << "Setting log level to " << _private::_levelToStr(level) << std::endl;
        return (_private::_level = level);
    }

    bool Logger::_LoggerImpl::_firstLog = true;
    /**
     * TODO : concerning the _file :
     *  -   handle with fs OutFile;
     *  -   use liminal_string_extra that overload String class to replace '' with '_'
     * -    handle file closing
    **/
        
    fs::OutFile Logger::_LoggerImpl::_file = fs::OutFile{fs::Path{_private::_getFormatedDate() + ".log"}};

    Logger trace(std::cout, Level::TRACE, _private::_Color::GREEN);
    Logger debug(std::cout, Level::DEBUG, _private::_Color::BLUE);
    Logger info(std::cout, Level::INFO, _private::_Color::WHITE);
    Logger warn(std::cerr, Level::WARNING, _private::_Color::YELLOW);
    Logger error(std::cerr, Level::ERROR, _private::_Color::ORANGE);
    Logger fatal(std::cerr, Level::FATAL, _private::_Color::RED);
    #undef MAX_BUFFER_SIZE

} // namespace logger
