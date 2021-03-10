
#include <utility.h>

#include "core.h"

namespace core {

/// Returns Unit ID of the created Window in Core.
/// Use this ID to refer to this window from anywhere.
unsigned int core::MakeWindow(const std::string& title, Rect rect) {
    Window* mainWindow = new Window(title, rect);

    return 0;
}


}