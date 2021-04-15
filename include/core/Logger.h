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
    DEBUG,
};
enum LOG_TYPE {
    GENERAL,  // For other logs
    PHYSICS,
    NETWORK,
    INTERNAL, // For engine logs
    RENDER,   // For drawing & rendering logs
    WINDOW,   // For window handler logs
};
enum PASS_INFO {
    SUCCESS,
    NO_INFO,
    FAIL,
};
class Logger : public Singleton<Logger>, public Object {
public:
    Logger() = default;

    static Log Log(LOG_LEVEL level, LOG_TYPE type = GENERAL);

    static string GetLogEntryText(LOG_TYPE type, LOG_LEVEL level);
private:
    static string PassText(PASS_INFO success);
    static string LevelText(LOG_LEVEL level);
    static string TypeText(LOG_TYPE log_type);
    static string TimeNow();
}; // class Logger

class Log {
public:
    Log(std::ostream& out, LOG_LEVEL level, LOG_TYPE type = GENERAL) : output(out) {
        stream << Logger::GetLogEntryText(type, level);
    }
    ~Log() {
        stream << "\n";
        output << stream.rdbuf();
        output.flush();
    }

    template <class T>
    Log& operator<<(const T& thing) { stream << thing; return *this; }

private:
    std::stringstream stream;
    std::ostream& output;
};


}

#endif //CORE_LOGGER_H
