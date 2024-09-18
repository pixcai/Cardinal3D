#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

namespace cardinal {
namespace rendering {

Camera::Camera(const glm::ivec2 dimension) {
    Reset();
    m_aspect_ratio = static_cast<float>(dimension.x) / static_cast<float>(dimension.y);
}

const glm::mat4 &Camera::GetViewMatrix() const { return m_view_matrix; }

const glm::mat4 &Camera::GetProjectionMatrix() const { return m_projection_matrix; }

void Camera::LookAt(glm::vec3 center, glm::vec3 position) {
    m_looking_at = center;
    m_position = position;
    m_radius = glm::length(m_position - m_looking_at);
    UpdatePosition();
}

void Camera::Reset() {
    m_fov = 75.0f;
    m_aspect_ratio = 4.0f / 3.0f;
    m_radius = 50.0f;
    m_near = 0.1f;
    m_far = 100.0f;
    m_looking_at = glm::vec3();
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_rotation = glm::quat();
    UpdatePosition();
}

void Camera::UpdatePosition() {
    m_position = m_rotation * glm::vec3(0.0f, 0.0f, 1.0f);
    m_position = m_looking_at + m_radius * glm::normalize(m_position);
    m_inv_view_matrix = glm::translate(glm::mat4(1.0f), m_position) * glm::mat4_cast(m_rotation);
    m_view_matrix = glm::inverse(m_inv_view_matrix);
    m_projection_matrix = glm::perspective(m_fov, m_aspect_ratio, m_near, m_far);
    m_inv_projection_matrix = glm::inverse(m_projection_matrix);
}

} // namespace rendering
} // namespace cardinal