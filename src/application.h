#pragma once

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

#include "gui/manager.h"
#include "rendering/renderer.h"

namespace cardinal {

class Platform;

class Application {
  public:
    Application(Platform *platform = nullptr);
    ~Application();

  private:
    friend class Platform;

    void Render();
    void ProcessEvent(const SDL_Event &event);

    Platform *platform_;
    gui::Manager gui_;
    rendering::Scene scene_;
    rendering::Renderer renderer_;
};

}; // namespace cardinal