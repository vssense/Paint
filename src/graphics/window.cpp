#include "window.hpp"

static const char* kDefaultTitle = "Paint";

Window::Window(size_t width, size_t height)
{
    window_ = SDL_CreateWindow(kDefaultTitle, SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, width, height, 0);

    assert(window_ && "Couldn't create window\n");
}

Window::~Window()
{
    assert(window_);

    SDL_DestroyWindow(window_);
}

SDL_Window* Window::GetWindow()
{
    return window_;
}

void Window::SetTitleFPS(int fps)
{
    assert(window_);

    char* title = (char*)calloc(kTitleSize, sizeof(char));
    assert(title);

    snprintf(title, kTitleSize, "FPS %d", fps);
    SDL_SetWindowTitle(window_, title);

    free(title);
}