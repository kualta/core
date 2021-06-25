#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "Essential.h"
#include "Primitive.h"
#include "Object.h"
#include "Vector.h"
#include "Logger.h"

#include <SDL_syswm.h>

namespace core {

class Window : public Object {
public:
    Window(const std::string &title, const core::Rect &rect);
    ~Window();

    uint32_t GetHeight() const;
    int32_t GetFrameBufferHeight() const;
    uint32_t GetWidth() const;
    int32_t GetFrameBufferWidth() const;
    Vector2 GetPosition() const;
    SDL_Window* GetSdlWindow() const;
    SDL_SysWMinfo* GetSdlWmi() const;
    std::string GetTitle() const;

    void SetPosition(const Vector2& pos);

private:
    SDL_Window *sdlWindow;
    SDL_SysWMinfo sdlWmi;
    std::string title;
    Vector2 position;

    uint32_t height;
    uint32_t width;

    int32_t frameBufferHeight;
    int32_t frameBufferWidth;
};

} // namespace core

#endif //CORE_WINDOW_H
