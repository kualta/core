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
#ifndef CORE_SCENEVIEWEDITORWINDOW_H
#define CORE_SCENEVIEWEDITORWINDOW_H

#include "core/Essentials.h"
#include "core/Logger.h"
#include "core/GUI/GUI.h"
#include "core/Editor/EditorWindow.h"

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/GL/Buffer.h>
#include "Magnum/ImGuiIntegration/Integration.h"

namespace core {

class SceneViewEditorWindow : public EditorWindow {
public:
    SceneViewEditorWindow(ImGuiID& dockID) : EditorWindow(dockID, "Scene View") {
        flags |= ImGuiWindowFlags_NoBackground;
    }

    void DrawWindowContent() override {
        ImVec2 currentSize = ImGui::GetWindowSize();
        ImVec2 currentPos = ImGui::GetWindowPos();
        if (currentSize.x != size.x || currentSize.y != size.y || currentPos.x != pos.x || currentPos.y != pos.y) {
            size = currentSize;
            pos = currentPos;
            SceneView::Get()->Resize(Vector2i(pos.x, pos.y), Vector2i(size.x, size.y));
        }

    }

protected:

    static ImVec2 size;
    static ImVec2 pos;
};

ImVec2 SceneViewEditorWindow::size { 0, 0 };
ImVec2 SceneViewEditorWindow::pos  { 0, 0 };

} // namespace core

#endif //CORE_SCENEVIEWEDITORWINDOW_H
