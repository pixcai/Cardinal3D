#include "manager.h"

namespace cardinal {
namespace gui {

Manager::Manager(const glm::ivec2 dimension) : dimension_(dimension) {}

Manager::~Manager() {}

void Manager::Render(rendering::Scene &scene, rendering::Camera &camera) {
    glm::mat4 &view_matrix = camera.GetViewMatrix();

    scene.ForEach([&](rendering::SceneItem &item) { item.Render(view_matrix); });
    RenderMainMenuBar(scene);
}

} // namespace gui
} // namespace cardinal