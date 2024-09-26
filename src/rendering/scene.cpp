// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#include "scene.h"
#include "utility/overload.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace cardinal {
namespace rendering {

SceneItem::SceneItem(SceneObject &&object) : m_data(std::move(object)) {}

SceneItem::SceneItem(SceneItem &&other) : m_data(std::move(other.m_data)) {}

SceneItem &SceneItem::operator=(SceneItem &&other) {
    m_data = std::move(other.m_data);
    return *this;
}

void SceneItem::Render(const glm::mat4 &view) {
    std::visit(utility::Overload{[&](SceneObject &object) {
                   object.Render(view);
               }},
               m_data);
}

Scene::Scene(SceneID start) : m_first_id(start), m_next_id(start) {}

std::string Scene::Load(const std::string &file) {
    Assimp::Importer importer;
    unsigned int flags = aiProcess_OptimizeMeshes | aiProcess_FindInvalidData |
                         aiProcess_FindInstances | aiProcess_FindDegenerates |
                         aiProcess_Triangulate;

    const aiScene *scene = importer.ReadFile(file, flags);

    return std::string(scene->mName.C_Str());
}

void Scene::Clear() {
    m_next_id = m_first_id;
    m_items.clear();
}

SceneID Scene::Add(SceneObject &&object) {
    SceneID id = object.GetID();

    assert(m_items.find(id) == m_items.end());
    m_items.emplace(std::make_pair(id, std::move(object)));
    return id;
}

void Scene::ForEach(std::function<void(SceneItem &item)> callback) {
    for (auto &item: m_items) {
        callback(item.second);
    }
}

void Scene::ForEach(std::function<void(const SceneItem &item)> callback) const {
    for (const auto &item: m_items) {
        callback(item.second);
    }
}

} // namespace rendering
} // namespace cardinal
