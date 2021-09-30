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
#ifndef CORE_EVENT_H
#define CORE_EVENT_H

#include "Essentials.h"

namespace core {




/**
 Key event

  keyPressEvent(),  keyReleaseEvent()
*/
class Sdl2Application::KeyEvent: public Sdl2Application::InputEvent {
public:
    /**
     *  Key
     *
     *   key()
     */
    enum class Key: SDL_Keycode {
        Unknown = SDLK_UNKNOWN,     /**< Unknown key */

        /**
         * Left Shift
         *
         *   InputEvent::Modifier::Shift
         */
        LeftShift = SDLK_LSHIFT,

        /**
         * Right Shift
         *
         *   InputEvent::Modifier::Shift
         */
        RightShift = SDLK_RSHIFT,

        /**
         * Left Ctrl
         *
         *   InputEvent::Modifier::Ctrl
         */
        LeftCtrl = SDLK_LCTRL,

        /**
         * Right Ctrl
         *
         *   InputEvent::Modifier::Ctrl
         */
        RightCtrl = SDLK_RCTRL,

        /**
         * Left Alt
         *
         *   InputEvent::Modifier::Alt
         */
        LeftAlt = SDLK_LALT,

        /**
         * Right Alt
         *
         *   InputEvent::Modifier::Alt
         */
        RightAlt = SDLK_RALT,

        /**
         * Left Super key (Windows/⌘)
         *
         *   InputEvent::Modifier::Super
         */
        LeftSuper = SDLK_LGUI,

        /**
         * Right Super key (Windows/⌘)
         *
         *   InputEvent::Modifier::Super
         */
        RightSuper = SDLK_RGUI,

        /**
         * AltGr
         *
         *   InputEvent::Modifier::AltGr
         */
        AltGr = SDLK_MODE,

        Enter = SDLK_RETURN,        /**< Enter */
        Esc = SDLK_ESCAPE,          /**< Escape */

        Up = SDLK_UP,               /**< Up arrow */
        Down = SDLK_DOWN,           /**< Down arrow */
        Left = SDLK_LEFT,           /**< Left arrow */
        Right = SDLK_RIGHT,         /**< Right arrow */
        Home = SDLK_HOME,           /**< Home */
        End = SDLK_END,             /**< End */
        PageUp = SDLK_PAGEUP,       /**< Page up */
        PageDown = SDLK_PAGEDOWN,   /**< Page down */
        Backspace = SDLK_BACKSPACE, /**< Backspace */
        Insert = SDLK_INSERT,       /**< Insert */
        Delete = SDLK_DELETE,       /**< Delete */

        F1 = SDLK_F1,               /**< F1 */
        F2 = SDLK_F2,               /**< F2 */
        F3 = SDLK_F3,               /**< F3 */
        F4 = SDLK_F4,               /**< F4 */
        F5 = SDLK_F5,               /**< F5 */
        F6 = SDLK_F6,               /**< F6 */
        F7 = SDLK_F7,               /**< F7 */
        F8 = SDLK_F8,               /**< F8 */
        F9 = SDLK_F9,               /**< F9 */
        F10 = SDLK_F10,             /**< F10 */
        F11 = SDLK_F11,             /**< F11 */
        F12 = SDLK_F12,             /**< F12 */

        Space = SDLK_SPACE,         /**< Space */
        Tab = SDLK_TAB,             /**< Tab */

        /**
         * Quote (<tt>'</tt>)
         * @m_since{2020,06}
         */
        Quote = SDLK_QUOTE,

        Comma = SDLK_COMMA,         /**< Comma */
        Period = SDLK_PERIOD,       /**< Period */
        Minus = SDLK_MINUS,         /**< Minus */
        Plus = SDLK_PLUS,           /**< Plus */
        Slash = SDLK_SLASH,         /**< Slash */
        Percent = SDLK_PERCENT,     /**< Percent */
        Semicolon = SDLK_SEMICOLON, /**< Semicolon (`;`) */
        Equal = SDLK_EQUALS,        /**< Equal */

        /**
         * Left bracket (`[`)
         * @m_since{2020,06}
         */
        LeftBracket = SDLK_LEFTBRACKET,

        /**
         * Right bracket (`]`)
         * @m_since{2020,06}
         */
        RightBracket = SDLK_RIGHTBRACKET,

        /**
         * Backslash (`\`)
         * @m_since{2020,06}
         */
        Backslash = SDLK_BACKSLASH,

        /**
         * Backquote (<tt>`</tt>)
         * @m_since{2020,06}
         */
        Backquote = SDLK_BACKQUOTE,

        /* no equivalent for GlfwApplication's World1 / World2 */

        Zero = SDLK_0,              /**< Zero */
        One = SDLK_1,               /**< One */
        Two = SDLK_2,               /**< Two */
        Three = SDLK_3,             /**< Three */
        Four = SDLK_4,              /**< Four */
        Five = SDLK_5,              /**< Five */
        Six = SDLK_6,               /**< Six */
        Seven = SDLK_7,             /**< Seven */
        Eight = SDLK_8,             /**< Eight */
        Nine = SDLK_9,              /**< Nine */

        A = SDLK_a,                 /**< Letter A */
        B = SDLK_b,                 /**< Letter B */
        C = SDLK_c,                 /**< Letter C */
        D = SDLK_d,                 /**< Letter D */
        E = SDLK_e,                 /**< Letter E */
        F = SDLK_f,                 /**< Letter F */
        G = SDLK_g,                 /**< Letter G */
        H = SDLK_h,                 /**< Letter H */
        I = SDLK_i,                 /**< Letter I */
        J = SDLK_j,                 /**< Letter J */
        K = SDLK_k,                 /**< Letter K */
        L = SDLK_l,                 /**< Letter L */
        M = SDLK_m,                 /**< Letter M */
        N = SDLK_n,                 /**< Letter N */
        O = SDLK_o,                 /**< Letter O */
        P = SDLK_p,                 /**< Letter P */
        Q = SDLK_q,                 /**< Letter Q */
        R = SDLK_r,                 /**< Letter R */
        S = SDLK_s,                 /**< Letter S */
        T = SDLK_t,                 /**< Letter T */
        U = SDLK_u,                 /**< Letter U */
        V = SDLK_v,                 /**< Letter V */
        W = SDLK_w,                 /**< Letter W */
        X = SDLK_x,                 /**< Letter X */
        Y = SDLK_y,                 /**< Letter Y */
        Z = SDLK_z,                 /**< Letter Z */

        NumZero = SDLK_KP_0,            /**< Numpad zero */
        NumOne = SDLK_KP_1,             /**< Numpad one */
        NumTwo = SDLK_KP_2,             /**< Numpad two */
        NumThree = SDLK_KP_3,           /**< Numpad three */
        NumFour = SDLK_KP_4,            /**< Numpad four */
        NumFive = SDLK_KP_5,            /**< Numpad five */
        NumSix = SDLK_KP_6,             /**< Numpad six */
        NumSeven = SDLK_KP_7,           /**< Numpad seven */
        NumEight = SDLK_KP_8,           /**< Numpad eight */
        NumNine = SDLK_KP_9,            /**< Numpad nine */
        NumDecimal = SDLK_KP_DECIMAL,   /**< Numpad decimal */
        NumDivide = SDLK_KP_DIVIDE,     /**< Numpad divide */
        NumMultiply = SDLK_KP_MULTIPLY, /**< Numpad multiply */
        NumSubtract = SDLK_KP_MINUS,    /**< Numpad subtract */
        NumAdd = SDLK_KP_PLUS,          /**< Numpad add */
        NumEnter = SDLK_KP_ENTER,       /**< Numpad enter */
        NumEqual = SDLK_KP_EQUALS       /**< Numpad equal */
    };

    /**
     *  Name for given key
     *
     * Human-readable localized UTF-8 name for given @p key, intended for
     * displaying to the user in e.g. key binding configuration. If there
     * is no name for given key, empty string is returned.
     *   keyName(Key)
     */
    static std::string keyName(Key key);

    /**
     *  Key
     *
     *   keyName()
     */
    Key key() const { return _key; }

    /**
     *  Key name
     *
     * Human-readable localized UTF-8 name for the key returned by
     *  key(), intended for displaying to the user in e.g.
     * key binding configuration. If there is no name for that key, empty
     * string is returned.
     *   keyName(Key)
     */
    std::string keyName() const;

    /**  Modifiers */
    Modifiers modifiers() const { return _modifiers; }

    /**
     *  Whether the key press is repeated
     *
     * Returns @cpp true @ce if the key press event is repeated,
     * @cpp false @ce if not or if this was key release event.
     */
    bool isRepeated() const { return _repeated; }

private:
    friend Sdl2Application;

    explicit KeyEvent(const SDL_Event& event, Key key, Modifiers modifiers, bool repeated): InputEvent{event}, _key{key}, _modifiers{modifiers}, _repeated{repeated} {}

    const Key _key;
    const Modifiers _modifiers;
    const bool _repeated;
};

/**
 Mouse event

  MouseMoveEvent,  MouseScrollEvent,  mousePressEvent(),
     mouseReleaseEvent()
*/
class Sdl2Application::MouseEvent: public Sdl2Application::InputEvent {
public:
    /**
     *  Mouse button
     *
     *   button()
     */
    enum class Button: Uint8 {
        Left = SDL_BUTTON_LEFT,         /**< Left button */
        Middle = SDL_BUTTON_MIDDLE,     /**< Middle button */
        Right = SDL_BUTTON_RIGHT,       /**< Right button */

        /** First extra button (e.g. wheel left) */
        X1 = SDL_BUTTON_X1,

        /** Second extra button (e.g. wheel right) */
        X2 = SDL_BUTTON_X2,
    };

    /**  Button */
    Button button() const { return _button; }

    /**  Position */
    Vector2i position() const { return _position; }

#ifndef CORRADE_TARGET_EMSCRIPTEN
    /**
     *  Click count
     *
     * @note Not available in  CORRADE_TARGET_EMSCRIPTEN "Emscripten".
     */
    Int clickCount() const { return _clickCount; }
#endif

    /**
     *  Modifiers
     *
     * Lazily populated on first request.
     */
    Modifiers modifiers();

private:
    friend Sdl2Application;

    explicit MouseEvent(const SDL_Event& event, Button button, const Vector2i& position
#ifndef CORRADE_TARGET_EMSCRIPTEN
            , Int clickCount
#endif
    ): InputEvent{event}, _button{button}, _position{position}
#ifndef CORRADE_TARGET_EMSCRIPTEN
            , _clickCount{clickCount}
#endif
    {}

    const Button _button;
    const Vector2i _position;
#ifndef CORRADE_TARGET_EMSCRIPTEN
    const Int _clickCount;
#endif
    Containers::Optional<Modifiers> _modifiers;
};

/**
 Mouse move event

  MouseEvent,  MouseScrollEvent,  mouseMoveEvent()
*/
class Sdl2Application::MouseMoveEvent: public Sdl2Application::InputEvent {
public:
    /**
     *  Mouse button
     *
     *   Buttons,  buttons()
     */
    enum class Button: Uint32 {
        Left = SDL_BUTTON_LMASK,        /**< Left button */
        Middle = SDL_BUTTON_MMASK,      /**< Middle button */
        Right = SDL_BUTTON_RMASK,       /**< Right button */

        /** First extra button (e.g. wheel left) */
        X1 = SDL_BUTTON_X1MASK,

        /** Second extra button (e.g. wheel right) */
        X2 = SDL_BUTTON_X2MASK
    };

    /**
     *  Set of mouse buttons
     *
     *   buttons()
     */
    typedef Containers::EnumSet<Button> Buttons;

    /**  Position */
    Vector2i position() const { return _position; }

    /**
     *  Relative position
     *
     * Position relative to previous move event.
     */
    Vector2i relativePosition() const { return _relativePosition; }

    /**  Mouse buttons */
    Buttons buttons() const { return _buttons; }

    /**
     *  Modifiers
     *
     * Lazily populated on first request.
     */
    Modifiers modifiers();

private:
    friend Sdl2Application;

    explicit MouseMoveEvent(const SDL_Event& event, const Vector2i& position, const Vector2i& relativePosition, Buttons buttons): InputEvent{event}, _position{position}, _relativePosition{relativePosition}, _buttons{buttons} {}

    const Vector2i _position, _relativePosition;
    const Buttons _buttons;
    Containers::Optional<Modifiers> _modifiers;
};

/**
 Mouse scroll event

  MouseEvent,  MouseMoveEvent,  mouseScrollEvent()
*/
class Sdl2Application::MouseScrollEvent: public Sdl2Application::InputEvent {
public:
    /**  Scroll offset */
    Vector2 offset() const { return _offset; }

    /**
     *  Position
     *
     * Lazily populated on first request.
     */
    Vector2i position();

    /**
     *  Modifiers
     *
     * Lazily populated on first request.
     */
    Modifiers modifiers();

private:
    friend Sdl2Application;

    explicit MouseScrollEvent(const SDL_Event& event, const Vector2& offset): InputEvent{event}, _offset{offset} {}

    const Vector2 _offset;
    Containers::Optional<Vector2i> _position;
    Containers::Optional<Modifiers> _modifiers;
};

/**
 Multi gesture event

@experimental
  multiGestureEvent()
*/
class Sdl2Application::MultiGestureEvent {
public:
    /**  Copying is not allowed */
    MultiGestureEvent(const MultiGestureEvent&) = delete;

    /**  Moving is not allowed */
    MultiGestureEvent(MultiGestureEvent&&) = delete;

    /**  Copying is not allowed */
    MultiGestureEvent& operator=(const MultiGestureEvent&) = delete;

    /**  Moving is not allowed */
    MultiGestureEvent& operator=(MultiGestureEvent&&) = delete;

    /**  Whether the event is accepted */
    bool isAccepted() const { return _accepted; }

    /**
     *  Set event as accepted
     *
     * If the event is ignored (i.e., not set as accepted), it might be
     * propagated elsewhere, for example to another screen when using
     *  BasicScreenedApplication "ScreenedApplication". By default is
     * each event ignored and thus propagated.
     */
    void setAccepted(bool accepted = true) { _accepted = accepted; }

    /**  Gesture center */
    Vector2 center() const { return _center; }

    /**
     *  Relative rotation
     *
     * Rotation relative to previous event.
     */
    Float relativeRotation() const { return _relativeRotation; }

    /**
     *  Relative distance
     *
     * Distance of the fingers relative to previous event.
     */
    Float relativeDistance() const { return _relativeDistance; }

    /**
     *  Finger count
     *
     * Count of fingers performing the gesture.
     */
    Int fingerCount() const { return _fingerCount; }

    /**
     *  Underlying SDL event
     *
     * Of type `SDL_MULTIGESTURE`.
     *   Sdl2Application::anyEvent()
     */
    const SDL_Event& event() const { return _event; }

private:
    friend Sdl2Application;

    explicit MultiGestureEvent(const SDL_Event& event, const Vector2& center, Float relativeRotation, Float relativeDistance, Int fingerCount): _event(event), _center{center}, _relativeRotation{relativeRotation}, _relativeDistance{relativeDistance}, _fingerCount{fingerCount}, _accepted{false} {}

    const SDL_Event& _event;
    const Vector2 _center;
    const Float _relativeRotation;
    const Float _relativeDistance;
    const Int _fingerCount;
    bool _accepted;
};

/**
 Text input event

  TextEditingEvent,  textInputEvent()
*/
class Sdl2Application::TextInputEvent {
public:
    /**  Copying is not allowed */
    TextInputEvent(const TextInputEvent&) = delete;

    /**  Moving is not allowed */
    TextInputEvent(TextInputEvent&&) = delete;

    /**  Copying is not allowed */
    TextInputEvent& operator=(const TextInputEvent&) = delete;

    /**  Moving is not allowed */
    TextInputEvent& operator=(TextInputEvent&&) = delete;

    /**  Whether the event is accepted */
    bool isAccepted() const { return _accepted; }

    /**
     *  Set event as accepted
     *
     * If the event is ignored (i.e., not set as accepted), it might be
     * propagated elsewhere, for example to another screen when using
     *  BasicScreenedApplication "ScreenedApplication". By default is
     * each event ignored and thus propagated.
     */
    void setAccepted(bool accepted = true) { _accepted = accepted; }

    /**  Input text in UTF-8 */
    Containers::ArrayView<const char> text() const { return _text; }

    /**
     *  Underlying SDL event
     *
     * Of type `SDL_TEXTINPUT`.
     *   Sdl2Application::anyEvent()
     */
    const SDL_Event& event() const { return _event; }

private:
    friend Sdl2Application;

    explicit TextInputEvent(const SDL_Event& event, Containers::ArrayView<const char> text): _event(event), _text{text}, _accepted{false} {}

    const SDL_Event& _event;
    const Containers::ArrayView<const char> _text;
    bool _accepted;
};

/**
 Text editing event

  textEditingEvent()
*/
class Sdl2Application::TextEditingEvent {
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
     * If the event is ignored (i.e., not set as accepted), it might be
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

    /**
     *  Underlying SDL event
     *
     * Of type `SDL_TEXTEDITING`.
     *   Sdl2Application::anyEvent()
     */
    const SDL_Event& event() const { return _event; }

private:
    friend Sdl2Application;

    explicit TextEditingEvent(const SDL_Event& event, Containers::ArrayView<const char> text, Int start, Int length): _event(event), _text{text}, _start{start}, _length{length}, _accepted{false} {}

    const SDL_Event& _event;
    const Containers::ArrayView<const char> _text;
    const Int _start;
    const Int _length;
    bool _accepted;
};

}

#endif //CORE_EVENT_H
