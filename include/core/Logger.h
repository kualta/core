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

    /**
     * Creates a Log entry
     * @warning At every Log object destruction the stream flushes. Might cause
     * performance issues
     */
    static Log Log(LOG_LEVEL level, LOG_TYPE type = GENERAL);

    /**
     * Adds current time stamp to string stream
     * @note Format: HH.MM.SS.ms
     * @note CORE_LOG_DATE defined macro changes format to YY/MM/DD HH:MM:SS.ms
     */
    static std::stringstream& AddTimeStamp(std::stringstream& stream);

    static string GetLogTypeText(LOG_TYPE log_type);
    static string GetLogLevelText(LOG_LEVEL level);
    static string GetPassText(PASS_INFO success);


}; // class Logger

class Log {
public:
    Log(std::ostream& out, LOG_LEVEL level, LOG_TYPE type = GENERAL) : output(out) {
        logStream << "- ";
        Logger::AddTimeStamp(logStream) << " ";
        logStream << Logger::GetLogTypeText(type) << " ";
        logStream << Logger::GetLogLevelText(level);
    }
    ~Log() {
        logStream << "\n";
        output << logStream.rdbuf();
        output.flush();
    }

    template <class T>
    Log& operator<<(const T& thing) {
        logStream << thing;
        return *this;
    }

private:
    std::stringstream logStream;
    std::ostream& output;
}; // class Log

}

#endif //CORE_LOGGER_H
