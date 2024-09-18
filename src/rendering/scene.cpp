#include <cassert>
#include <utility>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "scene.h"
#include "util/util.h"

namespace cardinal {
namespace rendering {

SceneItem::SceneItem(SceneObject &&object) : data_(std::move(object)) {}

SceneItem::SceneItem(SceneItem &&other) : data_(std::move(other.data_)) {}

SceneItem &SceneItem::operator=(SceneItem &&other) {
    data_ = std::move(other.data_);
    return *this;
}

void SceneItem::Render(const glm::mat4 &view) {
    std::visit(overloaded{[&](SceneObject &object) { object.Render(view); }}, data_);
}

Scene::Scene(SceneID start) : first_id_(start), next_id_(start) {}

std::string Scene::Load(const std::string &file) {
    Assimp::Importer importer;
    unsigned int flags = aiProcess_OptimizeMeshes | aiProcess_FindInvalidData | aiProcess_FindInstances |
                         aiProcess_FindDegenerates | aiProcess_Triangulate;

    const aiScene *scene = importer.ReadFile(file, flags);

    return std::string(scene->mName.C_Str());
}

void Scene::Clear() {
    next_id_ = first_id_;
    items_.clear();
}

SceneID Scene::Add(SceneObject &&object) {
    SceneID id = object.GetID();

    assert(items_.find(id) == items_.end());
    items_.emplace(std::make_pair(id, std::move(object)));
    return id;
}

void Scene::ForEach(std::function<void(SceneItem &item)> callback) {
    for (auto &item : items_) {
        callback(item.second);
    }
}

void Scene::ForEach(std::function<void(const SceneItem &item)> callback) const {
    for (const auto &item : items_) {
        callback(item.second);
    }
}

} // namespace rendering
} // namespace cardinal
