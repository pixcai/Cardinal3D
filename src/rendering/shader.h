#pragma once

#include <string>
#include <string_view>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace cardinal {
namespace rendering {

class Shader {
  public:
    struct Presets {
        static const std::string_view mesh_vertex, mesh_fragment;
    };

    Shader(std::string_view vertex, std::string_view fragment);
    Shader(const Shader &other) = delete;
    Shader(Shader &&other);
    ~Shader();

    void operator=(const Shader &other) = delete;
    void operator=(Shader &&other);

    void Bind() const;
    void Load(std::string_view vertex, std::string_view fragment);

    void Uniform(const std::string &name, const glm::mat4 &matrix) const;
    void Uniform(const std::string &name, const glm::vec3 &vector) const;
    void Uniform(const std::string &name, GLuint value) const;

  private:
    bool Validate(GLuint shader) const;
    void Destroy();

    GLuint program_ = 0, vertex_ = 0, fragment_ = 0;
};

} // namespace rendering
} // namespace cardinal