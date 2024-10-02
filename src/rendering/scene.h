// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "rendering/rendering.h"
#include "rendering/scene_object.h"
#include <functional>
#include <unordered_map>

namespace cardinal {
namespace rendering {

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    std::string Load(const std::string &file);
    void Clear();

    template <typename Tp>
    void Add(Tp &&object);

    void ForEach(std::function<void(SceneObjectBase &object)> callback);

    void
    ForEach(std::function<void(const SceneObjectBase &object)> callback) const;

private:
    std::unordered_map<size_t, SceneObjectBase> m_objects{};
};

} // namespace rendering
} // namespace cardinal
