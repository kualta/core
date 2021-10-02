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

/** Mouse event */
class MouseEvent : public InputEvent {
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
    Button button() const { return _button; }

    /** Position */
    Vector2i position() const { return _position; }

    /** Click count */
    Int clickCount() const { return _clickCount; }

    /**
     * Modifiers
     * Lazily populated on first request. */
    Modifiers modifiers();

private:
    friend InputModule;

    explicit MouseEvent(const SDL_Event& event, Button button, const Vector2i& position, Int clickCount )
    : InputEvent { event },
    _button      { button },
    _position    { position },
    _clickCount  { clickCount } { }

    const Button _button;
    const Vector2i _position;
    const Int _clickCount;
    Containers::Optional<Modifiers> _modifiers;
};

/** Mouse move event */
class MouseMoveEvent : public InputEvent {
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

    /** Set of mouse buttons */
    typedef Containers::EnumSet<Button> Buttons;

    /** Position */
    Vector2i position() const { return _position; }

    /**
     * Relative position
     * Position relative to previous move event. */
    Vector2i relativePosition() const { return _relativePosition; }

    /**  Mouse buttons */
    Buttons buttons() const { return _buttons; }

    /**
     * Modifiers
     * Lazily populated on first request. */
    Modifiers modifiers();

private:
    friend InputModule;

    explicit MouseMoveEvent(const SDL_Event& event,
                            const Vector2i& position,
                            const Vector2i& relativePosition,
                            Buttons buttons)
                            : InputEvent        { event },
                              _position         { position },
                              _relativePosition { relativePosition },
                              _buttons          { buttons } { }

    const Vector2i _position;
    const Vector2i _relativePosition;
    const Buttons _buttons;
    Containers::Optional<Modifiers> _modifiers;
};

/** Mouse scroll event */
class MouseScrollEvent : public InputEvent {
public:

    /** Scroll offset */
    Vector2 offset() const { return _offset; }

    /**
     * Position
     * Lazily populated on first request. */
    Vector2i position();

    /**
     * Modifiers
     * Lazily populated on first request. */
    Modifiers modifiers();

private:
    friend InputModule;

    explicit MouseScrollEvent(const SDL_Event& event, const Vector2& offset)
    : InputEvent { event }, _offset { offset } { }

    const Vector2 _offset;
    Containers::Optional<Vector2i> _position;
    Containers::Optional<Modifiers> _modifiers;
};

} // namespace core

#endif //CORE_MOUSEEVENT_H
