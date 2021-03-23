#include "LogManager.h"
#include <iostream>
#include <string>


namespace core {


// TODO: Simplify logging syntax
// TODO: Add time/date stamps to logs
LogManager::LogManager() {
}
void LogManager::LogInfo(const std::string &message, LOG_TYPE logType) {
    std::cout << TypeText(logType) << " INFO: " << message << std::endl;
}
void LogManager::LogWarn(const std::string& message, LOG_TYPE logType) {
    std::cout << TypeText(logType) << " WARN: " << message << std::endl;
}
void LogManager::LogError(const std::string& message, LOG_TYPE logType) {
    std::cout << TypeText(logType) << " ERROR! " << message << std::endl;
}
std::string LogManager::PassText(PASS_INFO success) {

    std::string afterText;

    switch (success) {
        case NO_INFO : afterText = "";
        case FAIL    : afterText = "- failed";
        case SUCCESS : afterText = "- success";
    }

    return afterText;
}
std::string LogManager::TypeText(LOG_TYPE log_type) {

    std::string preText;

    switch (log_type) {
        case GENERAL : preText = "|";
        case NETWORK : preText = "|NET|";
        case INTERNAL: preText = "|CORE|";
        case PHYSICS : preText = "|PHYS|";
        case DEBUG   : preText = "|DEBUG|";
        case RENDER  : preText = "|RENDER|";
        case WINDOW  : preText = "|WINDOW|";
    }

    return preText;
}


}