#pragma once

#include <glm/vec2.hpp>

#include "rendering/scene.h"

namespace cardinal {
namespace gui {

class Manager {
  public:
    Manager(const glm::vec2 dimension);
    ~Manager();

    void Render(rendering::Scene &scene);

  private:
    void RenderMainMenuBar(rendering::Scene &scene);

    glm::vec2 dimension_;
};

} // namespace gui
} // namespace cardinal