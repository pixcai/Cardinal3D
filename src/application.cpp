// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#include "application.h"
#include "rendering/renderer.h"

namespace cardinal {

Application::Application(Settings settings)
    : m_platform(settings.title, settings.dimension),
      m_gui(m_platform.GetWindowSize()),
      m_scene(0),
      m_camera(m_platform.GetDrawableSize()) {
    Renderer::Setup(m_platform.GetDrawableSize());
    Renderer::Get().SetProjectionMatrix(m_camera.GetProjectionMatrix());

    Mesh box{
        {
            {{-1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, 0},
            {{1.0f, -1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, 1},
            {{1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, 2},
            {{-1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, 3},

            {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, 4},
            {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, 5},
            {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, 6},
            {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, -1.0f}, 7},
        },
        {0, 1, 2, 2, 3, 0, 4, 7, 6, 6, 5, 4, 3, 2, 6, 6, 7, 3,
         0, 4, 5, 5, 1, 0, 4, 0, 3, 3, 7, 4, 5, 6, 2, 2, 1, 5},
    };
    m_scene.Add(SceneObject{1, std::move(box)});
}

Application::~Application() {
    Renderer::Shutdown();
}

int Application::Run() {
    return m_platform.Run(*this);
}

void Application::Render() {
    Renderer &renderer = Renderer::Get();

    renderer.BeginRender();
    m_gui.Render(m_scene, m_camera);
    renderer.EndRender();
}

void Application::ProcessEvent(const SDL_Event &event) {
    ImGuiIO &io = ImGui::GetIO();

    switch (event.type) {
    case SDL_MOUSEMOTION: {
        glm::vec2 mouse_offset{event.motion.xrel, event.motion.yrel};

        if (m_camera_control == CameraControl::kRotation) {
            m_camera.SetRotate(mouse_offset);
        } else if (m_camera_control == CameraControl::kMovement) {
            m_camera.SetOffset(mouse_offset);
        }
        break;
    }
    case SDL_MOUSEBUTTONDOWN: {
        if (io.WantCaptureMouse) {
            break;
        }
        if (event.button.button == SDL_BUTTON_LEFT) {
            m_camera_control = CameraControl::kRotation;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
            m_camera_control = CameraControl::kMovement;
        }
        break;
    }
    case SDL_MOUSEBUTTONUP: {
        m_camera_control = CameraControl::kNone;
        break;
    }
    case SDL_MOUSEWHEEL: {
        if (io.WantCaptureMouse) {
            break;
        }
        m_camera.SetScale(static_cast<float>(event.wheel.y));
        break;
    }
    default: break;
    }
}

} // namespace cardinal
