#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

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

  private:
    Renderer(const glm::ivec2 dimension);
    ~Renderer();

    static inline Renderer *current_ = nullptr;

    Framebuffer framebuffer_;
    Shader mesh_shader_;

    glm::ivec2 dimension_;
    glm::mat4 projection_;
};

} // namespace rendering
} // namespace cardinal