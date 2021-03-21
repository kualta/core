#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <SDL.h>
#include <string>
#include <SDL_syswm.h>

#include "Context.h"
#include "Geometry.h"
#include "ObjectId.h"


namespace core {


    typedef struct WindowInfo {
        SDL_SysWMinfo wmi;
    } WindowInfo;

    class Window : public ObjectId {
    public:
        Window(const std::string &title, const core::Rect &rect);
        ~Window();

        uint32_t GetHeight() const;
        uint32_t GetWidth() const;
        Vector2 GetPosition() const;
        SDL_Window* GetSdlWindowPtr() const;
        WindowInfo* GetInfo() const;
        std::string GetTitle() const;
        SDL_SysWMinfo wmi;

        int SetPosition(const Vector2& pos);

    private:
        SDL_Window* sdlWindow;
        std::string title;
        Vector2 position;
        WindowInfo* info;
        Context context;
        uint32_t height;
        uint32_t width;
    };



}

#endif //CORE_WINDOW_H
