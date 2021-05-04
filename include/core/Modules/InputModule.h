#ifndef CORE_INPUTMODULE_H
#define CORE_INPUTMODULE_H

#include <core/IModule.h>

#include <SDL_events.h>
#include <memory>

namespace core {


class InputModule : public IModule {
public:
    InputModule();
    ~InputModule();

    void Update();

    bool GetAnyKey();

    bool exitRequested { false };

protected:
    SDL_Event event;
    void PollEvents();

private:

};


}


#endif //CORE_INPUTMODULE_H
