#include "manager.h"

namespace cardinal {
namespace gui {

Manager::Manager(const glm::ivec2 dimension) : dimension_(dimension) {}

Manager::~Manager() {}

void Manager::Render(rendering::Scene &scene) {
    scene.ForEach([&](rendering::SceneItem &item) { item.Render(); });
    RenderMainMenuBar(scene);
}

} // namespace gui
} // namespace cardinal