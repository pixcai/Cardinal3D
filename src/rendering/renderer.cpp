#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.h"

static const int DEFAULT_SAMPLES = 4;

namespace cardinal {
namespace rendering {

void Renderer::Setup(const glm::ivec2 dimension) {
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonOffset(1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_GREATER);
    glClearDepth(0.0f);
    glCullFace(GL_BACK);
    current_ = new Renderer(dimension);
}

void Renderer::Shutdown() {
    delete current_;
    current_ = nullptr;
}

Renderer &Renderer::Get() {
    assert(current_);
    return *current_;
}

void Renderer::BeginRender() {
    framebuffer_.Clear(0, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    framebuffer_.Clear(1, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    framebuffer_.ClearDepth();
}

void Renderer::Render(Mesh &mesh, const MeshOptions &options) {
    mesh_shader_.Bind();
    mesh_shader_.Uniform("u_mvp", projection_ * options.model_view);
    mesh_shader_.Uniform("u_color", options.color);
    mesh.Render();
}

void Renderer::EndRender() { framebuffer_.BlitToScreen(0, dimension_); }

Renderer::Renderer(const glm::ivec2 dimension)
    : framebuffer_(2, dimension, DEFAULT_SAMPLES, true),
      mesh_shader_(Shader::Presets::mesh_vertex, Shader::Presets::mesh_fragment), dimension_(dimension),
      projection_(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)) {}

Renderer::~Renderer() {}

} // namespace rendering
} // namespace cardinal