#ifndef INTERFACERS_LOGGER_H
#define INTERFACERS_LOGGER_H

#include <string>


namespace core {

    enum LOG_LEVEL {
        INFO,
        WARN,
        ERR,
    };

    void Log(LOG_LEVEL level, const std::string& message);

    void LogInfo(const std::string& message);
    void LogWarn(const std::string& message);
    void LogError(const std::string& message);
}


#endif //INTERFACERS_LOGGER_H
