// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "rendering/scene_object.h"

namespace cardinal {
namespace rendering {

struct Vertex {
    std::vector<float> position;
    std::vector<float> normal;
    GLuint index;
};

struct SceneMeshData {
    static inline constexpr GLsizei kSizeOfVertex = sizeof(Vertex);
    static inline constexpr GLsizei kSizeOfIndex = sizeof(GLuint);

    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
};

class SceneMeshBase : public SceneObjectBase {
public:
    SceneMeshBase(SceneMeshData &&data);
    virtual ~SceneMeshBase();

    SceneMeshBase(const SceneMeshBase &other) = delete;
    void operator=(const SceneMeshBase &other) = delete;

    SceneMeshBase(SceneMeshBase &&other);
    void operator=(SceneMeshBase &&other);

    void Render() override;
    void ReCreate(SceneMeshData &&data);

private:
    void Create();
    void Destroy();
    void Update();

    bool m_dirty = true;
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;

    SceneMeshData m_data;
};

} // namespace rendering
} // namespace cardinal
