#include <imgui.h>
#include <imgui_impl_sdl2.h>

#include "application.h"

namespace cardinal {

Application::Application() : gui_({}) {}

Application::~Application() {}

void Application::Run() {
    SDL_Window *window = platform_.GetWindow();
    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE &&
                event.window.windowID == SDL_GetWindowID(window)) {
                running = false;
            }
        }
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
            continue;
        }
        platform_.BeginFrame();
        gui_.Render(scene_);
        platform_.EndFrame();
    }
}

} // namespace cardinal
