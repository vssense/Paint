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
            type_ = kMouseButtonPress;
            value_.coordinates = Vec2<uint32_t>(event.button.x, event.button.y);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            type_ = kMouseButtonRelease;
            value_.coordinates = Vec2<uint32_t>(event.button.x, event.button.y);
            break;
        }
        case SDL_MOUSEMOTION:
        {
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