/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018, 2019,
                2020, 2021 Vladimír Vondruš <mosra@centrum.cz>
    Copyright © 2018 ShaddyAQN <ShaddyAQN@gmail.com>
    Copyright © 2018 Tomáš Skřivan <skrivantomas@seznam.cz>
    Copyright © 2018 Jonathan Hale <squareys@googlemail.com>

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
#ifndef CORE_GUICONTEXT_H
#define CORE_GUICONTEXT_H

#include "Essentials.h"
#include "Math.h"

#include <Magnum/Timeline.h>
#include <Magnum/GL/AbstractShaderProgram.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/Shaders/FlatGL.h>

#include <imgui.h>
#include <Magnum/GL/Buffer.h>
#include <Magnum/Shaders/FlatGL.h>

namespace core {

class GUIContext {
public:

    /**
     * @param size                  Size of the user interface to which all widgets are positioned
     * @param windowSize            Size of the window to which all input events are related
     * @param framebufferSize       Size of the window framebuffer. On some platforms with HiDPI screens may be
     *                              different from window size.
     *
     * This function creates the ImGui context using ImGui::CreateGUIContext() and then queries the font glyph cache from
     * ImGui, uploading it to the GPU. If you need to do some extra work on the context and before the font texture
     * gets uploaded, use GUIContext(ImGuiGUIContext&, const Vector2&, const Vector2i&, const Vector2i&) instead. */
    explicit GUIContext(const Vector2& size, const Vector2i& windowSize, const Vector2i& framebufferSize);

    /**
     * Construct without DPI awareness
     * Equivalent to calling GUIContext(const Vector2&, const Vector2i&, const Vector2i&) with size passed to all three
     * parameters. */
    explicit GUIContext(const Vector2i& size);

    /**
     * Construct without creating the underlying ImGui context
     *
     * This constructor also doesn't create any internal OpenGL objects, meaning it can be used without an active
     * OpenGL context. Calling any APIs that interact with ImGui on such instance is not allowed. Move a non-empty
     * instance over to make it useful. */
    explicit GUIContext(NoCreateT) noexcept;

    /**
     * Construct from an existing context
     * @param context          Existing ImGui context
     * @param size             Size of the user interface to which all widgets are positioned
     * @param windowSize       Size of the window to which all inputs events are related
     * @param framebufferSize  Size of the window framebuffer. On some platforms with HiDPI
     *                         screens may be different from window size.
     *
     * Expects that no instance is created yet; takes ownership of the passed context, deleting it on destruction.
     * In comparison to GUIContext(const Vector2&, const Vector2i&, const Vector2i&) this constructor is useful if you
     * need to do some work before the font glyph cache gets uploaded to the GPU, for example adding custom fonts. */
    explicit GUIContext(ImGuiContext& context,
                     const Vector2& size,
                     const Vector2i& windowSize,
                     const Vector2i& framebufferSize);

    /**
     * Construct from an existing context without DPI awareness
     *
     * Equivalent to calling GUIContext(ImGuiGUIContext&, const Vector2&, const Vector2i&, const Vector2i&) with size passed
     * to the last three parameters. */
    explicit GUIContext(ImGuiContext& context, const Vector2i& size);

    /** Copying is not allowed */
    GUIContext(const GUIContext&) = delete;

    /** Move constructor */
    GUIContext(GUIContext&& other) noexcept;

    /**
     * If context() is not nullptr, makes it current using ImGui::SetGUIContextCurent()
     * and then calls ImGui::DeleteGUIContext(). */
    ~GUIContext();

    /** Copying is not allowed */
    GUIContext& operator=(const GUIContext&) = delete;

    /** Move assignment */
    GUIContext& operator=(GUIContext&& other) noexcept;

    /** Underlying ImGui context */
    ImGuiContext* getcontext() { return context; }

    /**
     * Release the underlying ImGui context
     *
     * Returns the underlying ImGui context and sets the internal context pointer to nullptr, making the instance
     * equivalent to a moved-out state. Calling APIs that interact with ImGui is not allowed on the instance anymore. */
    ImGuiContext* Release();

    /** Font texture used in `ImFontAtlas` */
    GL::Texture2D& AtlasTexture() { return texture; }

    /**
     * Relayout the context
     *
     * Calls ImGui::SetGUIContextCurent() on context() and adapts the internal state for a new window size or pixel
     * density. In case the pixel density gets changed, font glyph caches are rebuilt to match the new pixel density. */
    void Relayout(const Vector2& size, const Vector2i& windowSize, const Vector2i& framebufferSize);

    /**
     * Relayout the context
     *
     * Equivalent to calling Relayout(const Vector2&, const Vector2i&, const Vector2i&)
     * with size passed to all three parameters. */
    void Relayout(const Vector2i& size);

    /**
     * Start a new frame
     *
     * Calls cpp ImGui::SetGUIContextCurent() on context() and initializes a new ImGui frame using ImGui::NewFrame().
     * This function also decides if a text input needs to be enabled */
    void NewFrame();

    /**
     * Draw a frame
     *
     * Calls ImGui::SetGUIContextCurent() on GUIContext(), ImGui::Render() and then draws the frame created by ImGui calls
     * since last call to newFrame() to currently bound framebuffer. */
    void DrawFrame();

    /**
     * Handle mouse press event
     *
     * Calls ImGui::SetGUIContextCurent() on GUIContext() first and then propagates the event to ImGui. Returns true if ImGui
     * wants to capture the mouse (so the event shouldn't be further propagated to the rest of the application),
     * false otherwise. */
    template<class MouseEvent>
    bool HandleMousePressEvent(MouseEvent& event);

    /**
     * Handle mouse release event
     *
     * Calls ImGui::SetGUIContextCurent() on context() first and then propagates the event to ImGui. Returns true if ImGui
     * wants to capture the mouse (so the event shouldn't be further propagated to the rest of the application),
     * false otherwise. */
    template<class MouseEvent> bool
    HandleMouseReleaseEvent(MouseEvent& event);

    /**
     * Handle mouse scroll event
     *
     * Calls ImGui::SetGUIContextCurent() on context() first and then propagates the event to ImGui. Returns true if ImGui
     * wants to capture the mouse (so the event shouldn't be further propagated to the rest of the application),
     * false otherwise. */
    template<class MouseScrollEvent>
    bool HandleMouseScrollEvent(MouseScrollEvent& event);

    /**
     * Handle mouse move event
     *
     * Calls ImGui::SetGUIContextCurent() on context() first and then propagates the event to ImGui. Returns true if ImGui
     * wants to capture the mouse (so the event shouldn't be further propagated to the rest of the application),
     * false otherwise. */
    template<class MouseMoveEvent>
    bool HandleMouseMoveEvent(MouseMoveEvent& event);

    /**
     * Handle key press event
     *
     * Calls ImGui::SetGUIContextCurent() on context() first and then propagates the event to ImGui. Returns true if ImGui
     * wants to capture the keyboard (so the event shouldn't be further propagated to the rest of the application),
     * false otherwise. */
    template<class KeyEvent>
    bool HandleKeyPressEvent(KeyEvent& event);

    /**
     * Handle key release event
     *
     * Calls ImGui::SetGUIContextCurent() on context() first and then propagates the event to ImGui. Returns true if ImGui
     * wants to capture the keyboard (so the event shouldn't be further propagated to the rest of the application),
     * false otherwise. */
    template<class KeyEvent>
    bool HandleKeyReleaseEvent(KeyEvent& event);

    /**
     * Handle text input event
     *
     * Calls ImGui::SetGUIContextCurent() on context() first and then propagates the event to ImGui. Returns true if ImGui
     * wants to capture the keyboard (so the event shouldn't be further propagated to the rest of the application),
     * false otherwise. */
    template<class TextInputEvent>
    bool HandleTextInputEvent(TextInputEvent& event);

    /**
     * Update application mouse cursor
     *
     * Calls ImGui::SetGUIContextCurent() on GUIContext() first and then queries ImGui::GetMouseCursor() */
    template<class Application>
    void UpdateApplicationCursor(Application& application);

private:

    template<class KeyEvent>
    bool HandleKeyEvent(KeyEvent& event, bool value);

    template<class MouseEvent>
    bool HandleMouseEvent(MouseEvent& event, bool value);

    ImGuiContext* context;

    BoolVector3        mousePressed;
    BoolVector3        mousePressedInThisFrame;
    Shaders::FlatGL2D  shader;
    Timeline           timeline;
    Vector2            eventScaling;
    Vector2            supersamplingRatio;
    GL::Mesh           mesh;
    GL::Texture2D      texture      { NoCreate };
    GL::Buffer         vertexBuffer { GL::Buffer::TargetHint::Array };
    GL::Buffer         indexBuffer  { GL::Buffer::TargetHint::ElementArray };

};


} // namespace core

#include "GUIContext.tpp"

#endif //CORE_GUICONTEXT_H
