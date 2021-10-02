#include <core/Modules/InputModule.h>
#include <core/Event.h>
#include <core/ViewportEvent.h>
#include <core/KeyEvent.h>
#include <core/MouseEvent.h>
#include <core/GestureEvent.h>
#include <core/TextEvent.h>
#include <core/ExitEvent.h>

#include "SDL_keyboard.h"

namespace core {

InputEvent::Modifiers fixedModifiers(Uint16 mod) {
    InputEvent::Modifiers modifiers(static_cast<InputEvent::Modifier>(mod));
    if (modifiers & InputEvent::Modifier::Shift) modifiers |= InputEvent::Modifier::Shift;
    if (modifiers & InputEvent::Modifier::Ctrl)  modifiers |= InputEvent::Modifier::Ctrl;
    if (modifiers & InputEvent::Modifier::Alt)   modifiers |= InputEvent::Modifier::Alt;
    if (modifiers & InputEvent::Modifier::Super) modifiers |= InputEvent::Modifier::Alt;
    return modifiers;
}


InputModule::InputModule() : IModule("Input", INPUT_T) {

}
InputModule::~InputModule() {

}
void InputModule::Tick() {
    PollEvents();
    keystate = SDL_GetKeyboardState(nullptr);
}
void InputModule::PollEvents() {
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_WINDOWEVENT:
                switch(event.window.event) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED: {
                        Vector2i size = Vector2i(event.window.data1, event.window.data2);
                        ViewportEvent viewportEvent { event, size, size, {1, 1} };
                        OnViewportEvent.Trigger(viewportEvent);
                    } break;
                    case SDL_WINDOWEVENT_EXPOSED:
                        // TODO: Add SDL_WINDOWEVENT_EXPOSED handling
                        break;
                    default:
                        // TODO: Add Default handling
                        break;
                } break;

            case SDL_KEYDOWN:
            case SDL_KEYUP: {
                KeyEvent keyEvent { event, static_cast<KeyEvent::Key>(event.key.keysym.sym), fixedModifiers(event.key.keysym.mod), event.key.repeat != 0 };
                OnKeyEvent.Trigger(keyEvent);
            } break;

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP: {
                MouseEvent mouseEvent{event, static_cast<MouseEvent::Button>(event.button.button), { event.button.x, event.button.y }, event.button.clicks};
                OnMouseEvent.Trigger(mouseEvent);
            } break;

            case SDL_MOUSEWHEEL: {
                MouseScrollEvent mouseScrollEvent { event, { Float(event.wheel.x), Float(event.wheel.y) } };
                OnMouseScrollEvent.Trigger(mouseScrollEvent);
            } break;

            case SDL_MOUSEMOTION: {
                MouseMoveEvent mouseMoveEvent{event, {event.motion.x, event.motion.y}, {event.motion.xrel, event.motion.yrel}, static_cast<MouseMoveEvent::Button>(event.motion.state)};
                OnMouseMoveEvent.Trigger(mouseMoveEvent);
            } break;

            case SDL_MULTIGESTURE: {
                MultiGestureEvent multiGestureEvent { event, { event.mgesture.x, event.mgesture.y },
                                                     event.mgesture.dTheta, event.mgesture.dDist, event.mgesture.numFingers };
                OnMultigestureEvent.Trigger(multiGestureEvent);
            } break;

            case SDL_TEXTINPUT: {
                TextInputEvent textInputEvent {event, { event.text.text, std::strlen(event.text.text) } };
                OnTextInputEvent.Trigger(textInputEvent);
            } break;

            case SDL_TEXTEDITING: {
                TextEditingEvent textEditingEvent { event, { event.edit.text, std::strlen(event.text.text) },
                                                    event.edit.start,
                                                    event.edit.length };
                OnTextEditingEvent.Trigger(textEditingEvent);
            } break;

            case SDL_QUIT: {
                ExitEvent exitEvent { event };
                OnExitEvent.Trigger(exitEvent);
            } break;

            default:
                // TODO: Add default handling
                break;
        }
    }
}

}