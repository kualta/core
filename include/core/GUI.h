#ifndef CORE_GUI_H
#define CORE_GUI_H

#include "Essentials.h"
#include "Math.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace core {

class GUI {
public:

    static bool Button(const string& title = "Button", Vector2 pos = { 0, 0 } );

};


}

#endif //CORE_GUI_H
