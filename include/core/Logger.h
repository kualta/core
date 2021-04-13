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
    Logger();

    static std::ostringstream& Log(LOG_LEVEL level = INFO);

    static string PassText(PASS_INFO success);
    static string LevelText(LOG_LEVEL level);
    static string TypeText(LOG_TYPE log_type);
    static string TimeNow();


protected:
    // FIXME: current implementation is not thread-safe!
    static std::ostringstream os;

};


}

#endif //CORE_LOGGER_H
