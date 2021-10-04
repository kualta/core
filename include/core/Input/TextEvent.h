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
#ifndef CORE_TEXTEVENT_H
#define CORE_TEXTEVENT_H

#include "InputEvent.h"
#include "core/Event.h"

namespace core {

/** Text input Event */
class TextInputEvent {
    friend InputModule;
public:

    /** Copying is not allowed */
    TextInputEvent(const TextInputEvent&) = delete;

    /** Moving is not allowed */
    TextInputEvent(TextInputEvent&&) = delete;

    /** Copying is not allowed */
    TextInputEvent& operator=(const TextInputEvent&) = delete;

    /** Moving is not allowed */
    TextInputEvent& operator=(TextInputEvent&&) = delete;

    /** Input GetText in UTF-8 */
    Containers::ArrayView<const char> GetText() const { return text; }

    /** Underlying SDL GetEvent of type SDL_TEXTINPUT. */
    const SDL_Event& GetEvent() const { return event; }

private:
    explicit TextInputEvent(const SDL_Event& event,
                            Containers::ArrayView<const char> text)
                            : event(event),
                            text { text } { }

    const SDL_Event& event;
    const Containers::ArrayView<const char> text;
};

/** Text editing Event */
class TextEditingEvent {
    friend InputModule;
public:
    /**  Copying is not allowed */
    TextEditingEvent(const TextEditingEvent&) = delete;

    /**  Moving is not allowed */
    TextEditingEvent(TextEditingEvent&&) = delete;

    /**  Copying is not allowed */
    TextEditingEvent& operator=(const TextEditingEvent&) = delete;

    /**  Moving is not allowed */
    TextEditingEvent& operator=(TextEditingEvent&&) = delete;

    /**  Input text in UTF-8 */
    Containers::ArrayView<const char> GetText() const { return text; }

    /**  Location to begin editing from */
    int32_t GetStartLocation() const { return start; }

    /**  Number of characters to edit from the GetStartLocation point */
    int32_t GetLength() const { return length; }

    /**  Underlying SDL GetEvent of type SDL_TEXTEDITING. */
    const SDL_Event& GetEvent() const { return event; }

private:
    explicit TextEditingEvent(const SDL_Event& event,
                              Containers::ArrayView<const char> text,
                              int32_t start,
                              int32_t length)
                              : event(event),
                                text    { text },
                                start   { start },
                                length  { length } { }

    const SDL_Event& event;
    const Containers::ArrayView<const char> text;
    const int32_t start;
    const int32_t length;
};

} // namespace core

#endif //CORE_TEXTEVENT_H
