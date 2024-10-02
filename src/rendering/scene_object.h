// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "rendering/camera.h"
#include "rendering/rendering.h"
#include <type_traits>

namespace cardinal {
namespace rendering {

class SceneObjectBase {
public:
    SceneObjectBase();
    virtual ~SceneObjectBase();

    size_t GetID() noexcept;
    size_t GetID() const noexcept;

    virtual void Render() {}

protected:
    size_t m_id;
};

template <typename Tp>
class SceneObject final {
public:
    template <typename Up>
    static constexpr bool is = std::is_base_of_v<Tp, Up>;

public:
    SceneObject() = default;
    SceneObject(SceneObject &&other) = default;
    SceneObject(Tp &&base);

    size_t GetID() noexcept;
    size_t GetID() const noexcept;

    void Render(Renderer &renderer, Camera &camera);

private:
    Tp m_base;
};

} // namespace rendering
} // namespace cardinal
