#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace cardinal {
namespace rendering {

class Framebuffer {
  public:
    Framebuffer(int outputs, const glm::ivec2 dimension, int samples = 1, bool depth = true);
    Framebuffer(const Framebuffer &other) = delete;
    Framebuffer(Framebuffer &&other);
    ~Framebuffer();

    void operator=(const Framebuffer &other) = delete;
    void operator=(Framebuffer &&other);

    void Bind() const;
    void Clear(int index, const glm::vec4 &color) const;
    void ClearDepth() const;
    void Resize(const glm::ivec2 dimension, int samples = 1);

    void BlitToScreen(int index, const glm::ivec2 dimension) const;
    void BlitTo(int index, const Framebuffer &other) const;

  private:
    void Create();
    void Destroy();

    std::vector<GLuint> output_textures_;
    GLuint depth_texture_ = 0;
    GLuint framebuffer_ = 0;

    int samples_ = 0;
    bool depth_ = true;

    glm::ivec2 dimension_;
};

} // namespace rendering
} // namespace cardinal
