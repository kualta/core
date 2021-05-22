#ifndef CORE_INPUTMODULE_H
#define CORE_INPUTMODULE_H

#include <core/IModule.h>

#include <SDL.h>
#include <memory>

namespace core {


class InputModule : public IModule {
public:
    InputModule();
    ~InputModule();

    void Tick() override;

    bool GetAnyKey();

    bool exitRequested { false };

protected:
    SDL_Event       event;
    const uint8_t*  keystate;

    void PollEvents();

private:

};


}


#endif //CORE_INPUTMODULE_H
