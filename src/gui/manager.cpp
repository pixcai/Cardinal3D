#include <imgui.h>

#include "manager.h"

namespace cardinal {
namespace gui {

Manager::Manager(const glm::vec2 dimension) { dimension_ = dimension; }

Manager::~Manager() {}

void Manager::Render(rendering::Scene &scene) { RenderMainMenuBar(scene); }

} // namespace gui
} // namespace cardinal