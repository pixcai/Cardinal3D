#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

namespace cardinal {
namespace rendering {

Shader::Shader(std::string_view vertex, std::string_view fragment) { Load(vertex, fragment); }

Shader::Shader(Shader &&other) {
    program_ = other.program_;
    vertex_ = other.vertex_;
    fragment_ = other.fragment_;
    other.program_ = other.vertex_ = other.fragment_ = 0;
}

Shader::~Shader() { Destroy(); }

void Shader::operator=(Shader &&other) {
    Destroy();
    program_ = other.program_;
    vertex_ = other.vertex_;
    fragment_ = other.fragment_;
    other.program_ = other.vertex_ = other.fragment_ = 0;
}

void Shader::Bind() const { glUseProgram(program_); }

void Shader::Load(std::string_view vertex, std::string_view fragment) {
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    fragment_ = glCreateShader(GL_FRAGMENT_SHADER);

    const char *source = vertex.data();
    glShaderSource(vertex_, 1, &source, nullptr);
    glCompileShader(vertex_);
    if (!Validate(vertex_)) {
        Destroy();
        return;
    }

    source = fragment.data();
    glShaderSource(fragment_, 1, &source, nullptr);
    glCompileShader(fragment_);
    if (!Validate(fragment_)) {
        Destroy();
        return;
    }

    program_ = glCreateProgram();
    glAttachShader(program_, vertex_);
    glAttachShader(program_, fragment_);
    glLinkProgram(program_);
}

void Shader::Uniform(const std::string &name, const glm::mat4 &matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(program_, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::Uniform(const std::string &name, const glm::vec3 &vector) const {
    glUniform3fv(glGetUniformLocation(program_, name.c_str()), 1, glm::value_ptr(vector));
}

void Shader::Uniform(const std::string &name, GLuint value) const {
    glUniform1ui(glGetUniformLocation(program_, name.c_str()), value);
}

bool Shader::Validate(GLuint shader) const {
    GLint success = 0;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        throw std::runtime_error("Failed to compile shader.");
    }
    return success != 0;
}

void Shader::Destroy() {
    glUseProgram(0);
    glDeleteShader(vertex_);
    glDeleteShader(fragment_);
    glDeleteProgram(program_);
    program_ = vertex_ = fragment_ = 0;
}

const std::string_view Shader::Presets::mesh_vertex = R"(
#version 460 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in uint v_id;

uniform mat4 u_mvp;

void main() {
    gl_Position = u_mvp * vec4(v_position, 1.0);
})";

const std::string_view Shader::Presets::mesh_fragment = R"(
#version 460 core

layout(location = 0) out vec4 out_color;

uniform vec3 u_color;

void main() {
    out_color = vec4(u_color, 1.0);
})";

} // namespace rendering
} // namespace cardinal