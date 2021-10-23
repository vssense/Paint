#ifndef _WINDOW_H_INCLUDED
#define _WINDOW_H_INCLUDED

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include <SDL.h>

const size_t kWindowHeight = 768;
const size_t kWindowWidth  = 1024;
const size_t kTitleSize    = 10;

class Window
{
public:
    Window(size_t width = kWindowWidth, size_t height = kWindowHeight);
    ~Window();
    void SetTitleFPS(int fps);
    SDL_Window* GetWindow();

private:
    SDL_Window* window_;
};

#endif /* _WINDOW_H_INCLUDED */