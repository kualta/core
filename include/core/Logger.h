#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

#include "Essential.h"
#include "Object.h"
#include "Singleton.h"

#include <ostream>
#include <sstream>
#include <chrono>

namespace core {


enum LOG_LEVEL {
    ERR,
    WARN,
    INFO,
    DEBUG1,
    DEBUG2,
    DEBUG3,
};
enum LOG_TYPE {
    GENERAL,  // For other logs
    PHYSICS,
    NETWORK,
    INTERNAL, // For engine logs
    RENDER,   // For drawing & rendering logs
    WINDOW,   // For window handler logs
    DEBUG,
};
enum PASS_INFO {
    SUCCESS,
    NO_INFO,
    FAIL,
};


class Logger : public Singleton<Logger>, public Object {

public:
    Logger();

    static void LogInfo(const std::string& message, LOG_TYPE logType = GENERAL);
    static void LogWarn(const std::string& message, LOG_TYPE logType = GENERAL);
    static void LogError(const std::string& message, LOG_TYPE logType = GENERAL);
    static void LogMessage(const std::string& message);

    static std::string PassText(PASS_INFO success);
    static std::string TypeText(LOG_TYPE log_type);
private:
};


}

#endif //CORE_LOGGER_H
