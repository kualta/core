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
#ifndef CORE_MOUSEEVENT_H
#define CORE_MOUSEEVENT_H

#include "InputEvent.h"
#include "Math.h"

namespace core {

/** Mouse GetEvent */
class MouseEvent : public InputEvent {
    friend InputModule;
public:

    /** Mouse button */
    enum class Button: Uint8 {
        Left    = SDL_BUTTON_LEFT,         /**< Left button */
        Middle  = SDL_BUTTON_MIDDLE,     /**< Middle button */
        Right   = SDL_BUTTON_RIGHT,       /**< Right button */

        /** First extra button (e.g. wheel left) */
        X1 = SDL_BUTTON_X1,

        /** Second extra button (e.g. wheel right) */
        X2 = SDL_BUTTON_X2,
    };

    /** Button */
    Button GetButton() const { return button; }

    /** Position */
    Vector2i GetPosition() const { return position; }

    /** Click count */
    int32_t GetClickCount() const { return clickCount; }

    /**
     * Modifiers
     * Lazily populated on first request. */
    Modifiers GetModifiers();

private:
    explicit MouseEvent(const SDL_Event& event,
                        Button button,
                        const Vector2i& position,
                        int32_t clickCount)
                        : InputEvent  { event },
                          button      { button },
                          position    { position },
                          clickCount  { clickCount } { }

    const Button button;
    const Vector2i position;
    const int32_t clickCount;
    Containers::Optional<Modifiers> modifiers;
};

/** Mouse move GetEvent */
class MouseMoveEvent : public InputEvent {
    friend InputModule;
public:

    /** Mouse button */
    enum class Button: Uint32 {
        Left    = SDL_BUTTON_LMASK,        /**< Left button */
        Middle  = SDL_BUTTON_MMASK,      /**< Middle button */
        Right   = SDL_BUTTON_RMASK,       /**< Right button */

        /** First extra button (e.g. wheel left) */
        X1 = SDL_BUTTON_X1MASK,

        /** Second extra button (e.g. wheel right) */
        X2 = SDL_BUTTON_X2MASK
    };

    /** Set of mouse GetButtons */
    typedef Containers::EnumSet<Button> Buttons;

    /** Position */
    Vector2i GetPosition() const { return position; }

    /**
     * Relative Position of MouseEvent
     * @note: Position relative to previous move GetEvent.
     */
    Vector2i GetRelativePosition() const { return relativePosition; }

    /** Mouse GetButtons */
    Buttons GetButtons() const { return buttons; }

    /**
     * Returns Modifiers of MouseEvent
     * @note: Lazily populated on first request. */
    Modifiers GetModifiers();

private:
    explicit MouseMoveEvent(const SDL_Event& event,
                            const Vector2i& position,
                            const Vector2i& relativePosition,
                            Buttons buttons)
                            : InputEvent       { event },
                              position         { position },
                              relativePosition { relativePosition },
                              buttons          { buttons } { }

    const Vector2i position;
    const Vector2i relativePosition;
    const Buttons buttons;
    Containers::Optional<Modifiers> modifiers;
};

/** Mouse scroll GetEvent */
class MouseScrollEvent : public InputEvent {
    friend InputModule;
public:

    /** Scroll offset */
    Vector2 GetOffset() const { return offset; }

    /**
     * @retunrs Position of MouseScrollEvent
     * @note Lazily populated on first request.
     */
    Vector2i GetPosition();

    /**
     * @returns Modifiers of MouseScrollEvent
     * @note Lazily populated on first request.
     */
    Modifiers GetModifiers();

private:
    explicit MouseScrollEvent(const SDL_Event& event,
                              const Vector2& offset)
                              : InputEvent { event },
                                offset { offset } { }

    const Vector2 offset;
    Containers::Optional<Vector2i> position;
    Containers::Optional<Modifiers> modifiers;
};

} // namespace core

#endif //CORE_MOUSEEVENT_H
