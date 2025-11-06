/**
 * @file logger.test.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-06
 * 
 * @copyright Copyright (c) 2024
 * 
*/

#include <logger/logger.hpp>

#include "test/logger/Helper.hpp"

#include <sstream>
#include <regex>
#include <tuple>
#include <vector>
#include <utility>
#include <cstdarg>
#include <memory>
#include <algorithm>
#include <stdexcept>

#include <gtest/gtest.h>
#include <gmock/gmock.h>




#include <iostream>
#include <iomanip>
class LoggerTest : public ::testing::Test {
    protected:
        std::vector<logger::Level> _levels;
        std::vector<std::string> _loggerNames;

        LoggerTest(void):
        _levels{std::vector<logger::Level>{
            logger::Level::TRACE,
            logger::Level::DEBUG,
            logger::Level::INFO,
            logger::Level::WARNING,
            logger::Level::ERROR,
            logger::Level::FATAL,
        }},
        _loggerNames{std::vector<std::string>{
            "trace",
            "debug",
            "info",
            "warn",
            "error",
            "fatal"
        }}
        {}

    bool _shouldLog(const logger::Level &level, const std::string &loggerName) {
        return this->_getLoggerNamePos(loggerName) >= this->_getLevelPos(level);
    }

    private:
        std::size_t _getLoggerNamePos(const std::string &name) {
            auto it = std::find(this->_loggerNames.begin(), this->_loggerNames.end(), name);
            if (it != this->_loggerNames.end()) {
                return std::distance(this->_loggerNames.begin(), it);
            }
            throw std::runtime_error("Given name not found: " + name);
        }

        std::size_t _getLevelPos(const logger::Level &level) {
            auto it = std::find(this->_levels.begin(), this->_levels.end(), level);
            if (it != this->_levels.end()) {
                return std::distance(this->_levels.begin(), it);
            }
            throw std::runtime_error("Given level not found");
        }
};


#define _PERFORM_LOG(instance, actions) \
    std::stringstream buffer{}; \
    std::streambuf *sbuf = logger::instance.getOutput().rdbuf(); \
    logger::instance.getOutput().rdbuf(buffer.rdbuf()); \
    logger::instance actions;  \
    logger::instance.getOutput().rdbuf(sbuf); \

#define _CREATE_INSTANCE_TEST(name, logLevel, levelDisplay, instance, actions, expected) \
    TEST_F(LoggerTest, name ## _using_logger_ ## instance) { \
        logger::setLevel(logLevel); \
        _PERFORM_LOG(instance, actions); \
        EXPECT_TRUE( \
            _shouldLog(logLevel, #instance) ? \
            std::string{#expected} == "\"\"" ? \
            buffer.str() == "" : \
            std::regex_search(buffer.str(), ::test::logger::Helper::getMessageRegexp(levelDisplay, expected)) : \
            buffer.str().empty()); \
    };

#define CREATE_LOGGER_TEST(name, logLevel, actions, expected) \
    _CREATE_INSTANCE_TEST(name, logLevel, "TRACE", trace, actions, expected); \
    _CREATE_INSTANCE_TEST(name, logLevel, "DEBUG", debug, actions, expected); \
    _CREATE_INSTANCE_TEST(name, logLevel, "INFO", info, actions, expected); \
    _CREATE_INSTANCE_TEST(name, logLevel, "WARNING", warn, actions, expected); \
    _CREATE_INSTANCE_TEST(name, logLevel, "ERROR", error, actions, expected); \
    _CREATE_INSTANCE_TEST(name, logLevel, "FATAL", fatal, actions, expected);


CREATE_LOGGER_TEST(
    Empty,
    logger::Level::TRACE,
    << "Nothing should be logged since no end manipulator provided",
    ""
);

CREATE_LOGGER_TEST(
    Trace,
    logger::Level::TRACE,
    << "TRACE LOG" << std::endl,
    "TRACE LOG"
);

CREATE_LOGGER_TEST(
    Debug,
    logger::Level::DEBUG,
    << "DEBUG LOG" << std::endl,
    "DEBUG LOG"
);

CREATE_LOGGER_TEST(
    Info,
    logger::Level::DEBUG,
    << "INFO LOG" << std::endl,
    "INFO LOG"
);

CREATE_LOGGER_TEST(
    Warning,
    logger::Level::WARNING,
    << "WARNING LOG" << std::endl,
    "WARNING LOG"
);

CREATE_LOGGER_TEST(
    Error,
    logger::Level::ERROR,
    << "ERROR LOG" << std::endl,
    "ERROR LOG"
);

CREATE_LOGGER_TEST(
    Fatal,
    logger::Level::FATAL,
    << "FATAL LOG" << std::endl,
    "FATAL LOG"
);

CREATE_LOGGER_TEST(
    BasicMessage,
    logger::Level::INFO,
    << "Basic Message" << std::endl,
    "Basic Message"
);

CREATE_LOGGER_TEST(
    MediumMessage,
    logger::Level::DEBUG,
    << "Medium Message with Details: " << 42 << std::endl,
    "Medium Message with Details: 42"
);

CREATE_LOGGER_TEST(
    ComplicatedMessage,
    logger::Level::WARNING,
    << "Complicated Message" << '\n' << "Line 2"
    << '\n' << "Line 3" << std::endl,
    "Complicated Message\nLine 2\nLine 3"
);

CREATE_LOGGER_TEST(
    ComplexTypes,
    logger::Level::INFO,
    << "Complex Types: " << 42 << " " << 3.14 << " " << 'A' << " " << true << std::endl,
    "Complex Types: 42 3.14 A true"
);

CREATE_LOGGER_TEST(
    NestedDataStructures,
    logger::Level::DEBUG,
    << "Nested Data Structures: {" << "key1: " << 42 << ", key2: {" << "nested_key: " << "value" << "}}" << std::endl,
    "Nested Data Structures: \\{key1: 42, key2: \\{nested_key: value\\}\\}"
);

// FIXME
// CREATE_LOGGER_TEST(
//     MultiLine,
//     logger::Level::FATAL,
//     << "Multi-line message:" << "Line 1\nLine 2\nLine 3" << std::endl,
//     "Multi-line message: Line 1\nLine 2\nLine 3"
// );

CREATE_LOGGER_TEST(
    CharType,
    logger::Level::INFO,
    << 'A' << std::endl,
    "A"
);

CREATE_LOGGER_TEST(
    UnsignedCharType,
    logger::Level::INFO,
    << static_cast<unsigned char>('B') << std::endl,
    "B"
);

CREATE_LOGGER_TEST(
    IntType,
    logger::Level::DEBUG,
    << 42 << std::endl,
    "42"
);

CREATE_LOGGER_TEST(
    UnsignedIntType,
    logger::Level::WARNING,
    << static_cast<unsigned int>(100) << std::endl,
    "100"
);

CREATE_LOGGER_TEST(
    UnsignedLongType,
    logger::Level::ERROR,
    << static_cast<unsigned long>(1000) << std::endl,
    "1000"
);

CREATE_LOGGER_TEST(
    FloatType,
    logger::Level::FATAL,
    << 3.14f << std::endl,
    "3.14"
);

CREATE_LOGGER_TEST(
    DoubleType,
    logger::Level::INFO,
    << 3.141592653589793 << std::endl,
    "3.14159"
);

CREATE_LOGGER_TEST(
    BoolType,
    logger::Level::DEBUG,
    << true << std::endl,
    "true"
);

CREATE_LOGGER_TEST(
    ShortType,
    logger::Level::WARNING,
    << static_cast<short>(10) << std::endl,
    "10"
);

CREATE_LOGGER_TEST(
    UnsignedShortType,
    logger::Level::ERROR,
    << static_cast<unsigned short>(20) << std::endl,
    "20"
);

CREATE_LOGGER_TEST(
    LongType,
    logger::Level::FATAL,
    << static_cast<long>(10000) << std::endl,
    "10000"
);

CREATE_LOGGER_TEST(
    LongLongType,
    logger::Level::INFO,
    << static_cast<long long>(100000) << std::endl,
    "100000"
);

CREATE_LOGGER_TEST(
    StringType,
    logger::Level::DEBUG,
    << std::string("Hello") << std::endl,
    "Hello"
);

CREATE_LOGGER_TEST(
    NullptrType,
    logger::Level::WARNING,
    << nullptr << std::endl,
    "nullptr"
);
