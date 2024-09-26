#pragma once

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include "gui/manager.h"
#include "platform.h"
#include "rendering/camera.h"

namespace cardinal {

using namespace gui;
using namespace rendering;

class Application {
  public:
    struct Settings {
        std::string title;
        glm::ivec2 dimension;

        Settings() : title("Cardinal3D"), dimension(1000, 640) {}
    };

    Application(Settings settings = {});
    ~Application();

    int Run();

  private:
    friend class Platform;

    void Render();
    void ProcessEvent(const SDL_Event &event);

    Platform m_platform;
    Manager m_gui;
    Scene m_scene;

    CameraControl m_camera_control = CameraControl::kNone;
    Camera m_camera;
};

}; // namespace cardinal