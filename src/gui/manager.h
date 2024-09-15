#pragma once

#include <glm/vec2.hpp>

namespace cardinal {
namespace gui {

class Manager {
  public:
    Manager(const glm::vec2 dimension);
    ~Manager();

  private:
    glm::vec2 dimension_;
};

} // namespace gui
} // namespace cardinal