#include <utility>

#include "application.h"
#include "platform.h"
#include "rendering/renderer.h"

namespace cardinal {

Application::Application(Platform *platform) : platform_(platform), gui_(platform->GetWindowSize()), scene_(0) {
    rendering::Renderer::Setup(platform->GetDrawableSize());

    rendering::Mesh box{
        {
            {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, 0},
            {{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, 1},
            {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, 2},
            {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, 3},
        },
        {0, 1, 2, 2, 3, 0},
    };
    scene_.Add(rendering::SceneObject{1, std::move(box)});
}

Application::~Application() { rendering::Renderer::Shutdown(); }

void Application::Render() {
    rendering::Renderer &renderer = rendering::Renderer::Get();

    renderer.BeginRender();
    gui_.Render(scene_);
    renderer.EndRender();
}

void Application::ProcessEvent(const SDL_Event &event) {}

} // namespace cardinal
