#pragma once

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

#include "gui/manager.h"
#include "platform.h"

namespace cardinal {

class Application {
  public:
    Application();
    ~Application();

    void Run();

  private:
    Platform platform_;
    gui::Manager gui_;
    rendering::Scene scene_;
};

}; // namespace cardinal