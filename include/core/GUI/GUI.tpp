#include <type_traits>
#include <misc/cpp/imgui_stdlib.h>
#include <core/Logger.h>
#include <any>

namespace core {

template<typename T>
bool GUI::Input(const string& label, T* value) {
    bool updated;
    ImGui::PushID(value);

    if      constexpr(std::is_same<int, T>::value)      { updated = ImGui::InputInt(label.c_str(), value); }
    else if constexpr(std::is_same<float, T>::value)    { updated = ImGui::InputFloat(label.c_str(), value); }
    else if constexpr(std::is_same<double, T>::value)   { updated = ImGui::InputDouble(label.c_str(), value); }
    else if constexpr(std::is_same<string, T>::value)   { updated = ImGui::InputText(label.c_str(), value); }
    else if constexpr(std::is_same<Vector4, T>::value)  { updated = ImGui::InputFloat4(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Vector3, T>::value)  { updated = ImGui::InputFloat3(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Vector2, T>::value)  { updated = ImGui::InputFloat2(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Vector4i, T>::value) { updated = ImGui::InputInt4(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Vector3i, T>::value) { updated = ImGui::InputInt3(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Vector2i, T>::value) { updated = ImGui::InputInt2(label.c_str(), value->data()); }
    else if constexpr(std::is_same<Matrix4, T>::value)  { updated = GUI::InputMatrix(label, value); }
    else if constexpr(std::is_same<Matrix3, T>::value)  { updated = GUI::InputMatrix(label, value); }

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