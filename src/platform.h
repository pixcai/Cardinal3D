#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace cardinal {

class Application;

class Platform {
  public:
    Platform(const std::string &title, glm::ivec2 dimension);
    ~Platform();

    int Run(Application &app);

    glm::ivec2 GetWindowSize() const;
    glm::ivec2 GetDrawableSize() const;

  private:
    void BeginFrame();
    void EndFrame();

    SDL_Window *window_ = nullptr;
    SDL_GLContext context_ = nullptr;
};

} // namespace cardinal