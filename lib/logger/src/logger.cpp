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



#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <csignal>
#include <atomic>

namespace logger {

#define BUFFER_SIZE_TO_FLUSH 65'536

    namespace _private {
#ifndef NDEBUG
    static Level _level = Level::TRACE; // TODO init depending on config file
#else
    static Level _level = Level::INFO; // TODO init depending on config file
#endif

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

        std::string _getFormatedDate(void) { return time_::Date::now().asStr("%Y-%m-%dT%H:%M:%S:%{ms}Z"); };

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
            static std::string _fileBuffer;

            static std::queue<std::string> _logMessages;
            static std::mutex _mutex;
            static std::condition_variable _condition;
            static std::atomic<bool> _running;
            static std::thread _worker;

            static void _workerFunc(void) {
                while (_LoggerImpl::_running) {
                    std::unique_lock<std::mutex> lock(_mutex);
                    _LoggerImpl::_condition.wait(lock, []{return !_logMessages.empty() || !_LoggerImpl::_running; });
                    while (!_logMessages.empty()) {
                        std::string message = std::move(_LoggerImpl::_logMessages.front());
                        _LoggerImpl::_logMessages.pop();
                        _LoggerImpl::_fileBuffer += message;
                        if (_LoggerImpl::_fileBuffer.size() >= BUFFER_SIZE_TO_FLUSH) _LoggerImpl::_flushFileBuffer();
                    }
                }
                // Flush remaining logs
                while (!_LoggerImpl::_logMessages.empty()) {
                    _LoggerImpl::_fileBuffer += _LoggerImpl::_logMessages.front();
                    _LoggerImpl::_logMessages.pop();
                }
                _LoggerImpl::_flushFileBuffer();
            }

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
                _LoggerImpl::_flushFileBuffer();
                if (Logger::_LoggerImpl::_file.isOpen()) Logger::_LoggerImpl::_file.close();
            }

            void log(void) {
                if (this->_level >= _private::_level) {
                    std::string prefix(_private::_getFormatedDate() + " " + this->_getFormatedLogLevel());
                    std::string bufferStr(this->_buffer.str() + "\n");

                    this->_stream << this->_ansiColor << prefix << bufferStr <<
                    this->_colorToAnsi(_private::_Color::RESET) << std::flush;
                    if (_LoggerImpl::_firstLog) {
                        _LoggerImpl::_firstLog = false;
                        if ( !_LoggerImpl::_file.getAbsolutePath().exists() ) _LoggerImpl::_file.getAbsolutePath().create(fs::Entry::Type::REGULAR_FILE, true);
                        if (_LoggerImpl::_file.open() != fs::Status::OK) error << "Failed to open log file: " << _LoggerImpl::_file.getAbsolutePath().asStr() << std::endl;
                    }
                    {
                        std::lock_guard<std::mutex> lock(_LoggerImpl::_mutex);
                        _LoggerImpl::_logMessages.push(prefix + bufferStr);
                    }
                    _LoggerImpl::_condition.notify_one();
                    this->_buffer.str("");
                    // this->_buffer.str(""); // reset buffer;

                    // _LoggerImpl::_fileBuffer += std::string(prefix + bufferStr);
                    // if (_LoggerImpl::_fileBuffer.size() >= BUFFER_SIZE_TO_FLUSH) _LoggerImpl::_flushFileBuffer();
                }
            };

            template<typename T>
            void bufferize(const T &message) {
                this->_buffer << message;
            }

            std::ostream &getOutput(void) const { return this->_stream; };

            static void _flushFileBuffer(void) {
                _LoggerImpl::_file.write(_LoggerImpl::_fileBuffer);
                _LoggerImpl::_fileBuffer = "";
            }

            static void startWorker(void) {
                _LoggerImpl::_running = true;
                _LoggerImpl::_worker = std::thread(_LoggerImpl::_workerFunc);
            }

            static void stopWorker(void) {
                _LoggerImpl::_running = false;
                _LoggerImpl::_condition.notify_all();
                if (_LoggerImpl::_worker.joinable()) _LoggerImpl::_worker.join();
            }

            static void flushOnCrash(int) {
                std::lock_guard<std::mutex> lock(_mutex);
                while (!_logMessages.empty()) {
                    _fileBuffer += _logMessages.front();
                    _logMessages.pop();
                }
                _LoggerImpl::_flushFileBuffer();
            }

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

    Logger &Logger::operator<<(std::ostream& (*manipulator)(std::ostream&)) {
        if (manipulator == static_cast<std::ostream& (*)(std::ostream&)>(std::endl))
            this->_loggerImpl->log();
        else
            this->_loggerImpl->bufferize(manipulator);
        return *this;
    }

    std::ostream &Logger::getOutput(void) const { return this->_loggerImpl->getOutput(); }

    void Logger::startWorker(void) { return _LoggerImpl::startWorker(); }
    void Logger::stopWorker(void) { return _LoggerImpl::stopWorker(); }
    void Logger::flushOnCrash(int signal) { return _LoggerImpl::flushOnCrash(signal); }

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
    std::string Logger::_LoggerImpl::_fileBuffer("");

    class DummyLogger : public Logger {
    public:
        DummyLogger() : Logger(std::cout, Level::TRACE, _private::_Color::RESET) {}

        template<typename T>
        DummyLogger &operator<<(const T&) { return *this; }

        DummyLogger &operator<<(std::ostream& (*)(std::ostream&)) { return *this; }

    };

    
#ifdef NDEBUG
static DummyLogger traceImpl;
static DummyLogger debugImpl;
#else
static Logger traceImpl(std::cout, Level::TRACE, _private::_Color::GREEN);
static Logger debugImpl(std::cout, Level::DEBUG, _private::_Color::BLUE);
#endif

static Logger infoImpl(std::cout, Level::INFO, _private::_Color::WHITE);
static Logger warnImpl(std::cerr, Level::WARNING, _private::_Color::YELLOW);
static Logger errorImpl(std::cerr, Level::ERROR, _private::_Color::ORANGE);
static Logger fatalImpl(std::cerr, Level::FATAL, _private::_Color::RED);

// références visibles publiquement
Logger& trace = traceImpl;
Logger& debug = debugImpl;
Logger& info = infoImpl;
Logger& warn = warnImpl;
Logger& error = errorImpl;
Logger& fatal = fatalImpl;





    #undef MAX_BUFFER_SIZE

} // namespace logger

std::queue<std::string> logger::Logger::_LoggerImpl::_logMessages;
std::mutex logger::Logger::_LoggerImpl::_mutex;
std::condition_variable logger::Logger::_LoggerImpl::_condition;
std::atomic<bool> logger::Logger::_LoggerImpl::_running{false};
std::thread logger::Logger::_LoggerImpl::_worker;
