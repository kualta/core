#include <core/MouseEvent.h>
#include <SDL_keyboard.h>

namespace core {

InputEvent::Modifiers fixedModifiers(Uint16 mod) {
    InputEvent::Modifiers modifiers(static_cast<InputEvent::Modifier>(mod));
    if (modifiers & InputEvent::Modifier::Shift) modifiers |= InputEvent::Modifier::Shift;
    if (modifiers & InputEvent::Modifier::Ctrl)  modifiers |= InputEvent::Modifier::Ctrl;
    if (modifiers & InputEvent::Modifier::Alt)   modifiers |= InputEvent::Modifier::Alt;
    if (modifiers & InputEvent::Modifier::Super) modifiers |= InputEvent::Modifier::Alt;
    return modifiers;
}
InputEvent::Modifiers MouseEvent::modifiers() {
    if(_modifiers) return *_modifiers;
    return *(_modifiers = fixedModifiers(Uint16(SDL_GetModState())));
}
InputEvent::Modifiers MouseMoveEvent::modifiers() {
    if(_modifiers) return *_modifiers;
    return *(_modifiers = fixedModifiers(Uint16(SDL_GetModState())));
}
Vector2i MouseScrollEvent::position() {
    if(_position) return *_position;
    _position = Vector2i{};
    SDL_GetMouseState(&_position->x(), &_position->y());
    return *_position;
}
InputEvent::Modifiers MouseScrollEvent::modifiers() {
    if(_modifiers) return *_modifiers;
    return *(_modifiers = fixedModifiers(Uint16(SDL_GetModState())));
}

}

