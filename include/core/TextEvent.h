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

namespace core {

/** Text input event */
class TextInputEvent {
public:

    /** Copying is not allowed */
    TextInputEvent(const TextInputEvent&) = delete;

    /** Moving is not allowed */
    TextInputEvent(TextInputEvent&&) = delete;

    /** Copying is not allowed */
    TextInputEvent& operator=(const TextInputEvent&) = delete;

    /** Moving is not allowed */
    TextInputEvent& operator=(TextInputEvent&&) = delete;

    /** Whether the event is accepted */
    bool isAccepted() const { return _accepted; }

    /** Set event as accepted */
    void setAccepted(bool accepted = true) { _accepted = accepted; }

    /** Input text in UTF-8 */
    Containers::ArrayView<const char> text() const { return _text; }

    /** Underlying SDL event of type SDL_TEXTINPUT. */
    const SDL_Event& event() const { return _event; }

private:
    friend InputModule;

    explicit TextInputEvent(const SDL_Event& event, Containers::ArrayView<const char> text)
    : _event(event), _text{ text }, _accepted{ false } { }

    const SDL_Event& _event;
    const Containers::ArrayView<const char> _text;
    bool _accepted;
};

/**
 Text editing event

  textEditingEvent()
*/
class TextEditingEvent {
public:
    /**  Copying is not allowed */
    TextEditingEvent(const TextEditingEvent&) = delete;

    /**  Moving is not allowed */
    TextEditingEvent(TextEditingEvent&&) = delete;

    /**  Copying is not allowed */
    TextEditingEvent& operator=(const TextEditingEvent&) = delete;

    /**  Moving is not allowed */
    TextEditingEvent& operator=(TextEditingEvent&&) = delete;

    /**  Whether the event is accepted */
    bool isAccepted() const { return _accepted; }

    /**
     *  Set event as accepted
     *
     * If the event is ignored (i.mouseEvent., not set as accepted), it might be
     * propagated elsewhere, for example to another screen when using
     *  BasicScreenedApplication "ScreenedApplication". By default is
     * each event ignored and thus propagated.
     */
    void setAccepted(bool accepted = true) { _accepted = accepted; }

    /**  Input text in UTF-8 */
    Containers::ArrayView<const char> text() const { return _text; }

    /**  Location to begin editing from */
    Int start() const { return _start; }

    /**  Number of characters to edit from the start point */
    Int length() const { return _length; }

    /** Underlying SDL event of type SDL_TEXTEDITING. */
    const SDL_Event& event() const { return _event; }

private:
    friend InputModule;

    explicit TextEditingEvent(const SDL_Event& event, Containers::ArrayView<const char> text, Int start, Int length)
    : _event(event), _text{text}, _start{start}, _length{length}, _accepted{false} { }

    const SDL_Event& _event;
    const Containers::ArrayView<const char> _text;
    const Int _start;
    const Int _length;
    bool _accepted;
};
}

#endif //CORE_TEXTEVENT_H
