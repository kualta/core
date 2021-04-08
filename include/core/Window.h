#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "Essential.h"
#include "Object.h"
#include "Vector.h"

#include <SDL_syswm.h>

namespace core {


    class Window : public Object {
    public:
        Window(const std::string &title, const core::Rect &rect);
        ~Window();

        uint32_t GetHeight() const;
        uint32_t GetWidth() const;
        Vector2 GetPosition() const;
        SDL_Window* GetSdlWindowPtr() const;
        SDL_SysWMinfo* GetSdlWmiPtr() const;
        std::string GetTitle() const;

        int SetPosition(const Vector2& pos);

    private:
        SDL_Window *sdlWindow;
        SDL_SysWMinfo sdlWmi;
        std::string title;
        Vector2 position;
        uint32_t height;
        uint32_t width;
    };



}

#endif //CORE_WINDOW_H
