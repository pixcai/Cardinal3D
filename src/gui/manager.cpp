// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#include "gui/manager.h"
#include "rendering/scene_object.h"

namespace cardinal {
namespace gui {

Manager::Manager(const glm::ivec2 dimension) : m_dimension(dimension) {}

Manager::~Manager() {}

void Manager::Render(rendering::Scene &scene) {
    scene.ForEach([&](rendering::SceneObjectBase &object) { object.Render(); });
    RenderMainMenuBar(scene);
}

} // namespace gui
} // namespace cardinal
