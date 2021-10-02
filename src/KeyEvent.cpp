#include <core/KeyEvent.h>
#include <SDL_keyboard.h>

namespace core {

string KeyEvent::keyName(const Key key) {
    return SDL_GetKeyName(SDL_Keycode(key));
}

string KeyEvent::keyName() const {
    return keyName(_key);
}

}
