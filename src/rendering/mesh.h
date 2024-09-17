#pragma once

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace cardinal {
namespace rendering {

class Mesh {
  public:
    using Index = GLuint;

    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        GLuint id;
    };

    Mesh();
    Mesh(std::vector<Vertex> &&vertices, std::vector<Index> &&indices);
    Mesh(const Mesh &other) = delete;
    Mesh(Mesh &&other);
    ~Mesh();

    void operator=(const Mesh &other) = delete;
    void operator=(Mesh &&other);

    void Render();
    void ReCreate(std::vector<Vertex> &&vertices, std::vector<Index> &&indices);

  private:
    void Create();
    void Destroy();
    void Update();

    bool dirty_ = true;
    GLuint element_count_ = 0;
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
    GLuint ebo_ = 0;

    std::vector<Vertex> vertices_;
    std::vector<Index> indices_;
};

} // namespace rendering
} // namespace cardinal