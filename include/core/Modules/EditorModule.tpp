namespace core {

template<typename T>
ImGuiID EditorModule::AddWindow(ImGuiID parent, const string& title, ImGuiDir direction, float size) {
    static_assert(std::is_base_of<core::EditorWindow, T>::value, "Window Type T must inherit from core::EditorWindow");

    unique<T> window = std::make_unique<T>(parent, title, direction, size);
    ImGuiID dockID = window->GetDockID();
    windows.push_back(std::move(window));

    return dockID;
}

}