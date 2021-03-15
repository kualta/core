#include <LogManager.h>
#include <iostream>
#include <string>


namespace core {


// TODO: Simplify logging syntax
// TODO: Add time/date stamps to logs
void LogManager::Log(LOG_LEVEL level, const std::string& message, LOG_TYPE type, PASS_INFO success) {
    // TODO: this switch could be replaced with one function
    switch (level) {
        case INFO  : LogManager::LogInfo(message, type, success);
        case WARN  : LogManager::LogWarn(message, type, success);
        case ERR   : LogManager::LogError(message, type, success);
    }
}
void LogManager::LogInfo(const std::string& message, LOG_TYPE logType, PASS_INFO passInfo) {
    std::cout << TypeText(logType) << "INFO: " << message << PassText(passInfo) << std::endl;
}
void LogManager::LogWarn(const std::string& message, LOG_TYPE logType, PASS_INFO passInfo) {
    std::cout << TypeText(logType) << "WARN: " << message << PassText(passInfo) << std::endl;
}
void LogManager::LogError(const std::string& message, LOG_TYPE logType, PASS_INFO passInfo) {
    std::cout << TypeText(logType) << "ERROR! " << message << PassText(passInfo) << std::endl;
}
std::string LogManager::PassText(PASS_INFO success) {

    std::string afterText;

    switch (success) {
        case NO_INFO : afterText = "";
        case FAIL    : afterText = failText_;
        case SUCCESS : afterText = successText_;
    }

    return afterText;
}
std::string LogManager::TypeText(LOG_TYPE log_type) {

    std::string preText;

    switch (log_type) {
        case GENERAL : preText = "|";
        case NETWORK : preText = "|NET|";
        case PHYSICS : preText = "|PHYS|";
        case DEBUG   : preText = "|DEBUG|";
        case RENDER  : preText = "|RENDER|";
        case WINDOW  : preText = "|WINDOW|";
    }

    return preText;
}

LogManager::LogManager() {

}

}