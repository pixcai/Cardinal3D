// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "common.h"

namespace cardinal {
namespace rendering {

class Renderer;

class Scene;

template <typename Tp>
class SceneObject;

class SceneMeshBase;
using SceneMesh = SceneObject<SceneMeshBase>;

} // namespace rendering
} // namespace cardinal
