/*
 * This is a stand-alone header file. No SceneGraphEditorWinodw.cpp is presented.
 */

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
#ifndef CORE_HIERARCHYREDITORWINDOW_H
#define CORE_HIERARCHYREDITORWINDOW_H

#include "core/Essentials.h"
#include "EditorWindow.h"

namespace core {

class HierarchyEditorWindow : public EditorWindow {
public:
    HierarchyEditorWindow(ImGuiID& dockID) : EditorWindow(dockID, "Hierarchy") {

    }

    void DrawWindowContent() override {
        ImGui::Text("Wow Hierarchy!");
        // TODO: Implement Hierarchy window
    }

};

}

#endif //CORE_HIERARCHYREDITORWINDOW_H
