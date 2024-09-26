#pragma once

#include <string_view>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace cardinal {
namespace rendering {

struct ShaderPresets {
    static const std::string_view kMeshVertex, kMeshFragment;
};

class Shader {
  public:
    Shader(std::string_view vertex, std::string_view fragment);
    Shader(const Shader &other) = delete;
    Shader(Shader &&other);
    ~Shader();

    void operator=(const Shader &other) = delete;
    void operator=(Shader &&other);

    void Bind() const;
    void Load(std::string_view vertex, std::string_view fragment);

    void Uniform(std::string_view name, const glm::mat4 &matrix) const;
    void Uniform(std::string_view name, glm::vec3 vector) const;
    void Uniform(std::string_view name, GLuint value) const;

  private:
    bool Validate(GLuint shader) const;
    void Destroy();

    GLuint program_ = 0, vertex_ = 0, fragment_ = 0;
};

} // namespace rendering
} // namespace cardinal