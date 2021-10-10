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
    static bool CheckBox(const string& label, bool& value);
    static void Text(const string& text);
    static void TextLabel(const string& text, const string& label);
    static void Tooltip(const string& text);

    static bool Box(bool& value);
    static void EndBox();

    template<typename T>
    static bool Input(const string& label, T *value);

    template<typename T>
    static bool Slider(const string& label, T* value, float min, float max);

    static bool IsHovered();
    static bool IsActive();
    static bool IsFocused();

protected:

    template<typename T>
    static bool InputMatrix(const string& label, T* mtx);

};

} // namespace core

#include "GUI.tpp"

#endif //CORE_GUI_H
