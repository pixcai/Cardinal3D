#include "manager.h"

namespace cardinal {
namespace gui {

Manager::Manager(const glm::ivec2 dimension) : dimension_(dimension) {}

Manager::~Manager() {}

void Manager::Render(rendering::Scene &scene, const rendering::Camera &camera) {
    const glm::mat4 &view = camera.GetViewMatrix();

    scene.ForEach([&](rendering::SceneItem &item) { item.Render(view); });
    RenderMainMenuBar(scene);
}

} // namespace gui
} // namespace cardinal