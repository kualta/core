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
#include <type_traits>
#include <misc/cpp/imgui_stdlib.h>
#include <core/Logger.h>
#include <any>

namespace core {

template<typename T>
bool GUI::Input(const string& label, T* value) {
    bool updated = false;
    ImGui::PushID(value);

    if      constexpr(std::is_same<int, T>::value)      { updated = ImGui::InputInt(label.c_str(), value); }
    else if constexpr(std::is_same<float, T>::value)    { updated = ImGui::InputFloat(label.c_str(), value, 0.1f, 0.1f); }
    else if constexpr(std::is_same<double, T>::value)   { updated = ImGui::InputDouble(label.c_str(), value, 0.1f, 0.1f); }
    else if constexpr(std::is_same<string, T>::value)   { updated = ImGui::InputText(label.c_str(), value); }
    else if constexpr(std::is_same<Vector4, T>::value)  { updated = ImGui::InputFloat4(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Vector3, T>::value)  { updated = ImGui::InputFloat3(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Vector2, T>::value)  { updated = ImGui::InputFloat2(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Vector4i, T>::value) { updated = ImGui::InputInt4(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Vector3i, T>::value) { updated = ImGui::InputInt3(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Vector2i, T>::value) { updated = ImGui::InputInt2(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Matrix4, T>::value)  { updated = GUI::InputMatrix(label, value); }
    else if constexpr(std::is_same<Matrix3, T>::value)  { updated = GUI::InputMatrix(label, value); }
    else if constexpr(std::is_same<Color3, T>::value)   { updated = ImGui::ColorEdit3(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Color4, T>::value)   { updated = ImGui::ColorEdit4(label.c_str(), value->data(), ImGuiColorEditFlags_AlphaBar); }

    ImGui::PopID();
    return updated;
}
template<typename T>
bool GUI::Slider(const string &label, T* value, float min, float max) {
    bool updated = false;
    ImGui::PushID(value);

    if      constexpr(std::is_same<int, T>::value)      { updated = ImGui::SliderInt(label.c_str(), value, min, max); }
    else if constexpr(std::is_same<float, T>::value)    { updated = ImGui::SliderFloat(label.c_str(), value, min, max); }
    else if constexpr(std::is_same<Vector4, T>::value)  { updated = ImGui::SliderFloat4(label.c_str(), value->data(), min, max); }
    else if constexpr(std::is_same<Vector3, T>::value)  { updated = ImGui::SliderFloat3(label.c_str(), value->data(), min, max); }
    else if constexpr(std::is_same<Vector2, T>::value)  { updated = ImGui::SliderFloat2(label.c_str(), value->data(), min, max); }
    else if constexpr(std::is_same<Vector4i, T>::value) { updated = ImGui::SliderInt4(label.c_str(), value->data(), min, max); }
    else if constexpr(std::is_same<Vector3i, T>::value) { updated = ImGui::SliderInt3(label.c_str(), value->data(), min, max); }
    else if constexpr(std::is_same<Vector2i, T>::value) { updated = ImGui::SliderInt2(label.c_str(), value->data(), min, max); }

    ImGui::PopID();
    return updated;
}
template<typename T>
bool GUI::InputMatrix(const string &label, T* mtx) {
    bool updated = false;
    size_t cols = mtx->Cols;

    for (int i = 0; i < cols; i++) {
        auto* ptr = mtx->data() + (cols * i);
        ImGui::PushID(ptr);
        updated |= ImGui::InputScalarN(i == 0 ? label.c_str() : "", ImGuiDataType_Float, ptr, cols);
        ImGui::PopID();
    }
    return updated;
}

}