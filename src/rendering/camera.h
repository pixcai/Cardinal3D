// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "common.h"
#include <glm/gtc/quaternion.hpp>

namespace cardinal {
namespace rendering {

enum class CameraControl {
    kNone,
    kMovement,
    kRotation,
};

class Camera {
public:
    Camera(glm::ivec2 dimension);

    glm::mat4 &GetViewMatrix();
    const glm::mat4 &GetViewMatrix() const;

    glm::mat4 &GetProjectionMatrix();
    const glm::mat4 &GetProjectionMatrix() const;

    glm::vec3 GetDirection();
    glm::vec3 GetDirection() const;

    void LookAt(glm::vec3 target);

    void SetOffset(glm::vec2 offset);
    void SetRotate(glm::vec2 offset);
    void SetScale(float factor);

    void Reset();

private:
    void UpdatePosition();

    float m_fov, m_aspect_ratio, m_near, m_far, m_radius;
    glm::vec3 m_looking_at, m_position;
    glm::quat m_rotation;
    glm::mat4 m_view_matrix, m_view_matrix_inverse;
    glm::mat4 m_projection_matrix;
};

} // namespace rendering
} // namespace cardinal
