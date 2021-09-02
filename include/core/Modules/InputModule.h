#ifndef CORE_INPUTMODULE_H
#define CORE_INPUTMODULE_H

#include <core/IModule.h>
#include <core/Publisher.h>

#include <SDL.h>
#include <memory>
#include <functional>

namespace core {


class InputModule : public IModule, public Publisher {
public:
    InputModule();
    ~InputModule();

    void Tick() override;

    bool exitRequested { false };

protected:
    void PollEvents();

    SDL_Event       event;
    const uint8_t*  keystate;

private:

    void CreateEvents();

    void OnExitRequest();
    void OnWindowResize();


};


}


#endif //CORE_INPUTMODULE_H
