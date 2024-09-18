#include <utility>

#include "application.h"
#include "platform.h"
#include "rendering/renderer.h"

namespace cardinal {

Application::Application(Platform *platform) : m_platform(platform), m_gui(platform->GetWindowSize()), m_scene(0) {
    rendering::Renderer::Setup(platform->GetDrawableSize());

    rendering::Mesh box{
        {
            {{-5.0f, -5.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, 0},
            {{5.0f, -5.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, 1},
            {{5.0f, 5.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, 2},
            {{-5.0f, 5.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, 3},
        },
        {0, 1, 2, 2, 3, 0},
    };
    m_scene.Add(rendering::SceneObject{1, std::move(box)});
}

Application::~Application() { rendering::Renderer::Shutdown(); }

void Application::Render() {
    rendering::Renderer &renderer = rendering::Renderer::Get();

    renderer.BeginRender();
    m_gui.Render(m_scene, renderer.GetCamera());
    renderer.EndRender();
}

void Application::ProcessEvent(const SDL_Event &event) {}

} // namespace cardinal
