// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#include "rendering/scene_object.h"
#include "rendering/renderer.h"
#include <vector>

namespace cardinal {
namespace rendering {

static size_t kNextID = 0;
static std::vector<size_t> kFreeIDs{};

SceneObjectBase::SceneObjectBase() : m_id(++kNextID) {}

SceneObjectBase::~SceneObjectBase() {
    --kNextID;
}

size_t SceneObjectBase::GetID() noexcept {
    return m_id;
}

size_t SceneObjectBase::GetID() const noexcept {
    return m_id;
}

template <typename Tp>
SceneObject<Tp>::SceneObject(Tp &&base) : m_base(std::move(base)) {}

template <typename Tp>
size_t SceneObject<Tp>::GetID() noexcept {
    return m_base.GetID();
}

template <typename Tp>
size_t SceneObject<Tp>::GetID() const noexcept {
    return m_base.GetID();
}

template <typename Tp>
void SceneObject<Tp>::Render(Renderer &renderer, Camera &camera) {
    renderer.Render(m_base, camera);
}

} // namespace rendering
} // namespace cardinal
