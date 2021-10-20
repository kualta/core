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
#ifndef CORE_EDITORMODULE_H
#define CORE_EDITORMODULE_H

#include <core/Essentials.h>
#include <core/GUI/GUIModule.h>
#include <core/GUI/GUIBehaviour.h>
#include <core/IModule.h>
#include <core/GUI/GUI.h>
#include <core/Editor/EditorWindow.h>
#include <core/Scene/SceneView.h>

namespace core {

class EditorModule : public IModule, public GUIBehaviour {
public:
    explicit EditorModule(GUIModule* guiModule, InputModule* inputModule, SceneModule* sceneModule);

    template<typename T>
    ImGuiID AddWindow(ImGuiID dockID);

protected:

    void Start() override;
    void OnGUI() override;

    void PushDockStyle() const;
    void PopDockStyle() const;
    void ReloadViewport();
    void BeginEditorDockSpace();
    void ConstructDockSpace();

    InputModule*        inputModule;
    GUIModule*          guiModule;
    SceneModule*        sceneModule;

    ImGuiViewport*      viewport;
    SceneView           sceneView;
    ImGuiID             dockSpaceID;
    string              editorDockSpaceName;
    bool                viewportNeedsReload { true };

    ImGuiDockNodeFlags  dockSpaceFlags;
    ImGuiWindowFlags    windowFlags;

    std::vector<unique<EditorWindow>> windows;

};

} // namespace core

#include "EditorModule.tpp"

#endif //CORE_EDITORMODULE_H
