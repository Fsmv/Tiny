#pragma once

namespace Tiny2D {

enum LogLevel {
    ERROR,
    WARN,
    INFO,
    DEBUG
};

class Logger {
public:
    Logger(const char *name) : name(name) {};
    ~Logger() {};
    
    /**
     * Log to stdout and the log file if set at the specified log level
     *
     * prints in the format: YYYY-MM-DD HH:MM:SS LEVEL [name] - Message 
     * @param level the level to log at
     * @param message the message to log
     */
    void log(LogLevel level, const char *message);
    /**
     * Equivalent to log(ERROR, message)
     * @param message the message to log
     */
    void error(const char *message);
    /**
     * Equivalent to log(WARN, message)
     * @param message the message to log
     */
    void warn(const char *message);
    /**
     * Equivalent to log(INFO, message)
     * @param message the message to log
     */
    void info(const char *message);
    /**
     * Equivalent to log(DEBUGa, message)
     * @param message the message to log
     */
    void debug(const char *message);
    
    /**
     * Sets the file to log to
     * 
     * if nullptr do not log to a file
     * @param file file to log to
     */
    static void setLogFile(const char *file);
    /**
     * Sets Maximum log level to output
     * ERROR < WARN < INFO < DEBUG
     *
     * @param level the cutoff level
     */
    static void setLogLevel(LogLevel level);
private:
    static const char *printFormat;
    static const char *timeFormat;
    static const char *levelStr[4];

    static LogLevel printLevel;
    static const char *logFile;

    const char *name;
};
}
