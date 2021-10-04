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

