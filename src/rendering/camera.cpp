#include <utility>

#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

static constexpr glm::vec3 kUnitY{0.0f, 1.0f, 0.0f};
static constexpr glm::vec3 kUnitZ{0.0f, 0.0f, 1.0f};

namespace cardinal {
namespace rendering {

Camera::Camera(glm::ivec2 dimension) {
    Reset();
    m_aspect_ratio = static_cast<float>(dimension.x) / static_cast<float>(dimension.y);
    m_projection_matrix = glm::perspective(m_fov, m_aspect_ratio, m_near, m_far);
}

glm::mat4 &Camera::GetViewMatrix() { return m_view_matrix; }

const glm::mat4 &Camera::GetViewMatrix() const { return m_view_matrix; }

glm::mat4 &Camera::GetProjectionMatrix() { return m_projection_matrix; }

const glm::mat4 &Camera::GetProjectionMatrix() const { return m_projection_matrix; }

glm::vec3 Camera::GetDirection() { return glm::normalize(m_looking_at - m_position); }

glm::vec3 Camera::GetDirection() const { return glm::normalize(m_looking_at - m_position); }

void Camera::LookAt(glm::vec3 target) {
    m_looking_at = target;
    UpdatePosition();
}

void Camera::SetOffset(glm::vec2 offset) {
    glm::vec3 y = m_rotation * kUnitY;
    glm::vec3 z = GetDirection();
    glm::vec3 x = glm::normalize(glm::cross(z, y));

    m_looking_at += x * offset.x * 0.015f - y * offset.y * 0.015f;
    UpdatePosition();
}

void Camera::SetRotate(glm::vec2 offset) {
    float y_offset = offset.x * 0.015f;
    float x_offset = offset.y * 0.015f;

    glm::vec3 y = m_rotation * kUnitY;
    glm::vec3 z = GetDirection();
    glm::vec3 x = glm::normalize(glm::cross(z, y));

    m_rotation = glm::angleAxis(y_offset, kUnitY) * glm::angleAxis(x_offset, x) * m_rotation;
    UpdatePosition();
}

void Camera::SetScale(float factor) {
    m_radius -= factor * 0.25f;
    m_radius = std::max(m_near, std::min(m_radius, m_far));
    UpdatePosition();
}

void Camera::Reset() {
    m_fov = 75.0f;
    m_aspect_ratio = 1.0f;
    m_radius = 10.0f;
    m_near = 0.01f;
    m_far = 1000.0f;
    m_looking_at = glm::vec3();
    m_rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    UpdatePosition();
}

void Camera::UpdatePosition() {
    m_position = m_looking_at + m_rotation * kUnitZ * m_radius;
    m_view_matrix_inverse = glm::translate(glm::mat4(1.0f), m_position) * glm::mat4_cast(m_rotation);
    m_view_matrix = glm::inverse(m_view_matrix_inverse);
}

} // namespace rendering
} // namespace cardinal