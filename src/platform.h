#pragma once

#include <SDL2/SDL.h>

namespace cardinal {

class Platform {
  public:
    Platform();
    ~Platform();

    void BeginFrame();
    void EndFrame();

  private:
    SDL_Window *window_ = nullptr;
    SDL_GLContext context_ = nullptr;
};

} // namespace cardinal