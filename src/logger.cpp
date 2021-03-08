#include <logger.h>
#include <iostream>
#include <string>


namespace core {


// TODO: Add time/date stamps to logs
void Logger::Log(LOG_LEVEL level, const std::string& message, LOG_TYPE type, PASS_INFO success) {
    switch (level) {
        case INFO  : Logger::LogInfo(message, type, success);
        case WARN  : Logger::LogWarn(message, type, success);
        case ERR   : Logger::LogError(message, type, success);
    }
}
void Logger::LogInfo(const std::string& message, LOG_TYPE logType, PASS_INFO passInfo) {
    std::cout << PreText(logType) << "INFO: " << message << AfterText(passInfo) << std::endl;
}
void Logger::LogWarn(const std::string& message, LOG_TYPE logType, PASS_INFO passInfo) {
    std::cout << PreText(logType) << "WARN: " << message << AfterText(passInfo) << std::endl;
}
void Logger::LogError(const std::string& message, LOG_TYPE logType, PASS_INFO passInfo) {
    std::cout << PreText(logType) << "ERROR! " << message << AfterText(passInfo) << std::endl;
}
std::string Logger::AfterText(PASS_INFO success) {

    std::string afterText;

    switch (success) {
        case NO_INFO : afterText = "";
        case FAIL    : afterText = failText_;
        case SUCCESS : afterText = successText_;
    }

    return afterText;
}
std::string Logger::PreText(LOG_TYPE logType) {

    std::string preText;

    switch (logType) {
        case GENERAL : preText = "|";
        case NETWORK : preText = "|NET|";
        case PHYSICS : preText = "|PHYS|";
        case DEBUG   : preText = "|DEBUG|";
        case RENDER  : preText = "|RENDER|";
    }

    return preText;
}

// TODO: Check this implementation for thread safety
Logger *Logger::GetInstance() {

    if (logger_ == nullptr) {
        logger_ = new Logger();
    }

    return logger_;

}
Logger::Logger() {

}

}