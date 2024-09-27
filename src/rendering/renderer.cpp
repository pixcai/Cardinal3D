// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#include "renderer.h"

static constexpr int DEFAULT_SAMPLES = 4;

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
    m_current = new Renderer(dimension);
}

void Renderer::Shutdown() {
    delete m_current;
    m_current = nullptr;
}

Renderer &Renderer::Get() {
    assert(m_current);
    return *m_current;
}

void Renderer::BeginRender() {
    m_framebuffer.Clear(0, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    m_framebuffer.Clear(1, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    m_framebuffer.ClearDepth();
}

void Renderer::Render(Mesh &mesh, const MeshOptions &options) {
    m_mesh_shader.Bind();
    m_mesh_shader.Uniform("u_mvp", m_projection_matrix * options.model_view);
    m_mesh_shader.Uniform("u_normal",
                          glm::transpose(glm::inverse(options.model_view)));
    m_mesh_shader.Uniform("u_color", options.color);
    mesh.Render();
}

void Renderer::EndRender() {
    m_framebuffer.BlitToScreen(0, m_dimension);
}

void Renderer::SetProjectionMatrix(const glm::mat4 &projection_matrix) {
    m_projection_matrix = projection_matrix;
}

Renderer::Renderer(const glm::ivec2 dimension)
    : m_framebuffer(2, dimension, DEFAULT_SAMPLES, true),
      m_mesh_shader(ShaderPresets::kMeshVertex, ShaderPresets::kMeshFragment),
      m_dimension(dimension) {}

Renderer::~Renderer() {}

} // namespace rendering
} // namespace cardinal
