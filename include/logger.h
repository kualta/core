#ifndef INTERFACERS_LOGGER_H
#define INTERFACERS_LOGGER_H

#include <string>

// Umm... We'll talk about this one later, ok?
#undef ERROR

namespace core {

    enum LOG_LEVEL {
        INFO,
        WARN,
        ERROR,
    };

    void Log(LOG_LEVEL level, const std::string& message);

    void LogInfo(const std::string& message);
    void LogWarn(const std::string& message);
    void LogError(const std::string& message);
}


#endif //INTERFACERS_LOGGER_H
