// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "common.h"
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

    void SetProjectionMatrix(const glm::mat4 &projection_matrix);

private:
    Renderer(const glm::ivec2 dimension);
    ~Renderer();

    static inline Renderer *m_current = nullptr;

    Framebuffer m_framebuffer;
    Shader m_mesh_shader;

    glm::ivec2 m_dimension;
    glm::mat4 m_projection_matrix = glm::mat4(1.0f);
};

} // namespace rendering
} // namespace cardinal
