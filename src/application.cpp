#include "application.h"

namespace cardinal {

Application::Application() {}

Application::~Application() {}

void Application::Run() {
    bool running = true;

    while (running) {
        SDL_Event e;

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }
        }
        platform_.BeginFrame();
        platform_.EndFrame();
    }
}

} // namespace cardinal
