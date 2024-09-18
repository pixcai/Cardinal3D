#pragma once

#include <glm/glm.hpp>

#include "mesh.h"

namespace cardinal {
namespace rendering {

using SceneID = unsigned int;

class SceneObject {
  public:
    SceneObject() = default;
    SceneObject(SceneID id, Mesh &&mesh);
    SceneObject(const SceneObject &other) = delete;
    SceneObject(SceneObject &&other) = default;
    ~SceneObject() = default;

    void operator=(const SceneObject &other) = delete;
    SceneObject &operator=(SceneObject &&other) = default;

    SceneID GetID() const;

    void Render(const glm::mat4 &view);

    void SetMeshDirty();

  private:
    SceneID id_ = 0;
    mutable Mesh mesh_;
    mutable bool mesh_dirty_ = false;
};

} // namespace rendering
} // namespace cardinal