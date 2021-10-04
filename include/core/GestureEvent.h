/*
 * This is a stand-alone header file. No GestureEvent.cpp is presented
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
#ifndef CORE_GESTUREEVENT_H
#define CORE_GESTUREEVENT_H

#include "InputEvent.h"

namespace core {

/** Multi gesture GetEvent */
class MultiGestureEvent {
    friend InputModule;
public:
    /** Copying is not allowed */
    MultiGestureEvent(const MultiGestureEvent&) = delete;

    /** Moving is not allowed */
    MultiGestureEvent(MultiGestureEvent&&) = delete;

    /** Copying is not allowed */
    MultiGestureEvent& operator=(const MultiGestureEvent&) = delete;

    /** Moving is not allowed */
    MultiGestureEvent& operator=(MultiGestureEvent&&) = delete;

    /** Gesture center */
    Vector2 GetGestureCenter() const { return gestureCenter; }

    /**
     * Rotation relative to previous GetEvent.
     */
    float GetRelativeRotation() const { return relativeRotation; }

    /**
     * Distance of the fingers relative to previous GetEvent.
     */
    float GetRelativeDistance() const { return relativeDistance; }

    /**
     * Count of fingers performing the gesture.
     */
    int32_t GetFingerCount() const { return fingerCount; }

    /**
     * Underlying SDL GetEvent of type SDL_MULTIGESTURE.
     */
    const SDL_Event& GetEvent() const { return event; }

private:
    explicit MultiGestureEvent(const SDL_Event& event,
                               const Vector2& center,
                               float relativeRotation,
                               float relativeDistance,
                               int32_t fingerCount)
                               : event(event),
                                 relativeRotation { relativeRotation },
                                 relativeDistance { relativeDistance },
                                 fingerCount      { fingerCount },
                                 gestureCenter    { center } { }

    const SDL_Event& event;
    const float relativeRotation;
    const float relativeDistance;
    const int32_t fingerCount;
    const Vector2 gestureCenter;
};

}

#endif //CORE_GESTUREEVENT_H
