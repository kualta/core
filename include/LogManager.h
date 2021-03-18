#ifndef CORE_LOGMANAGER_H
#define CORE_LOGMANAGER_H

#include <string>
#include "Singleton.h"


namespace core {


enum LOG_LEVEL {
    INFO,
    WARN,
    ERR,
};
enum LOG_TYPE {
    GENERAL,
    PHYSICS,
    NETWORK,
    INTERNAL,
    RENDER,
    WINDOW,
    DEBUG,
};
enum PASS_INFO {
    SUCCESS,
    NO_INFO,
    FAIL,
};

class LogManager : public Singleton<LogManager> {

public:
    LogManager();

    static void LogInfo(const std::string& message, LOG_TYPE logType = GENERAL);
    static void LogWarn(const std::string& message, LOG_TYPE logType = GENERAL);
    static void LogError(const std::string& message, LOG_TYPE logType = GENERAL);
    static std::string PassText(PASS_INFO success);
    static std::string TypeText(LOG_TYPE log_type);

private:
};


}

#endif //CORE_LOGMANAGER_H
