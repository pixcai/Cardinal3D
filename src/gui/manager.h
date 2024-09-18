#pragma once

#include <glm/glm.hpp>
#include <imgui.h>

#include "rendering/camera.h"
#include "rendering/scene.h"

namespace cardinal {
namespace gui {

class Manager {
  public:
    Manager(const glm::ivec2 dimension);
    ~Manager();

    void Render(rendering::Scene &scene, const rendering::Camera &camera);

  private:
    void RenderMainMenuBar(rendering::Scene &scene);

    glm::ivec2 dimension_;
};

} // namespace gui
} // namespace cardinal