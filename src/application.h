#pragma once

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

#include "platform.h"

namespace cardinal {

class Application {
  public:
    Application();
    ~Application();

    void Run();

  private:
    Platform platform_;
};

}; // namespace cardinal