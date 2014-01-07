#include <stdio.h>
#include <time.h>

#include "Logger.h"

using namespace Tiny2D;

const char *Logger::printFormat = "%s %s [%s] - %s\n";
const char *Logger::timeFormat = "%F %H:%M:%S";
const char *Logger::levelStr[] = {"ERROR", "WARN", "INFO", "DEBUG"};
LogLevel Logger::printLevel = INFO;
const char *Logger::logFile = nullptr;

void Logger::log(LogLevel level, const char *message) {
    static bool logfileErr = false;

    if(level <= printLevel) {
        time_t currentTime;
        time(&currentTime);
        char timeStr[21];
        strftime(timeStr, 20, Logger::timeFormat, localtime(&currentTime));

        printf(Logger::printFormat, timeStr, Logger::levelStr[level], name, message);
        if(logFile != nullptr) {
            FILE *file = fopen(logFile, "a");
            if(file != nullptr) {
                fprintf(file, Logger::printFormat, timeStr, Logger::levelStr[level], name, message);
                fclose(file);
            }else{
                if(!logfileErr) {
                    printf(Logger::printFormat, timeStr, Logger::levelStr[WARN], "Logger");
                    logfileErr = true;
                }
            }
        }
    }
}

void Logger::setLogFile(const char *file) {
    Logger::logFile = file;
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
