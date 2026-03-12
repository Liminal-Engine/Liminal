/**
 * @file main.cpp
 * @author DE VITA Matteo (matteo.devita7@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-01-02
 * 
 * @copyright Copyright (c) 2023
 * 
*/

#include "logger/logger.hpp"
#include <csignal>

#include <host/Engine.hpp>
#include <host/Application.hpp>

void setupLoggerSignalHandlers() {
    std::signal(SIGSEGV, logger::Logger::flushOnCrash);
    std::signal(SIGABRT, logger::Logger::flushOnCrash);
    std::signal(SIGINT,  logger::Logger::flushOnCrash);
    std::signal(SIGTERM, logger::Logger::flushOnCrash);
}

int main() {
    setupLoggerSignalHandlers();
    logger::Logger::startWorker();

    host::Application applicaton;


    int res = host::Engine(applicaton).run();
    logger::Logger::stopWorker();
    return res;
}
