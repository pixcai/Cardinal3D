#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "scene.h"

namespace cardinal {
namespace rendering {

Scene::Scene() {}
Scene::~Scene() {}

std::string Scene::Load(const std::string &file) {
    Assimp::Importer importer;
    unsigned int flags = aiProcess_OptimizeMeshes | aiProcess_FindInvalidData | aiProcess_FindInstances |
                         aiProcess_FindDegenerates | aiProcess_Triangulate;

    const aiScene *scene = importer.ReadFile(file, flags);

    return std::string(scene->mName.C_Str());
}

} // namespace rendering
} // namespace cardinal
