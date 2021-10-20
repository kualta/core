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
