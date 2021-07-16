#include <core/Modules/InputModule.h>
#include "SDL_keyboard.h"

namespace core {


InputModule::InputModule() : IModule("Input", INPUT_T) {

}
InputModule::~InputModule() {

}
bool InputModule::GetAnyKey() {
    throw std::runtime_error("Not yet implemented");
}
void InputModule::Tick() {
    PollEvents();
    keystate = SDL_GetKeyboardState(nullptr);
}
void InputModule::PollEvents() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exitRequested = true;
            break;
            case SDL_KEYDOWN:
                if ( event.key.keysym.sym == SDLK_ESCAPE ) exitRequested = true;
            break;
        }
    }
}

}