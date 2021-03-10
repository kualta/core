
#include <Utility.h>

#include "core.h"

namespace core {

/// Returns Unit ID of the created Window in core.
/// Use this ID to refer to this window from anywhere.
unsigned int core::MakeWindow(const std::string& title, Rect rect) {
    Window* _window = new Window(title, rect);

    return 0;
}


}