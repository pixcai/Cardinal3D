#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace cardinal {
namespace rendering {

class Camera {
  public:
    Camera(const glm::ivec2 dimension);

    const glm::mat4 &GetViewMatrix() const;
    const glm::mat4 &GetProjectionMatrix() const;

    void LookAt(glm::vec3 center, glm::vec3 position);

    void Reset();

  private:
    void UpdatePosition();

    float m_fov, m_aspect_ratio, m_near, m_far, m_radius;
    glm::vec3 m_looking_at, m_position, m_up;
    glm::quat m_rotation;
    glm::mat4 m_view_matrix, m_inv_view_matrix;
    glm::mat4 m_projection_matrix, m_inv_projection_matrix;
};

} // namespace rendering
} // namespace cardinal