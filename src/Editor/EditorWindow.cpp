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
#include <core/Editor/EditorWindow.h>
#include <core/Logger.h>

#include <utility>

namespace core {

EditorWindow::EditorWindow(ImGuiID dockID, string title)
: title(std::move(title)), dockID(dockID)
{
    ImGui::DockBuilderDockWindow(GetTitle().c_str(), dockID);
}
string EditorWindow::GetTitle() {
    return title;
}
ImGuiID EditorWindow::GetDockID() {
    return dockID;
}
void EditorWindow::Draw() {
    ImGui::Begin(title.c_str(), &isOpen, flags);
        DrawWindowContent();
    ImGui::End();
}
void EditorWindow::AddCustomStyle(ImGuiCol colorVar, ImVec4 newvalue) {
    ImVec4* colors = ImGui::GetStyle().Colors;
    ImVec4 oldValue = colors[colorVar];
    customStyles.push_back({colorVar, newvalue, oldValue});
}
void EditorWindow::ApplyCustomStyles() {
    ImVec4* colors = ImGui::GetStyle().Colors;
//    colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0);
    for (auto& style : customStyles) {
        Log() << style.colorVar << " " << style.newvalue.z;
        colors[style.colorVar] = style.newvalue;
    }
}
void EditorWindow::RemoveCustomStyles() {
//    ImVec4* colors = ImGui::GetStyle().Colors;
//    colors[ImGuiCol_WindowBg] = ImVec4(1, 1, 1, 1);
    ImVec4* colors = ImGui::GetStyle().Colors;
    for (auto& style : customStyles) {
        Log() << style.colorVar << " " << style.oldValue.z;
        colors[style.colorVar] = style.oldValue;
    }
}

}