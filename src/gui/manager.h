#pragma once

#include <glm/glm.hpp>
#include <imgui.h>

#include "rendering/camera.h"
#include "rendering/scene.h"

namespace cardinal {
namespace gui {

class Manager {
  public:
    Manager(glm::ivec2 dimension);
    ~Manager();

    void Render(rendering::Scene &scene, rendering::Camera &camera);

  private:
    void RenderMainMenuBar(rendering::Scene &scene);

    glm::ivec2 m_dimension;
};

} // namespace gui
} // namespace cardinal