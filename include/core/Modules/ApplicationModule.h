#ifndef CORE_APPLICATIONMODULE_H
#define CORE_APPLICATIONMODULE_H

#include <core/Essentials.h>
#include <core/IModule.h>
#include <core/Application.h>

namespace core {

class ApplicationModule : public IModule {
public:
    ApplicationModule(InputModule* inputModule);

    void CreateApplication(const string &title = "Core Application", Rect rect = { 0, 0, 1280, 720 });

    Vector2 GetWindowDpiScale(uint32_t id = 0);
    Vector2i GetWindowSize(uint32_t id = 0);
    Vector2i GetFrameBufferSize(uint32_t id = 0);

    void SwapRedraw();
    void Redraw();

protected:

    void Start() override;
    void EarlyTick() override;
    void LateTick() override;

private:

    std::vector<Application*> apps;
    InputModule* inputModule;
};

}

#endif //CORE_APPLICATIONMODULE_H
