// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "rendering/scene.h"
#include <glm/glm.hpp>
#include <imgui.h>

namespace cardinal {
namespace gui {

class Manager {
public:
    Manager(glm::ivec2 dimension);
    ~Manager();

    void Render(rendering::Scene &scene);

private:
    void RenderMainMenuBar(rendering::Scene &scene);

    glm::ivec2 m_dimension;
};

} // namespace gui
} // namespace cardinal
