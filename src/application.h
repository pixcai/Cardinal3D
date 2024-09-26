#pragma once

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "gui/manager.h"
#include "rendering/camera.h"

namespace cardinal {

using namespace gui;
using namespace rendering;

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
    Manager m_gui;
    Scene m_scene;

    CameraControl m_camera_control = CameraControl::kNone;
    Camera m_camera;
};

}; // namespace cardinal