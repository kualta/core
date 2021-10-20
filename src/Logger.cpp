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
#include <core/Logger.h>
#include <iostream>
#include <ctime>
#include <utility>
#include "core/ObjectTag.h"

namespace core {

Logger::Logger() : Object("Logger") {

}
LogEntry Logger::Log(ObjectTag tag, LogLevel level, const LogPlace& place) {
    switch (level) {
        case   ERR: return core::LogEntry {std::cout, ERR, tag, place };
        case  WARN: return core::LogEntry {std::cout, WARN, tag, place };
        case  INFO: return core::LogEntry {std::cout, INFO, tag, place };
        case DEBUG: return core::LogEntry {std::cout, DEBUG, tag, place };
    }
    return core::LogEntry {std::cout, ERR, INTERNAL };
}
string Logger::GetPassText(PassInfo success) {
   string text;

    switch (success) {
        case NO_INFO: text = ""; break;
        case    FAIL: text = "- failed"; break;
        case SUCCESS: text = "- success"; break;
    }

    return text;
}
string Logger::GetLogLevelText(LogLevel level) {
    string text;

    switch (level) {
        case   ERR: text = " ERROR! "; break;
        case  WARN: text = " WARN: ";  break;
        case  INFO: text = " ";        break;
        case DEBUG: text = " ";        break;
    }

    return text;
}
string Logger::GetLogTypeText(ObjectTag tag) {
    string text;

    switch (tag) {
        case  GENERAL: text = "        "; break;
        case   OBJECT: text = "       >"; break;
        case  NETWORK: text = "   |NET|"; break;
        case   MEMORY: text = "   |MEM|"; break;
        case INTERNAL: text = "  |CORE|"; break;
        case  PHYSICS: text = "  |PHYS|"; break;
        case    SCENE: text = " |SCENE|"; break;
        case   MODULE: text = "|MODULE|"; break;
        case   IMPORT: text = "|IMPORT|"; break;
        case   RENDER: text = "|RENDER|"; break;
        case   WINDOW: text = "|WINDOW|"; break;
        case   EDITOR: text = "|EDITOR|"; break;
    }

    return text;
}
string Logger::GetPlaceText(const LogPlace& place) {
    // TODO: Add build option to include place.functionName in the text

    if ( !place.exist ) {
        return "";
    }

    string text = " - at [";

    text += place.fileName;
    text += ":";
    text += std::to_string(place.lineNumber);
    text += "]";

    return text;
}
// FIXME: That's way too heavy for every single log, refactoring needed
std::stringstream& Logger::LogTimeStamp(std::stringstream& stream) {
    auto now = std::chrono::system_clock::now();

    auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
    auto fraction = now - seconds;
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(fraction);

    const std::time_t cnow = std::chrono::system_clock::to_time_t(now);
    const std::tm localTime = *std::localtime(std::addressof(cnow));

    // Macro is defined by CORE_LOG_DATE option in CMake
    #ifdef CORE_LOG_DATE
        stream << localTime.tm_year + 1900 << "/" << localTime.tm_mon + 1 << "/" << localTime.tm_mday << " ";
    #endif

    // FIXME: Ugly, refactoring needed!
    FillWidth(stream, '0', 2);
    stream << localTime.tm_hour << ":";

    FillWidth(stream, '0', 2);
    stream << localTime.tm_min << ":";

    FillWidth(stream, '0', 2);
    stream << localTime.tm_sec << ".";

    FillWidth(stream, '0', 3);
    stream << milliseconds.count();

    stream << " ";

    return stream;
}
std::stringstream &Logger::LogTagText(std::stringstream &stream, ObjectTag tag) {
    stream << GetLogTypeText(tag);

    return stream;
}
std::stringstream &Logger::LogLevelText(std::stringstream &stream, LogLevel level) {
    stream << GetLogLevelText(level);

    return stream;
}
std::stringstream &Logger::FillWidth(std::stringstream &stream, const char& ch, const int8_t& width) {
    stream.fill(ch);
    stream.width(width);

    return stream;
}
string Logger::ToUpper(string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return std::move(str);
}
LogEntry::~LogEntry() {
    logStream << Logger::GetPlaceText(logPlace);
    logStream << "\n";
    output << logStream.rdbuf();
    output.flush();
}
LogEntry::LogEntry(std::ostream &out, LogLevel level, ObjectTag tag, LogPlace logPlace)
: level(level),
logPlace(std::move(logPlace)),
output(out)
{
    logStream << "- ";
    Logger::LogTimeStamp(logStream);
    Logger::LogTagText(logStream, tag);
    Logger::LogLevelText(logStream, level);
}

LogEntry Log(ObjectTag tag, LogLevel level, const LogPlace &place) {
    return Logger::Log(tag, level, place);
}

} // namespace core