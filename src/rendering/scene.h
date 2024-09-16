#pragma once

#include <string>

namespace cardinal {
namespace rendering {

class Scene {
  public:
    Scene();
    ~Scene();

    std::string Load(const std::string &file);
};

} // namespace rendering
} // namespace cardinal