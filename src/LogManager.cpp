#include <LogManager.h>
#include <iostream>
#include <string>


namespace core {


// TODO: Add time/date stamps to logs
void LogManager::Log(LOG_LEVEL level, const std::string& message, LOG_TYPE type, PASS_INFO success) {
    switch (level) {
        case INFO  : LogManager::LogInfo(message, type, success);
        case WARN  : LogManager::LogWarn(message, type, success);
        case ERR   : LogManager::LogError(message, type, success);
    }
}
void LogManager::LogInfo(const std::string& message, LOG_TYPE logType, PASS_INFO passInfo) {
    std::cout << PreText(logType) << "INFO: " << message << AfterText(passInfo) << std::endl;
}
void LogManager::LogWarn(const std::string& message, LOG_TYPE logType, PASS_INFO passInfo) {
    std::cout << PreText(logType) << "WARN: " << message << AfterText(passInfo) << std::endl;
}
void LogManager::LogError(const std::string& message, LOG_TYPE logType, PASS_INFO passInfo) {
    std::cout << PreText(logType) << "ERROR! " << message << AfterText(passInfo) << std::endl;
}
std::string LogManager::AfterText(PASS_INFO success) {

    std::string afterText;

    switch (success) {
        case NO_INFO : afterText = "";
        case FAIL    : afterText = failText_;
        case SUCCESS : afterText = successText_;
    }

    return afterText;
}
std::string LogManager::PreText(LOG_TYPE logType) {

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

LogManager::LogManager() {

}

}