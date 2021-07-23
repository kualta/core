#include <core/Modules/InputModule.h>
#include "SDL_keyboard.h"

namespace core {


InputModule::InputModule() : IModule("Input", INPUT_T) {

}
InputModule::~InputModule() {

}
void InputModule::Tick() {
    PollEvents();
    keystate = SDL_GetKeyboardState(nullptr);
}
void InputModule::PollEvents() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if ( event.key.keysym.sym == SDLK_ESCAPE ) exitRequested = true;
            break;

            case SDL_QUIT:                OnExitRequest(); break;
            case SDL_WINDOWEVENT_RESIZED: OnWindowResize(); break;
        }
    }
}
void InputModule::OnExitRequest() {
    exitRequested = true;
}
void InputModule::OnWindowResize() {

}

}