/*
 * This is a stand-alone header file. No ViewportEvent.cpp is presented.
 */
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
                2020, 2021 Vladimír Vondruš <mosra@centrum.cz>
    Copyright © 2019 Marco Melorio <m.melorio@icloud.com>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/
#ifndef CORE_VIEWPORTEVENT_H
#define CORE_VIEWPORTEVENT_H

#include "core/Essentials.h"
#include "core/Math.h"

namespace core {

/** Viewport GetEvent */
class ViewportEvent {
    friend InputModule;
public:
    /**  Copying is not allowed */
    ViewportEvent(const ViewportEvent&) = delete;

    /**  Moving is not allowed */
    ViewportEvent(ViewportEvent&&) = delete;

    /**  Copying is not allowed */
    ViewportEvent& operator=(const ViewportEvent&) = delete;

    /**  Moving is not allowed */
    ViewportEvent& operator=(ViewportEvent&&) = delete;

    /**
     * @returns window size
     * @note On some platforms with HiDPI displays, window size can be different from GetFramebufferSize(). */
    Vector2i GetWindowSize() const { return windowSize; }

    /**
     * @returns framebuffer size of Viewport
     * @note On some platforms with HiDPI displays, framebuffer size can be different from  GetWindowSize(). */
    Vector2i GetFramebufferSize() const { return framebufferSize; }

    /**
     * @returns DPI scaling of Viewport
     * @note On some platforms moving an app between displays can result in DPI scaling value being changed in tandem with a
     * window / framebuffer size. Simply resizing a window doesn't change the DPI scaling value.
     */
    Vector2 GetDpiScaling() const { return dpiScaling; }

    /**
     *  Underlying SDL GetEvent
     *
     * Of type `SDL_WINDOWEVENT`.
     * @note Not available in  CORRADE_TARGET_EMSCRIPTEN "Emscripten".
     *   Sdl2Application::anyEvent()
     */
    const SDL_Event& GetEvent() const { return event; }

private:
    explicit ViewportEvent(const SDL_Event& event,
                           const Vector2i& windowSize,
                           const Vector2i& framebufferSize,
                           const Vector2& dpiScaling)
                           : event(event),
                             windowSize      { windowSize },
                             framebufferSize { framebufferSize },
                             dpiScaling      { dpiScaling } { }

    const SDL_Event& event;
    const Vector2i windowSize;
    const Vector2i framebufferSize;
    const Vector2 dpiScaling;
};

} // namespace core

#endif //CORE_VIEWPORTEVENT_H
