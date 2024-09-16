#include <tinyfiledialogs/tinyfiledialogs.h>

#include "manager.h"

namespace cardinal {
namespace gui {

static void OnOpen(rendering::Scene &scene) {
    char *file = nullptr;

    file = tinyfd_openFileDialog("Open", nullptr, 0, nullptr, nullptr, 0);
    if (!file) {
        return;
    }
    scene.Load(std::string(file));
}

void Manager::RenderMainMenuBar(rendering::Scene &scene) {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
                OnOpen(scene);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

} // namespace gui
} // namespace cardinal