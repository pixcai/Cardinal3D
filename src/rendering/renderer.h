// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "common.h"
#include "rendering/camera.h"
#include "rendering/framebuffer.h"
#include "rendering/shader.h"

namespace cardinal {
namespace rendering {

class Renderer {
public:
    static void Setup(const glm::ivec2 dimension);
    static void Shutdown();
    static Renderer &Get();

    void BeginRender();
    template <typename Tp>
    void Render(Tp &object, Camera &camera);
    void EndRender();

private:
    Renderer(const glm::ivec2 dimension);
    ~Renderer();

    static inline Renderer *m_current = nullptr;

    Framebuffer m_framebuffer;
    Shader m_mesh_shader;

    glm::ivec2 m_dimension;
};

} // namespace rendering
} // namespace cardinal
