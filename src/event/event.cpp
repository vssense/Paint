#include "event.hpp"

bool Event::PollEvent()
{
    SDL_Event event;
    if (!SDL_PollEvent(&event))
    {
        return false;
    }

    switch (event.type)
    {
        case SDL_QUIT:
        {
            type_ = Quit;
            break;
        }
        case SDL_KEYDOWN:
        {
            type_ = KeyDown;
            value_.scancode = event.key.keysym.scancode;
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            type_ = MouseClick;
            value_.coordinates = Vec2<uint32_t>(event.button.x, event.button.y);
            break;
        }
        default:
        {
            return false;
        }
    }

    return true;
}