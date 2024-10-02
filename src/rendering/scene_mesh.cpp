// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#include "rendering/scene_mesh.h"

namespace cardinal {
namespace rendering {

SceneMeshBase::SceneMeshBase(SceneMeshData &&data) : m_data(std::move(data)) {
    Create();
    ReCreate(std::move(m_data));
}

SceneMeshBase::SceneMeshBase(SceneMeshBase &&other)
    : m_data(std::move(other.m_data)) {
    m_dirty = other.m_dirty;
    other.m_dirty = true;
    m_vao = other.m_vao;
    m_vbo = other.m_vbo;
    m_ebo = other.m_ebo;
    other.m_vao = other.m_vbo = other.m_ebo = 0;
}

SceneMeshBase::~SceneMeshBase() {
    Destroy();
}

void SceneMeshBase::operator=(SceneMeshBase &&other) {
    Destroy();
    m_dirty = other.m_dirty;
    other.m_dirty = true;
    m_vao = other.m_vao;
    m_vbo = other.m_vbo;
    m_ebo = other.m_ebo;
    other.m_vao = other.m_vbo = other.m_ebo = 0;
}

void SceneMeshBase::Render() {
    if (m_dirty) {
        Update();
    }
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_data.indices.size(), GL_UNSIGNED_INT,
                   nullptr);
    glBindVertexArray(0);
}

void SceneMeshBase::ReCreate(SceneMeshData &&data) {
    m_dirty = true;
    m_data = std::move(data);
}

void SceneMeshBase::Create() {
    glCreateVertexArrays(1, &m_vao);
    glCreateBuffers(1, &m_vbo);
    glCreateBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          SceneMeshData::kSizeOfVertex, nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          SceneMeshData::kSizeOfVertex,
                          reinterpret_cast<GLvoid *>(sizeof(glm::vec3)));
    glEnableVertexAttribArray(1);

    glVertexAttribIPointer(2, 1, GL_UNSIGNED_INT, SceneMeshData::kSizeOfVertex,
                           reinterpret_cast<GLvoid *>(2 * sizeof(glm::vec3)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBindVertexArray(0);
}

void SceneMeshBase::Destroy() {
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    m_vao = m_vbo = m_ebo = 0;
}

void SceneMeshBase::Update() {
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 SceneMeshData::kSizeOfVertex * m_data.vertices.size(),
                 m_data.vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 SceneMeshData::kSizeOfIndex * m_data.indices.size(),
                 m_data.indices.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    m_dirty = false;
}

} // namespace rendering
} // namespace cardinal
