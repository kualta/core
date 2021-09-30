/*
 * This is a stand-alone header file. No InputEvent.cpp is presented.
 */
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
                2020, 2021 Vladimír Vondruš <mosrantrum.cz>
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
#ifndef CORE_INPUTEVENT_H
#define CORE_INPUTEVENT_H

namespace core {

/**
 * Base for input events
 */
class InputEvent {
public:

    /** Modifier */
    enum class Modifier: Uint16 {
        /**
         * Shift
         *   KeyEvent::Key::LeftShift,  KeyEvent::Key::RightShift */
        Shift = KMOD_SHIFT,

        /**
         * Ctrl
         *   KeyEvent::Key::LeftCtrl,  KeyEvent::Key::RightCtrl */
        Ctrl = KMOD_CTRL,

        /**
         * Alt
         *   KeyEvent::Key::LeftAlt,  KeyEvent::Key::RightAlt */
        Alt = KMOD_ALT,

        /**
         * Super key (Windows/⌘)
         *   KeyEvent::Key::LeftSuper,  KeyEvent::Key::RightSuper */
        Super = KMOD_GUI,

        /**
         * AltGr
         *   KeyEvent::Key::AltGr */
        AltGr = KMOD_MODE,

        /**
         * Caps lock
         * */
        CapsLock = KMOD_CAPS,

        /**
         * Num lock */
        NumLock = KMOD_NUM
    };

    /**
     *  Set of modifiers
     *   KeyEvent::modifiers(),  MouseEvent::modifiers(), MouseMoveEvent::modifiers() */
    typedef Containers::EnumSet<Modifier> Modifiers;

    /**  Copying is not allowed */
    InputEvent(const InputEvent&) = delete;

    /**  Moving is not allowed */
    InputEvent(InputEvent&&) = delete;

    /**  Copying is not allowed */
    InputEvent& operator=(const InputEvent&) = delete;

    /**  Moving is not allowed */
    InputEvent& operator=(InputEvent&&) = delete;

    /**  Whether the event is accepted */
    bool IsAccepted() const { return accepted; }

    /**
     * Set event as accepted
     * If the event is ignored (i.e., not set as accepted), it might be propagated elsewhere */
    void SetAccepted(bool eventAccepted = true) { accepted = eventAccepted; }

    /**
     *  Underlying SDL event
     *
     * Of type `SDL_KEYDOWN`       / `SDL_KEYUP`           for KeyEvent,
     *         `SDL_MOUSEBUTTONUP` / `SDL_MOUSEBUTTONDOWN` for MouseEvent,
     *         `SDL_MOUSEWHEEL`                            for MouseScrollEvent,
     *         `SDL_MOUSEMOTION`                           for MouseMoveEvent.
     */
    const SDL_Event& GetEvent() const { return event; }

#ifndef DOXYGEN_GENERATING_OUTPUT
protected:
    explicit InputEvent(const SDL_Event& event): event(event), accepted(false) { }

    ~InputEvent() = default;
#endif

private:
    const SDL_Event& event;
    bool accepted;
};

} // namespace core

#endif //CORE_INPUTEVENT_H
