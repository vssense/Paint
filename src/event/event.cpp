#include "event.hpp"

std::queue<Event> Event::queue_;

bool Event::PollEvent()
{
    while (PollSDLEvent());

    if (queue_.empty())
    {
        return false;
    }

    *this = queue_.front();
    queue_.pop();
    return true;
}

bool Event::PollSDLEvent()
{
    static bool mouse_button_pressed = false; 
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
            mouse_button_pressed = true;
            type_ = kMouseButtonPress;
            value_.coordinates = Vec2<uint32_t>(event.button.x, event.button.y);
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            mouse_button_pressed = false;
            type_ = kMouseButtonRelease;
            value_.coordinates = Vec2<uint32_t>(event.button.x, event.button.y);
            break;
        }
        case SDL_MOUSEMOTION:
        {
            type_ = kMouseHover;
            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);
            value_.coordinates.x = static_cast<uint32_t>(x);
            value_.coordinates.y = static_cast<uint32_t>(y);
            queue_.push(*this);
            if (!mouse_button_pressed)
            {
                return true;
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

    queue_.push(*this);
    return true;
}