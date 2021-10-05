namespace core {

template<typename T>
ImGuiID EditorModule::AddWindow(ImGuiID& parent, ImGuiDir direction, float size) {
    static_assert(std::is_base_of<core::EditorWindow, T>::value, "Window Type T must inherit from core::EditorWindow");

    unique<T> window = std::make_unique<T>(parent, direction, size);
    ImGuiID dockID = window->GetDockID();
    windows.push_back(std::move(window));

    return dockID;
}

}