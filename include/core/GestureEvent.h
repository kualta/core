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
#ifndef CORE_GESTUREEVENT_H
#define CORE_GESTUREEVENT_H

#include "InputEvent.h"

namespace core {

/** Multi gesture event */
class MultiGestureEvent {
public:
    /** Copying is not allowed */
    MultiGestureEvent(const MultiGestureEvent&) = delete;

    /** Moving is not allowed */
    MultiGestureEvent(MultiGestureEvent&&) = delete;

    /** Copying is not allowed */
    MultiGestureEvent& operator=(const MultiGestureEvent&) = delete;

    /** Moving is not allowed */
    MultiGestureEvent& operator=(MultiGestureEvent&&) = delete;

    /** Whether the event is accepted */
    bool isAccepted() const { return _accepted; }

    /** Set event as accepted */
    void setAccepted(bool accepted = true) { _accepted = accepted; }

    /**  Gesture center */
    Vector2 center() const { return _center; }

    /**
     * Relative rotation
     *
     * Rotation relative to previous event.
     */
    Float relativeRotation() const { return _relativeRotation; }

    /**
     * Relative distance
     *
     * Distance of the fingers relative to previous event.
     */
    Float relativeDistance() const { return _relativeDistance; }

    /**
     * Finger count
     *
     * Count of fingers performing the gesture.
     */
    Int fingerCount() const { return _fingerCount; }

    /**
     * Underlying SDL event of type SDL_MULTIGESTURE.
     */
    const SDL_Event& event() const { return _event; }

private:
    friend Sdl2Application;

    explicit MultiGestureEvent(const SDL_Event& event,
                               const Vector2& center,
                               Float relativeRotation,
                               Float relativeDistance,
                               Int fingerCount)
                               : _event(event),
                               _center           { center },
                               _relativeRotation { relativeRotation },
                               _relativeDistance { relativeDistance },
                               _fingerCount      { fingerCount },
                               _accepted         { false } { }

    const SDL_Event& _event;

    const Float _relativeRotation;
    const Float _relativeDistance;
    const Int _fingerCount;
    const Vector2 _center;
    bool _accepted;
};

}

#endif //CORE_GESTUREEVENT_H
