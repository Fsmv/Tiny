#include <time.h>

#include "utils/Logger.h"

using namespace Tiny2D;

const char *Logger::printFormat = "%s %s [%s] - %s\n";
const char *Logger::timeFormat = "%F %H:%M:%S";
const char *Logger::levelStr[] = {"ERROR", "WARN", "INFO", "DEBUG"};
LogLevel Logger::printLevel = INFO;
FILE *Logger::logFile = nullptr;

void Logger::log(LogLevel level, const char *message) {
    if(level <= printLevel) {
        time_t currentTime;
        time(&currentTime);
        char timeStr[21];
        strftime(timeStr, 20, Logger::timeFormat, localtime(&currentTime));

        printf(Logger::printFormat, timeStr, Logger::levelStr[level], name, message);
        if(Logger::logFile != nullptr) {
            fprintf(Logger::logFile, Logger::printFormat, timeStr, Logger::levelStr[level], name, message);
        }
    }
}

void Logger::setLogFile(const char *file) {
    if(Logger::logFile != nullptr) {
        fclose(Logger::logFile);
    }
    
    //Just keep it open until the process dies or we switch to new file since it's static
    Logger::logFile = fopen(file, "a");
    
    if(Logger::logFile == nullptr) {
        Logger logger("Logger");
        logger.warn("Could not open log file");
    }
}

void Logger::setLogLevel(LogLevel level) {
    Logger::printLevel = level;
}

void Logger::error(const char *message) {
    log(ERROR, message);
}

void Logger::warn(const char *message) {
    log(WARN, message);
}

void Logger::info(const char *message) {
    log(INFO, message);
}

void Logger::debug(const char *message) {
    log(DEBUG, message);
}
