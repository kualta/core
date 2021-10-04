namespace core {

template<typename T>
ImGuiID EditorModule::AddWindow(ImGuiID& parent, const string& title, ImGuiDir direction, float size) {
    static_assert(std::is_base_of<core::EditorWindow, T>::value, "Window Type T must inherit from core::EditorWindow");

    Logger::Log(GENERAL) << "Parent: " << parent;
    Logger::Log(GENERAL) << "Title: " << title;
    unique<T> window = std::make_unique<T>(parent, title, direction, size);
    ImGuiID dockID = window->GetDockID();
    Logger::Log(GENERAL) << "DockID: " << dockID;
    windows.push_back(std::move(window));

    return dockID;
}

}