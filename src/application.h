#pragma once

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

#include "gui/manager.h"

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

    Platform *m_platform;
    gui::Manager m_gui;
    rendering::Scene m_scene;
};

}; // namespace cardinal