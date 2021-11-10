/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#ifndef CORE_LOGGER_H
#define CORE_LOGGER_H

#include "Essentials.h"
#include "Singleton.h"
#include "Object.h"
#include "ObjectTag.h"

#include <ostream>
#include <sstream>
#include <chrono>
#include <algorithm>
#include <utility>

#ifndef LOG_HERE
#   ifdef CORE_LOG_FULL_PATH
#       define LOG_HERE LogPlace { true, __FILE__, __FUNCTION__, __LINE__ }
#   else
#       define LOG_HERE LogPlace { true, __FILENAME__, __FUNCTION__, __LINE__ }
#   endif
#endif

#ifndef WARN_HERE
#   define WARN_HERE LogLevel::WARN, LOG_HERE
#endif

#ifndef ERR_HERE
#   define ERR_HERE LogLevel::ERR, LOG_HERE
#endif

#ifndef INFO_HERE
#   define INFO_HERE LogLevel::INFO, LOG_HERE
#endif

#ifndef DEBUG_HERE
#   define DEBUG_HERE LogLevel::DEBUG, LOG_HERE
#endif

#ifndef NEW_LINE
#   define NEW_LINE string('\n') + string(16, ' ') + string(' |')
#endif

namespace core {

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERR,
};

enum PassInfo {
    SUCCESS,
    NO_INFO,
    FAIL,
};

struct LogPlace {
    bool    exist = false;
    string  fileName;
    string  functionName;
    int32_t lineNumber;
};

class Logger : public Object {
public:
    Logger();
    ~Logger() = default;

    /**
     * Creates a Log entry
     * @warning At every Log object destruction the stream flushes. Might cause
     * performance issues
     */
    static LogEntry Log(ObjectTag tag = GENERAL, LogLevel level = INFO, const LogPlace& place = { });

    /**
     * Sets width and fill char for next value in stream
     * @param stream - stream to set values to
     * @param ch - char to fill the width with
     * @param width - width of filling
     * @return std::stringstream&
     */
    static std::stringstream& FillWidth(std::stringstream& stream, const char& ch, const int8_t& width);
    
    /**
     * Set minimal LogLevel for the log entry to appear
     * @note default: LogLevel::INFO
     * @details if log entry level is lower than minimal, it will be skipped in the output stream
     */
    static void SetMinLogLevel(LogLevel level);
    
    /**
     * Get minimal LogLevel for log entry to appear
     * @return
     */
    static LogLevel GetMinLogLevel();
    
    /**
     * Get ObjectTag text
     * @note Format: |MODULE|
     */
    static string GetObjectTagText(ObjectTag tag);
    
    /**
     * Get LogLevel text
     * @note Format: ERROR!, WARN:, or empty string
     */
    static string GetLogLevelText(LogLevel level);
    
    /**
     * Get LogPlace text
     * @note Format: - at [filename::line]
     */
    static string GetLogPlaceText(const LogPlace& place);
    
    /**
     * Get PassInfo text
     * @note Format: - success, - failed or empty string
     */
    static string GetPassText(PassInfo success);
    
    /**
     * Convert all characters in string to uppercase
     */
    static string ToUpper(string str);

protected:
    friend class LogEntry;
    
    /**
     * Adds current time stamp to string stream
     * @note Format: HH.MM.SS.ms
     * @note CORE_LOG_DATE defined macro changes format to YY/MM/DD HH:MM:SS.ms
     */
    static std::stringstream& LogTimeStamp(std::stringstream& stream);
    
    /**
     * Adds ObjectTag text to string stream
     * @note Format: |MODULE|
     */
    static std::stringstream& LogTagText(std::stringstream& stream, ObjectTag tag);
    
    /**
     * Adds LogLevel text to string stream
     * @note Format: ERROR!, WARN:, or empty string
     */
    static std::stringstream& LogLevelText(std::stringstream& stream, LogLevel level);
    
    static LogLevel minLogLevel;
    
}; // class Logger

class LogEntry {
public:
    LogEntry(std::ostream& out, LogLevel level = INFO, ObjectTag tag = GENERAL, LogPlace place = { });
    ~LogEntry();

    template<class T>
    LogEntry& operator<<(const T& thing) {
        stream << thing;
        return *this;
    };

private:
    
    LogPlace            logPlace;
    LogLevel            level;
    std::ostream&       outStream;
    std::stringstream   stream;
    
}; // class LogEntry

/**
 * Global wraper of Logger::Log for rapid development
 */
LogEntry Log(ObjectTag tag = GENERAL, LogLevel level = INFO, const LogPlace& place = { });


}

#endif //CORE_LOGGER_H
