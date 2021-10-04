#ifndef CORE_INPUTMODULE_H
#define CORE_INPUTMODULE_H

#include <core/IModule.h>
#include <core/Publisher.h>
#include <core/Event.h>
#include <core/Input/KeyEvent.h>
#include <core/Input/MouseEvent.h>
#include <core/Input/ViewportEvent.h>
#include <core/Input/TextEvent.h>
#include <core/Input/GestureEvent.h>
#include <core/Input/ExitEvent.h>

#include <SDL.h>
#include <memory>
#include <functional>

namespace core {


class InputModule : public IModule, public Publisher {
public:
    InputModule();

    void EarlyTick() override;

    bool exitRequested { false };

    Event<KeyEvent>          OnKeyPressEvent;
    Event<KeyEvent>          OnKeyReleaseEvent;
    Event<ViewportEvent>     OnViewportEvent;
    Event<MouseEvent>        OnMouseReleaseEvent;
    Event<MouseEvent>        OnMousePressEvent;
    Event<MouseMoveEvent>    OnMouseMoveEvent;
    Event<MouseScrollEvent>  OnMouseScrollEvent;
    Event<MultiGestureEvent> OnMultigestureEvent;
    Event<TextEditingEvent>  OnTextEditingEvent;
    Event<TextInputEvent>    OnTextInputEvent;
    Event<ExitEvent>         OnExitEvent;

protected:
    void PollEvents();

    SDL_Event       event;
    const uint8_t*  keystate;

};


}


#endif //CORE_INPUTMODULE_H
