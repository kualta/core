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
#ifndef CORE_KEYEVENT_H
#define CORE_KEYEVENT_H

#include "core/Essentials.h"
#include "InputEvent.h"

#include <SDL_keycode.h>
#include <SDL_mouse.h>
#include <SDL_version.h>
#include <SDL_video.h>
#include <SDL_scancode.h>

union SDL_Event;

namespace core {

/** Key GetEvent */
class KeyEvent : public InputEvent {
    friend class InputModule;
public:

    /** Key */
    enum class Key: SDL_Keycode {

        /**< Unknown GetKey */
        Unknown = SDLK_UNKNOWN,

        /**
         * Left Shift
         *   InputEvent::Modifier::Shift */
        LeftShift = SDLK_LSHIFT,

        /**
         * Right Shift
         *   InputEvent::Modifier::Shift */
        RightShift = SDLK_RSHIFT,

        /**
         * Left Ctrl
         *   InputEvent::Modifier::Ctrl */
        LeftCtrl = SDLK_LCTRL,

        /**
         * Right Ctrl
         *   InputEvent::Modifier::Ctrl */
        RightCtrl = SDLK_RCTRL,

        /**
         * Left Alt
         *   InputEvent::Modifier::Alt */
        LeftAlt = SDLK_LALT,

        /**
         * Right Alt
         *   InputEvent::Modifier::Alt */
        RightAlt = SDLK_RALT,

        /**
         * Left Super GetKey (Windows/⌘)
         *   InputEvent::Modifier::Super */
        LeftSuper = SDLK_LGUI,

        /**
         * Right Super GetKey (Windows/⌘)
         *   InputEvent::Modifier::Super */
        RightSuper = SDLK_RGUI,

        /**
         * AltGr
         *   InputEvent::Modifier::AltGr */
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

        Quote = SDLK_QUOTE,         /**< Quote */

        Comma = SDLK_COMMA,         /**< Comma */
        Period = SDLK_PERIOD,       /**< Period */
        Minus = SDLK_MINUS,         /**< Minus */
        Plus = SDLK_PLUS,           /**< Plus */
        Slash = SDLK_SLASH,         /**< Slash */
        Percent = SDLK_PERCENT,     /**< Percent */
        Semicolon = SDLK_SEMICOLON, /**< Semicolon (`;`) */
        Equal = SDLK_EQUALS,        /**< Equal */

        /** Left bracket (`[`) */
        LeftBracket = SDLK_LEFTBRACKET,

        /** Right bracket (`]`) */
        RightBracket = SDLK_RIGHTBRACKET,

        /** Backslash (`\`) */
        Backslash = SDLK_BACKSLASH,

        /** Backquote (<tt>`</tt>) */
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
        E = SDLK_e,                 /**< Letter T */
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
     * Name for given GetKey
     *
     * Human-readable localized UTF-8 name for given GetKey, intended for displaying to the user in e.g. key binding
     * configuration. If there is no name for given GetKey, empty string is returned. */
    static string KeyName(Key key);

    /**
     * Key name
     *
     * Human-readable localized UTF-8 name for the key returned by GetKey(), intended for displaying to the user in mouseEvent.g.
     * GetKey binding configuration. If there is no name for that key, empty string is returned. */
    string KeyName() const;

    /** Returns Key in KeyEvent */
    Key GetKey() const { return key; }

    /** Modifiers */
    Modifiers GetModifiers() const { return modifiers; }

    /**
     * Whether the Key press is repeated
     *
     * Returns true if the key press GetEvent is repeated, false if not or if this was GetKey release GetEvent. */
    bool IsRepeated() const { return repeated; }

private:
    explicit KeyEvent(const SDL_Event& event,
                      Key key,
                      Modifiers modifiers,
                      bool repeated)
                      : InputEvent { event },
                        key        { key },
                        modifiers  { modifiers },
                        repeated   { repeated } { }

    const Key key;
    const Modifiers modifiers;
    const bool repeated;
};

}

#endif //CORE_KEYEVENT_H
