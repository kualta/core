#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include "Essential.h"

namespace core {


    class Window : public ObjectId {
    public:
        Window(const std::string &title, const core::Rect &rect);
        ~Window();

        uint32_t GetHeight() const;
        uint32_t GetWidth() const;
        Vector2 GetPosition() const;
        SDL_Window* GetSdlWindowPtr() const;
        std::string GetTitle() const;
        SDL_SysWMinfo& GetSdlWmi();

        int SetPosition(const Vector2& pos);

    private:
        SDL_Window* sdlWindow;
        SDL_SysWMinfo sdlWmi;
        std::string title;
        Vector2 position;
        uint32_t height;
        uint32_t width;
    };



}

#endif //CORE_WINDOW_H
