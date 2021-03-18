#ifndef CORE_WINDOW_H
#define CORE_WINDOW_H

#include <SDL.h>
#include <string>

#include "Context.h"
#include "Geometry.h"
#include "ObjectId.h"


namespace core {


    class Window : public ObjectId {
    public:
        Window(const std::string &title, const core::Rect &rect);
        ~Window();

        uint32_t GetWindowID() const;
        uint32_t GetHeight() const;
        uint32_t GetWidth() const;
        Vector2 GetPosition() const;
        SDL_Window *GetSdlWindowPtr() const;
        std::string GetTitle() const;

        int SetPosition(const Vector2& pos);

    private:
        SDL_Window *sdlWindow;
        std::string title;
        Vector2 position;
        Context context;
        uint32_t height;
        uint32_t width;

        uint32_t id;
    };



}

#endif //CORE_WINDOW_H
