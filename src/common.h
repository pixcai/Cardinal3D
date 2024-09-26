// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

// Frequently used standard library files
#include <cassert>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// OpenGL and 3D math are used in a lot of places
// so we make it part of the common header file
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cardinal {

// Since GLM doesn't define these unit vectors
// we need to define them separately
inline constexpr glm::vec3 kAxisX{1.0f, 0.0f, 0.0f};
inline constexpr glm::vec3 kAxisY{0.0f, 1.0f, 0.0f};
inline constexpr glm::vec3 kAxisZ{0.0f, 0.0f, 1.0f};

} // namespace cardinal
