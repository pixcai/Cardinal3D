#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "camera.h"
#include "framebuffer.h"
#include "mesh.h"
#include "scene.h"
#include "shader.h"

namespace cardinal {
namespace rendering {

class Renderer {
  public:
    static void Setup(const glm::ivec2 dimension);
    static void Shutdown();
    static Renderer &Get();

    struct MeshOptions {
        GLuint id;
        glm::vec3 color;
        glm::mat4 model_view;
    };

    void BeginRender();
    void Render(Mesh &mesh, const MeshOptions &options);
    void EndRender();

    Camera &GetCamera();

  private:
    Renderer(const glm::ivec2 dimension);
    ~Renderer();

    static inline Renderer *m_current = nullptr;

    Framebuffer m_framebuffer;
    Shader m_mesh_shader;

    glm::ivec2 m_dimension;

    Camera m_camera;
};

} // namespace rendering
} // namespace cardinal