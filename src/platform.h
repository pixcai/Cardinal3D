// This file is part of Cardinal3D.
// Copyleft 2024, pixcai and the Cardinal3D contributors. All wrongs reserved.

#pragma once

#include "common.h"

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

namespace cardinal {

class Application;

class Platform {
public:
    Platform(std::string_view title, glm::ivec2 dimension);
    ~Platform();

    int Run(Application &application);

    glm::ivec2 GetWindowSize() const;
    glm::ivec2 GetDrawableSize() const;

    glm::ivec2 Scale(glm::ivec2 position);

private:
    void BeginFrame();
    void EndFrame();

    SDL_Window *m_window = nullptr;
    SDL_GLContext m_context = nullptr;
};

} // namespace cardinal
