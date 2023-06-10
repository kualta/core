/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
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
#include <core/Input/MouseEvent.h>
#include <SDL_keyboard.h>

namespace core {

InputEvent::Modifiers FixedModifiers(Uint16 mod) {
    InputEvent::Modifiers modifiers(static_cast<InputEvent::Modifier>(mod));
    if (modifiers & InputEvent::Modifier::Shift) modifiers |= InputEvent::Modifier::Shift;
    if (modifiers & InputEvent::Modifier::Ctrl)  modifiers |= InputEvent::Modifier::Ctrl;
    if (modifiers & InputEvent::Modifier::Alt)   modifiers |= InputEvent::Modifier::Alt;
    if (modifiers & InputEvent::Modifier::Super) modifiers |= InputEvent::Modifier::Alt;
    return modifiers;
}
InputEvent::Modifiers MouseEvent::GetModifiers() {
    if (modifiers) return *modifiers;

    return *(modifiers = FixedModifiers(Uint16(SDL_GetModState())));
}
InputEvent::Modifiers MouseMoveEvent::GetModifiers() {
    if (modifiers) return *modifiers;

    return *(modifiers = FixedModifiers(Uint16(SDL_GetModState())));
}
Vector2i MouseScrollEvent::GetPosition() {
    if (position) return *position;

    position = Vector2i{ };
    SDL_GetMouseState(&position->x(), &position->y());
    return *position;
}
InputEvent::Modifiers MouseScrollEvent::GetModifiers() {
    if (modifiers) return *modifiers;

    return *(modifiers = FixedModifiers(Uint16(SDL_GetModState())));
}

}

