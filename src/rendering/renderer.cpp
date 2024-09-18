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
    const glm::mat4 &projection = m_camera.GetProjectionMatrix();

    m_mesh_shader.Bind();
    m_mesh_shader.Uniform("u_mvp", projection * options.model_view);
    m_mesh_shader.Uniform("u_color", options.color);
    mesh.Render();
}

void Renderer::EndRender() { m_framebuffer.BlitToScreen(0, m_dimension); }

Camera &Renderer::GetCamera() { return m_camera; }

Renderer::Renderer(const glm::ivec2 dimension)
    : m_framebuffer(2, dimension, DEFAULT_SAMPLES, true),
      m_mesh_shader(Shader::Presets::mesh_vertex, Shader::Presets::mesh_fragment), m_dimension(dimension),
      m_camera(dimension) {}

Renderer::~Renderer() {}

} // namespace rendering
} // namespace cardinal