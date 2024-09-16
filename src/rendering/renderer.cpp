#include "renderer.h"

static const int DEFAULT_SAMPLES = 4;

namespace cardinal {
namespace rendering {

Renderer::Renderer(const glm::ivec2 dimension)
    : dimension_(dimension), framebuffer_(2, dimension, DEFAULT_SAMPLES, true) {}

Renderer::~Renderer() {}

void Renderer::BeginRender() {
    framebuffer_.Clear(0, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    framebuffer_.Clear(1, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    framebuffer_.ClearDepth();
}

void Renderer::EndRender() { framebuffer_.BlitToScreen(0, dimension_); }

} // namespace rendering
} // namespace cardinal