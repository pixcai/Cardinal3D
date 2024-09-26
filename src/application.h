// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "common.h"
#include "gui/manager.h"
#include "platform.h"
#include "rendering/camera.h"

namespace cardinal {

using namespace gui;
using namespace rendering;

struct Settings {
    std::string title = "Cardinal3D";
    glm::ivec2 dimension{1000, 640};
};

class Application {
public:
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
