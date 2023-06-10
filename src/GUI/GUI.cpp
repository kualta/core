/*
 MIT License
 
 Copyright (c) 2021 kualta <contact@kualta.dev>
 
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
#include <core/GUI/GUI.h>
#include <Magnum/ImGuiIntegration/Integration.h>
#include <misc/cpp/imgui_stdlib.h>
#include <limits>

namespace core {

bool GUI::Button(const string& label, Vector2 size) {
    return ImGui::Button(label.c_str(), ImVec2(size));
}
bool GUI::CheckBox(const string& label, bool& value) {
    ImGui::PushID(value);
    bool out = ImGui::Checkbox(label.c_str(), &value);
    ImGui::PopID();
    return out;
}
void GUI::Text(const string& text) {
    return ImGui::Text("%s", text.c_str());
}
bool GUI::IsHovered() {
    return ImGui::IsItemHovered();
}
bool GUI::IsActive() {
    return ImGui::IsItemActive();
}
bool GUI::IsFocused() {
    return ImGui::IsItemFocused();
}
void GUI::Tooltip(const string& text) {
    ImGui::SetTooltip("%s", text.c_str());
}
void GUI::TextLabel(const string& text, const string& label) {
    ImGui::LabelText(label.c_str(), text.c_str());
}
bool GUI::Box(bool& isOpen) {
    ImGui::PushID(isOpen);
    bool out = ImGui::BeginChild("Box", { 0, 0 }, false, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse );
    return out;
}
void GUI::EndBox() {
    ImGui::EndChild();
    ImGui::PopID();
}

}