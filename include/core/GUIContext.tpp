#ifndef CORE_GUICONTEXT_TPP
#define CORE_GUICONTEXT_TPP

namespace core {

template <class KeyEvent>
bool Context::HandleKeyEvent(KeyEvent& event, bool value) {
    ImGui::SetCurrentContext(context);

    ImGuiIO &io = ImGui::GetIO();

    switch (event.key()) {
        case KeyEvent::Key::LeftShift:
        case KeyEvent::Key::RightShift:
            io.KeyShift = value;
            break;
        case KeyEvent::Key::LeftCtrl:
        case KeyEvent::Key::RightCtrl:
            io.KeyCtrl = value;
            break;
        case KeyEvent::Key::LeftAlt:
        case KeyEvent::Key::RightAlt:
            io.KeyAlt = value;
            break;
        case KeyEvent::Key::LeftSuper:
        case KeyEvent::Key::RightSuper:
            io.KeySuper = value;
            break;
        case KeyEvent::Key::Tab:
            io.KeysDown[ImGuiKey_Tab] = value;
            break;
        case KeyEvent::Key::Up:
            io.KeysDown[ImGuiKey_UpArrow] = value;
            break;
        case KeyEvent::Key::Down:
            io.KeysDown[ImGuiKey_DownArrow] = value;
            break;
        case KeyEvent::Key::Left:
            io.KeysDown[ImGuiKey_LeftArrow] = value;
            break;
        case KeyEvent::Key::Right:
            io.KeysDown[ImGuiKey_RightArrow] = value;
            break;
        case KeyEvent::Key::Home:
            io.KeysDown[ImGuiKey_Home] = value;
            break;
        case KeyEvent::Key::End:
            io.KeysDown[ImGuiKey_End] = value;
            break;
        case KeyEvent::Key::PageUp:
            io.KeysDown[ImGuiKey_PageUp] = value;
            break;
        case KeyEvent::Key::PageDown:
            io.KeysDown[ImGuiKey_PageDown] = value;
            break;
        case KeyEvent::Key::Enter:
        case KeyEvent::Key::NumEnter:
            io.KeysDown[ImGuiKey_Enter] = value;
            break;
        case KeyEvent::Key::Esc:
            io.KeysDown[ImGuiKey_Escape] = value;
            break;
        case KeyEvent::Key::Space:
            io.KeysDown[ImGuiKey_Space] = value;
            break;
        case KeyEvent::Key::Backspace:
            io.KeysDown[ImGuiKey_Backspace] = value;
            break;
        case KeyEvent::Key::Delete:
            io.KeysDown[ImGuiKey_Delete] = value;
            break;
        case KeyEvent::Key::A:
            io.KeysDown[ImGuiKey_A] = value;
            break;
        case KeyEvent::Key::C:
            io.KeysDown[ImGuiKey_C] = value;
            break;
        case KeyEvent::Key::V:
            io.KeysDown[ImGuiKey_V] = value;
            break;
        case KeyEvent::Key::X:
            io.KeysDown[ImGuiKey_X] = value;
            break;
        case KeyEvent::Key::Y:
            io.KeysDown[ImGuiKey_Y] = value;
            break;
        case KeyEvent::Key::Z:
            io.KeysDown[ImGuiKey_Z] = value;
            break;
            /* LCOV_EXCL_STOP */

            /* Unknown key, do nothing */
            default: return false;
    }

    return io.WantCaptureKeyboard;
}

template <class MouseEvent>
bool Context::HandleMouseEvent(MouseEvent& event, bool value) {
    ImGui::SetCurrentContext(context);

    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(Vector2(event.position())*eventScaling);

    std::size_t buttonId;
    switch(event.button()) {
        case MouseEvent::Button::Left:
            buttonId = 0;
            break;
        case MouseEvent::Button::Right:
            buttonId = 1;
            break;
        case MouseEvent::Button::Middle:
            buttonId = 2;
            break;

        /* Unknown button, do nothing */
        default: return false;
    }

    /* Instead of setting io.MouseDown directly, we delay this until the
       newFrame() call in order to prevent mouse clicks from being ignored when
       both a press and a release happens in the same frame. Apart from this
       happening when the app can't render fast enough, for some reason it also
       happens with SDL2 on macOS -- press delayed by a significant amount of
       time */
    mousePressed.set(buttonId, value);
    if(value) mousePressedInThisFrame.set(buttonId, true);

    return io.WantCaptureMouse;
}

template <class MouseEvent>
bool Context::HandleMousePressEvent(MouseEvent& event) {
    return HandleMouseEvent(event, true);
}

template <class MouseEvent>
bool Context::HandleMouseReleaseEvent(MouseEvent& event) {
    return HandleMouseEvent(event, false);
}

template <class MouseScrollEvent>
bool Context::HandleMouseScrollEvent(MouseScrollEvent& event) {
    /* Ensure we use the context we're linked to */
    ImGui::SetCurrentContext(context);

    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(Vector2(event.position())*eventScaling);
    io.MouseWheel += event.offset().y();
    io.MouseWheelH += event.offset().x();
    return io.WantCaptureMouse;
}

template <class MouseMoveEvent>
bool Context::HandleMouseMoveEvent(MouseMoveEvent& event) {
    /* Ensure we use the context we're linked to */
    ImGui::SetCurrentContext(context);

    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(Vector2(event.position())*eventScaling);
    return io.WantCaptureMouse;
}

template <class KeyEvent>
bool Context::HandleKeyPressEvent(KeyEvent& event) {
    return HandleKeyEvent(event, true);
}

template <class KeyEvent>
bool Context::HandleKeyReleaseEvent(KeyEvent& event) {
    return HandleKeyEvent(event, false);
}

template <class TextInputEvent>
bool Context::HandleTextInputEvent(TextInputEvent& event) {
    ImGui::SetCurrentContext(context);

    ImGui::GetIO().AddInputCharactersUTF8(event.text().data());
    return false;
}

} // namespace core

#endif //CORE_GUICONTEXT_TPP
