#ifndef CORE_GUI_H
#define CORE_GUI_H

#include "core/Essentials.h"
#include "core/Math.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace core {

class GUI {
public:

    static bool Button(const string& label = "Button", Vector2 size = { 0, 0 } );
    static bool CheckBox(const string& label, bool* value);
    static void Text(const string& text);

    template<typename T>
    static bool Input(const string& label, T *value);

protected:

    template<typename T>
    static bool InputMatrix(const string& label, T* mtx);

};


}

#include "GUI.tpp"

#endif //CORE_GUI_H
