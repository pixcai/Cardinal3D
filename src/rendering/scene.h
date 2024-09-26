// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "common.h"
#include "scene_object.h"
#include <functional>
#include <map>
#include <variant>

namespace cardinal {
namespace rendering {

class Camera;

class SceneItem {
public:
    SceneItem() = default;
    SceneItem(SceneObject &&object);
    SceneItem(const SceneItem &other) = delete;
    SceneItem(SceneItem &&other);

    SceneItem &operator=(const SceneItem &other) = delete;
    SceneItem &operator=(SceneItem &&other);

    void Render(const glm::mat4 &view);

private:
    std::variant<SceneObject> m_data;
};

class Scene {
public:
    Scene(SceneID start);
    ~Scene() = default;

    std::string Load(const std::string &file);
    void Clear();
    SceneID Add(SceneObject &&object);

    void ForEach(std::function<void(SceneItem &item)> callback);
    void ForEach(std::function<void(const SceneItem &item)> callback) const;

private:
    std::map<SceneID, SceneItem> m_items;
    SceneID m_first_id, m_next_id;
};

} // namespace rendering
} // namespace cardinal
