#include <core/Input/KeyEvent.h>
#include <SDL_keyboard.h>

namespace core {

string KeyEvent::KeyName(Key key) {
    return SDL_GetKeyName(SDL_Keycode(key));
}

string KeyEvent::KeyName() const {
    return KeyName(key);
}

}
