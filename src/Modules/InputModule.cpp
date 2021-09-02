#include <core/Modules/InputModule.h>
#include "SDL_keyboard.h"

namespace core {


InputModule::InputModule() : IModule("Input", INPUT_T) {
    CreateEvents();
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
                if ( event.key.keysym.sym == SDLK_ESCAPE ) OnExitRequest(); break;
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED) OnWindowResize(); break;

            case SDL_QUIT: OnExitRequest(); break;
        }
    }
}
void InputModule::OnExitRequest() {
    exitRequested = true;
    this->Trigger("OnExitRequest");
}
void InputModule::OnWindowResize() {
    this->Trigger("OnWindowResize");
}
void InputModule::CreateEvents() {
    // TODO: Add all window events
    this->AddEvent("OnExitRequest");
    this->AddEvent("OnWindowResize");
}

}