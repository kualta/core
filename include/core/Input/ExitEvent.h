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
#ifndef CORE_EXITEVENT_H
#define CORE_EXITEVENT_H

#include "core/Essentials.h"

namespace core {

/** Exit GetEvent */
class ExitEvent {
    friend class InputModule;
public:
    /**  Copying is not allowed */
    ExitEvent(const ExitEvent&) = delete;

    /**  Moving is not allowed */
    ExitEvent(ExitEvent&&) = delete;

    /**  Copying is not allowed */
    ExitEvent& operator=(const ExitEvent&) = delete;

    /**  Moving is not allowed */
    ExitEvent& operator=(ExitEvent&&) = delete;

    /** Underlying SDL GetEvent Of type SDL_QUIT. */
    const SDL_Event& GetEvent() const { return event; }

private:
    explicit ExitEvent(const SDL_Event& event) : event(event) { }

    const SDL_Event& event;
};

}

#endif //CORE_EXITEVENT_H
