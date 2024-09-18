#pragma once

#include <functional>
#include <map>
#include <string>
#include <variant>

#include <glm/glm.hpp>

#include "scene_object.h"

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
    std::variant<SceneObject> data_;
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
    std::map<SceneID, SceneItem> items_;
    SceneID first_id_, next_id_;
};

} // namespace rendering
} // namespace cardinal