#include <core/Logger.h>
#include <iostream>


namespace core {


// TODO: Simplify logging syntax
// TODO: Add time/date stamps to logs
Logger::Logger() {
}

std::ostringstream& Logger::Log(LOG_LEVEL level)
{
    os << "- " << TimeNow();
    os << " " << LevelText(level);
    return os;
}
string Logger::PassText(PASS_INFO success) {

   string afterText;

    switch (success) {
        case NO_INFO : afterText = ""; break;
        case FAIL    : afterText = "- failed"; break;
        case SUCCESS : afterText = "- success"; break;
    }

    return afterText;
}
string Logger::LevelText(LOG_LEVEL level) {

    string afterText;

    switch (level) {
        case ERR : afterText = "ERROR!"; break;
        case WARN : afterText = "WARN:"; break;
        case INFO : afterText = ":"; break;
        case DEBUG : afterText = ""; break;
    }

    return afterText;
}
string Logger::TypeText(LOG_TYPE log_type) {

    string preText;

    switch (log_type) {
        case GENERAL : preText = "|"; break;
        case NETWORK : preText = "|NET|"; break;
        case INTERNAL: preText = "|CORE|"; break;
        case PHYSICS : preText = "|PHYS|"; break;
        case DEBUG   : preText = "|DEBUG|"; break;
        case WINDOW  : preText = "|WINDOW|"; break;
        case RENDER  : preText = "|RENDER|"; break;
    }

    return preText;
}
string Logger::TimeNow() {
    // TODO: Implement timestamp
    return "23:23:23.141";
}

}