#pragma once

#include <glm/glm.hpp>

#include "framebuffer.h"
#include "scene.h"

namespace cardinal {
namespace rendering {

class Renderer {
  public:
    Renderer(const glm::ivec2 dimension);
    ~Renderer();

    void BeginRender();
    void EndRender();

  private:
    Framebuffer framebuffer_;

    glm::ivec2 dimension_;
};

} // namespace rendering
} // namespace cardinal