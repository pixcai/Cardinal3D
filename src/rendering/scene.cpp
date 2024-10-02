// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#include "rendering/scene.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

namespace cardinal {
namespace rendering {

std::string Scene::Load(const std::string &file) {
    Assimp::Importer importer;
    unsigned int flags = aiProcess_OptimizeMeshes | aiProcess_FindInvalidData |
                         aiProcess_FindInstances | aiProcess_FindDegenerates |
                         aiProcess_Triangulate;

    const aiScene *scene = importer.ReadFile(file, flags);

    return std::string(scene->mName.C_Str());
}

void Scene::Clear() {
    m_objects.clear();
}

template <typename Tp>
void Scene::Add(Tp &&object) {
    m_objects[object.GetID()] = std::move(object);
}

void Scene::ForEach(std::function<void(SceneObjectBase &objects)> callback) {
    for (auto &object: m_objects) {
        callback(object.second);
    }
}

void Scene::ForEach(
    std::function<void(const SceneObjectBase &objects)> callback) const {
    for (const auto &object: m_objects) {
        callback(object.second);
    }
}

} // namespace rendering
} // namespace cardinal
