#include "application.h"
#include "platform.h"

namespace cardinal {

Application::Application(Platform *platform)
    : platform_(platform), gui_(platform->GetWindowSize()), renderer_(platform->GetDrawableSize()) {}

Application::~Application() {}

void Application::Render() {
    renderer_.BeginRender();
    gui_.Render(scene_);
    renderer_.EndRender();
}

void Application::ProcessEvent(const SDL_Event &event) {}

} // namespace cardinal
