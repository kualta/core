/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#ifndef CORE_GUICONTEXT_TPP
#define CORE_GUICONTEXT_TPP

namespace core {

template<class KeyEvent>
bool GUIContext::HandleKeyEvent(KeyEvent& event, bool value) {
    ImGui::SetCurrentContext(context);

    ImGuiIO &io = ImGui::GetIO();

    switch (event.GetKey()) {
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

            /* Unknown GetKey, do nothing */
            default: return false;
    }

    return io.WantCaptureKeyboard;
}

template<class MouseEvent>
bool GUIContext::HandleMouseEvent(MouseEvent& event, bool value) {
    ImGui::SetCurrentContext(context);

    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(Vector2(event.GetPosition()) * eventScaling);

    std::size_t buttonId;
    switch(event.GetButton()) {
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
    if (value) mousePressedInThisFrame.set(buttonId, true);

    return io.WantCaptureMouse;
}

template<class MouseEvent>
bool GUIContext::HandleMousePressEvent(MouseEvent& event) {
    return HandleMouseEvent(event, true);
}

template<class MouseEvent>
bool GUIContext::HandleMouseReleaseEvent(MouseEvent& event) {
    return HandleMouseEvent(event, false);
}

template<class MouseScrollEvent>
bool GUIContext::HandleMouseScrollEvent(MouseScrollEvent& event) {
    /* Ensure we use the context we're linked to */
    ImGui::SetCurrentContext(context);

    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(Vector2(event.GetPosition()) * eventScaling);
    io.MouseWheel += event.GetOffset().y();
    io.MouseWheelH += event.GetOffset().x();
    return io.WantCaptureMouse;
}

template<class MouseMoveEvent>
bool GUIContext::HandleMouseMoveEvent(MouseMoveEvent& event) {
    /* Ensure we use the context we're linked to */
    ImGui::SetCurrentContext(context);

    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(Vector2(event.GetPosition()) * eventScaling);
    return io.WantCaptureMouse;
}

template<class KeyEvent>
bool GUIContext::HandleKeyPressEvent(KeyEvent& event) {
    return HandleKeyEvent(event, true);
}

template<class KeyEvent>
bool GUIContext::HandleKeyReleaseEvent(KeyEvent& event) {
    return HandleKeyEvent(event, false);
}

template<class TextInputEvent>
bool GUIContext::HandleTextInputEvent(TextInputEvent& event) {
    ImGui::SetCurrentContext(context);
    ImGui::GetIO().AddInputCharactersUTF8(event.GetText().data());
    return false;
}

} // namespace core

#endif //CORE_GUICONTEXT_TPP
