#include <core/GUI/GUI.h>
#include "Magnum/ImGuiIntegration/Integration.h"

namespace core {

bool GUI::Button(const string &title, Vector2 pos) {
    return ImGui::Button(title.c_str(), ImVec2(pos));
}

}