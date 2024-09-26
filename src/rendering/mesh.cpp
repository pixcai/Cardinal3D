// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#include "mesh.h"

namespace cardinal {
namespace rendering {

Mesh::Mesh() {
    Create();
}

Mesh::Mesh(std::vector<Vertex> &&vertices, std::vector<Index> &&indices) {
    Create();
    ReCreate(std::move(vertices), std::move(indices));
}

Mesh::Mesh(Mesh &&other) {
    dirty_ = other.dirty_;
    other.dirty_ = true;
    element_count_ = other.element_count_;
    other.element_count_ = 0;
    vao_ = other.vao_;
    vbo_ = other.vbo_;
    ebo_ = other.ebo_;
    other.vao_ = other.vbo_ = other.ebo_ = 0;
    vertices_ = std::move(other.vertices_);
    indices_ = std::move(other.indices_);
}

Mesh::~Mesh() {
    Destroy();
}

void Mesh::operator=(Mesh &&other) {
    Destroy();
    dirty_ = other.dirty_;
    other.dirty_ = true;
    element_count_ = other.element_count_;
    other.element_count_ = 0;
    vao_ = other.vao_;
    vbo_ = other.vbo_;
    ebo_ = other.ebo_;
    other.vao_ = other.vbo_ = other.ebo_ = 0;
    vertices_ = std::move(other.vertices_);
    indices_ = std::move(other.indices_);
}

void Mesh::Render() {
    if (dirty_) {
        Update();
    }
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, element_count_, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::ReCreate(std::vector<Vertex> &&vertices,
                    std::vector<Index> &&indices) {
    dirty_ = true;
    vertices_ = std::move(vertices);
    indices_ = std::move(indices);
    element_count_ = static_cast<GLsizei>(indices_.size());
}

void Mesh::Create() {
    glCreateVertexArrays(1, &vao_);
    glCreateBuffers(1, &vbo_);
    glCreateBuffers(1, &ebo_);

    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<GLvoid *>(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, sizeof(Vertex),
                           reinterpret_cast<GLvoid *>(2 * sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBindVertexArray(0);
}

void Mesh::Destroy() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glDeleteBuffers(1, &ebo_);
    vao_ = vbo_ = ebo_ = 0;
}

void Mesh::Update() {
    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices_.size(),
                 vertices_.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index) * indices_.size(),
                 indices_.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    dirty_ = false;
}

} // namespace rendering
} // namespace cardinal
