#ifndef CORE_GUICONTEXT_H
#define CORE_GUICONTEXT_H

class Context {
public:

    explicit Context(const Vector2& size, const Vector2i& windowSize, const Vector2i& framebufferSize);

    /** Construct without DPI awareness */
    explicit Context(const Vector2i& size);

    /** @brief Copying is not allowed */
    Context(const Context&) = delete;

    /** @brief Move constructor */
    Context(Context&& other) noexcept;

    /**
     * If context() is not nullptr, makes it current using ImGui::SetContextCurent()
     * and then calls ImGui::DeleteContext().
     */
    ~Context();

    /** @brief Copying is not allowed */
    Context& operator=(const Context&) = delete;

    /** @brief Move assignment */
    Context& operator=(Context&& other) noexcept;

    /** Underlying ImGui context */
    ImGuiContext* context() { return _context; }

    /**
     * @brief Release the underlying ImGui context
     *
     * Returns the underlying ImGui context and sets the internal context
     * pointer to @cpp nullptr @ce, making the instance equivalent to a
     * moved-out state. Calling APIs that interact with ImGui is not
     * allowed on the instance anymore.
     */
    ImGuiContext* release();

    /**
     * @brief Font texture used in `ImFontAtlas`
     * @m_since_{integration,2020,06}
     */
    GL::Texture2D& atlasTexture() { return _texture; }

    /**
     * @brief Relayout the context
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context() and
     * adapts the internal state for a new window size or pixel density. In
     * case the pixel density gets changed, font glyph caches are rebuilt
     * to match the new pixel density.
     *
     * The sizes are allowed to be zero in any dimension, but note that it
     * may trigger an unwanted rebuild of the font glyph cache due to
     * different calculated pixel density.
     */
    void relayout(const Vector2& size, const Vector2i& windowSize, const Vector2i& framebufferSize);

    /**
     * @brief Relayout the context
     *
     * Equivalent to calling @ref relayout(const Vector2&, const Vector2i&, const Vector2i&)
     * with @p size passed to all three parameters.
     */
    void relayout(const Vector2i& size);

    /**
     * @brief Start a new frame
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context() and
     * initializes a new ImGui frame using @cpp ImGui::NewFrame() @ce. This
     * function also decides if a text input needs to be enabled, see
     * @ref ImGuiIntegration-Context-usage-text-input for more information.
     */
    void newFrame();

    /**
     * @brief Draw a frame
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context(),
     * @cpp ImGui::Render() @ce and then draws the frame created by ImGui
     * calls since last call to @ref newFrame() to currently bound
     * framebuffer.
     *
     * See @ref ImGuiIntegration-Context-usage-rendering for more
     * information on which rendering states to set before and after
     * calling this method.
     */
    void drawFrame();

    /**
     * @brief Handle mouse press event
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context() first and
     * then propagates the event to ImGui. Returns @cpp true @ce if ImGui
     * wants to capture the mouse (so the event shouldn't be further
     * propagated to the rest of the application), @cpp false @ce
     * otherwise.
     */
    template<class MouseEvent> bool handleMousePressEvent(MouseEvent& event);

    /**
     * @brief Handle mouse release event
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context() first and
     * then propagates the event to ImGui. Returns @cpp true @ce if ImGui
     * wants to capture the mouse (so the event shouldn't be further
     * propagated to the rest of the application), @cpp false @ce
     * otherwise.
     */
    template<class MouseEvent> bool handleMouseReleaseEvent(MouseEvent& event);

    /**
     * @brief Handle mouse scroll event
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context() first and
     * then propagates the event to ImGui. Returns @cpp true @ce if ImGui
     * wants to capture the mouse (so the event shouldn't be further
     * propagated to the rest of the application), @cpp false @ce
     * otherwise.
     */
    template<class MouseScrollEvent> bool handleMouseScrollEvent(MouseScrollEvent& event);

    /**
     * @brief Handle mouse move event
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context() first and
     * then propagates the event to ImGui. Returns @cpp true @ce if ImGui
     * wants to capture the mouse (so the event shouldn't be further
     * propagated to the rest of the application), @cpp false @ce
     * otherwise.
     */
    template<class MouseMoveEvent> bool handleMouseMoveEvent(MouseMoveEvent& event);

    /**
     * @brief Handle key press event
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context() first and
     * then propagates the event to ImGui. Returns @cpp true @ce if ImGui
     * wants to capture the keyboard (so the event shouldn't be further
     * propagated to the rest of the application), @cpp false @ce
     * otherwise.
     */
    template<class KeyEvent> bool handleKeyPressEvent(KeyEvent& event);

    /**
     * @brief Handle key release event
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context() first and
     * then propagates the event to ImGui. Returns @cpp true @ce if ImGui
     * wants to capture the keyboard (so the event shouldn't be further
     * propagated to the rest of the application), @cpp false @ce
     * otherwise.
     */
    template<class KeyEvent> bool handleKeyReleaseEvent(KeyEvent& event);

    /**
     * @brief Handle text input event
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context() first and
     * then propagates the event to ImGui. Returns @cpp true @ce if ImGui
     * wants to capture the keyboard (so the event shouldn't be further
     * propagated to the rest of the application), @cpp false @ce
     * otherwise.
     */
    template<class TextInputEvent> bool handleTextInputEvent(TextInputEvent& event);

    /**
     * @brief Update application mouse cursor
     * @m_since_{integration,2020,06}
     *
     * Calls @cpp ImGui::SetContextCurent() @ce on @ref context() first and
     * then queries @cpp ImGui::GetMouseCursor() @ce, propagating that to
     * the application via @ref Platform::Sdl2Application::setCursor() "setCursor()".
     * If the application doesn't implement a corresponding cursor, falls
     * back to @ref Platform::Sdl2Application::Cursor::Arrow "Cursor::Arrow".
     */
    template<class Application> void updateApplicationCursor(Application& application);

    private:
    ImGuiContext* _context;
    Shaders::FlatGL2D _shader;
    GL::Texture2D _texture{NoCreate};
    GL::Buffer _vertexBuffer{GL::Buffer::TargetHint::Array};
    GL::Buffer _indexBuffer{GL::Buffer::TargetHint::ElementArray};
    Timeline _timeline;
    GL::Mesh _mesh;
    Vector2 _supersamplingRatio,
    _eventScaling;
    BoolVector3 _mousePressed, _mousePressedInThisFrame;

    private:
    template<class KeyEvent> bool handleKeyEvent(KeyEvent& event, bool value);
    template<class MouseEvent> bool handleMouseEvent(MouseEvent& event, bool value);
};

#endif //CORE_GUICONTEXT_H
