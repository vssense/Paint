#include "event.hpp"

bool Event::PollEvent()
{
    static bool button_pressed = false; 
    SDL_Event event;

    if (!SDL_PollEvent(&event))
    {
        return false;
    }

    switch (event.type)
    {
        case SDL_QUIT:
        {
            type_ = kQuit;
            break;
        }
        case SDL_KEYDOWN:
        {
            type_ = kKeyDown;
            value_.scancode = event.key.keysym.scancode;
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            button_pressed = true;
            type_ = kMouseButtonPress;
            value_.coordinates = Vec2<uint32_t>(event.button.x, event.button.y);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            button_pressed = false;
            type_ = kMouseButtonRelease;
            value_.coordinates = Vec2<uint32_t>(event.button.x, event.button.y);
            break;
        }
        case SDL_MOUSEMOTION:
        {
            if (!button_pressed)
            {
                return PollEvent();
            }

            type_ = kMouseMotion;
            value_.motion.start = Vec2<uint32_t>(event.motion.x - event.motion.xrel,
                                                 event.motion.y - event.motion.yrel);
            value_.motion.d     = Vec2<int32_t> (event.motion.xrel, event.motion.yrel);
            break;
        }
        default:
        {
            return false;
        }
    }

    return true;
}