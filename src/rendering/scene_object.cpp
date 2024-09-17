#include <utility>

#include <glm/glm.hpp>

#include "renderer.h"
#include "scene_object.h"

namespace cardinal {
namespace rendering {

SceneObject::SceneObject(SceneID id, Mesh &&mesh) : id_(id), mesh_(std::move(mesh)) {}

SceneID SceneObject::GetID() const { return id_; }

void SceneObject::Render() { Renderer::Get().Render(mesh_, {id_, glm::vec3(1.0f), glm::mat4(1.0f)}); }

void SceneObject::SetMeshDirty() { mesh_dirty_ = true; }

} // namespace rendering
} // namespace cardinal