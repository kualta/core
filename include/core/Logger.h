#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

#include "Essential.h"
#include "Singleton.h"
#include "Object.h"

#include <ostream>
#include <sstream>
#include <chrono>
#include <algorithm>

namespace core {

enum logLevel {
    ERR,
    WARN,
    INFO,
    DEBUG,
};
enum objectTag {
    INTERNAL, // For engine logs
    GENERAL,  // For other logs
    NETWORK,  // Network module logs
    PHYSICS,  // Physics module logs
    OBJECT,   // Objects logs
    WINDOW,   // Window module logs
    RENDER,   // Rendering module logs
    SCENE,    // Scene module logs
    INPUT,    // Scene module logs
};
enum passInfo {
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
    static Log Log(logLevel level, objectTag tag = GENERAL);

    /**
     * Adds current time stamp to string stream
     * @note Format: HH.MM.SS.ms
     * @note CORE_LOG_DATE defined macro changes format to YY/MM/DD HH:MM:SS.ms
     */
    static std::stringstream& AddTimeStamp(std::stringstream& stream);

    /**
     * Sets width and fill char for next value in stream
     * @param stream - stream to set values to
     * @param ch - char to fill the width with
     * @param width - width of filling
     * @return std::stringstream&
     */
    static std::stringstream& FillWidth(std::stringstream& stream, const char& ch, const int8_t& width);

    static string GetLogTypeText(objectTag tag);
    static string GetLogLevelText(logLevel level);
    static string GetPassText(passInfo success);
    static string ToUpper(string str);

}; // class Logger

class Log {
public:
    // Must be implemented in header
    Log(std::ostream& out, logLevel level, objectTag tag = GENERAL);
    ~Log();

    template<class T>
    Log& operator<<(const T& thing) {
        logStream << thing;
        return *this;
    };

private:
    std::stringstream logStream;
    std::ostream& output;
}; // class Log

}

#endif //CORE_LOGGER_H
