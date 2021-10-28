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
#include <core/GUI/GUIModule.h>
#include <core/Application/ApplicationModule.h>
#include <core/GUI/GUIBehaviour.h>

#include <functional>

namespace core {

GUIModule::GUIModule(ApplicationModule* appModule, InputModule* inputModule)
: IModule("GUI", WINDOW), appModule(appModule), inputModule(inputModule) {

}
void GUIModule::Start() {
    const Vector2 dpiScale         = appModule->GetWindowDpiScale(0);
    const Vector2i windowSize      = appModule->GetWindowSize(0);
    const Vector2i frameBufferSize = appModule->GetWindowFrameBufferSize(0);
    const float supersamplingRatio = frameBufferSize.x() / windowSize.x();

    ImGui::CreateContext();
    SetStandardFont(supersamplingRatio); // Order is important here, ImGui Context, Fonts, GUIContext
    gui = GUIContext(*ImGui::GetCurrentContext(), Vector2(windowSize) / dpiScale, windowSize, frameBufferSize);

    SubscribeToEvents();
    SetDefaultConfig();
    SetStandardStyle();
}
void GUIModule::SubscribeToEvents() {
    inputModule->OnMouseMoveEvent.Subscribe([&](MouseMoveEvent& event)     { gui.HandleMouseMoveEvent(event);     } );
    inputModule->OnTextInputEvent.Subscribe([&](TextInputEvent& event)     { gui.HandleTextInputEvent(event);     } );
    inputModule->OnMousePressEvent.Subscribe([&](MouseEvent& event)        { gui.HandleMousePressEvent(event);    } );
    inputModule->OnMouseReleaseEvent.Subscribe([&](MouseEvent& event)      { gui.HandleMouseReleaseEvent(event);  } );
    inputModule->OnMouseScrollEvent.Subscribe([&](MouseScrollEvent& event) { gui.HandleMouseScrollEvent(event);   } );
    inputModule->OnKeyPressEvent.Subscribe([&](KeyEvent& event)            { gui.HandleKeyPressEvent(event);      } );
    inputModule->OnKeyReleaseEvent.Subscribe([&](KeyEvent& event)          { gui.HandleKeyReleaseEvent(event);    } );
    inputModule->OnViewportEvent.Subscribe([&](ViewportEvent& event)       { gui.Relayout(event.GetWindowSize()); } );
}
void GUIModule::EarlyTick() {
    gui.NewFrame();
}
void GUIModule::Tick() {
    UpdateGUI();
    DrawGUI();
}
void GUIModule::UpdateGUI() {
    std::for_each(GUIBehaviour::instances.begin(),
                  GUIBehaviour::instances.end(),
                  [&] (GUIBehaviour* b) { b->OnGUI(); });
}
void GUIModule::DrawGUI() {
    GL::Renderer::enable(GL::Renderer::Feature::Blending);
    GL::Renderer::enable(GL::Renderer::Feature::ScissorTest);
    GL::Renderer::disable(GL::Renderer::Feature::FaceCulling);
    GL::Renderer::disable(GL::Renderer::Feature::DepthTest);

    gui.DrawFrame();

    GL::Renderer::disable(GL::Renderer::Feature::ScissorTest);
    GL::Renderer::disable(GL::Renderer::Feature::Blending);
    GL::Renderer::enable(GL::Renderer::Feature::DepthTest);
    GL::Renderer::enable(GL::Renderer::Feature::FaceCulling);
}
void GUIModule::SetStandardFont(const float ratio) {
    string filePath = __FILE__;
    string dirPath = filePath.substr(0, filePath.rfind("\\"));
    string fontsPath = dirPath + "/../../lib/other/";

    ImFontConfig thinFontConfig;
    thinFontConfig.OversampleH = 3;
    thinFontConfig.OversampleV = 2;
    thinFontConfig.RasterizerMultiply = 1.9f;

    ImGui::GetIO().Fonts->Clear();
    ImGui::GetIO().Fonts->AddFontFromFileTTF((fontsPath + "DejaVuSans-ExtraLight.ttf").c_str(), 14.0f * ratio, &thinFontConfig);
    ImGui::GetIO().Fonts->AddFontFromFileTTF((fontsPath + "DejaVuSansMono.ttf").c_str(), 14.0f * ratio);
    ImGui::GetIO().Fonts->Build();
}
void GUIModule::SetStandardStyle() {
    const int rounding = 4;

    ImGuiStyle& style               = ImGui::GetStyle();
    style.WindowPadding             = ImVec2(7, 7);
    style.FramePadding              = ImVec2(6, 3);
    style.CellPadding               = ImVec2(6, 3);
    style.ItemSpacing               = ImVec2(8, 4);
    style.ItemInnerSpacing          = ImVec2(6, 6);
    style.IndentSpacing             = 15;
    style.ScrollbarSize             = 12;
    style.GrabMinSize               = 12;
    style.WindowBorderSize          = 1;
    style.ChildBorderSize           = 1;
    style.PopupBorderSize           = 0;
    style.FrameBorderSize           = 0;
    style.TabBorderSize             = 0;
    style.ScrollbarRounding         = 8;
    style.WindowRounding            = rounding;
    style.ChildRounding             = rounding;
    style.FrameRounding             = rounding;
    style.PopupRounding             = rounding;
    style.GrabRounding              = rounding;
    style.LogSliderDeadzone         = rounding;
    style.TabRounding               = rounding;
    style.WindowTitleAlign          = ImVec2(0, 0.5f);
    style.ButtonTextAlign           = ImVec2(0.5f, 0.5f);
    style.DisplaySafeAreaPadding    = ImVec2(3, 3);
    style.WindowMenuButtonPosition  = ImGuiDir_None;
    style.ColorButtonPosition       = ImGuiDir_Right;

    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.63f, 0.63f, 0.63f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); // temporary made transparent, read comments in EditorModule.cpp
    colors[ImGuiCol_ChildBg]                = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.13f, 0.13f, 0.13f, 1.00f);
    colors[ImGuiCol_Border]                 = ImVec4(0.27f, 0.27f, 0.27f, 1.00f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(1.00f, 1.00f, 1.00f, 0.23f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.44f, 0.44f, 0.44f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.41f, 0.43f, 0.46f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.16f, 0.16f, 0.16f, 0.82f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.16f, 0.16f, 0.16f, 0.56f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.00f, 0.00f, 0.00f, 0.37f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.30f, 0.30f, 0.30f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.17f, 0.17f, 0.17f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.66f, 0.96f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.50f, 0.84f, 1.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.14f, 0.51f, 0.94f, 0.53f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.50f, 0.84f, 1.00f, 1.00f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}
void GUIModule::SetDefaultConfig() {

}

}