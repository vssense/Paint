#include "event.hpp"

EventManager* EventManager::instance_ = nullptr;

bool Event::PollEvent()
{
    return EventManager::GetInstance()->PollEvent(this);
}

EventType Event::GetType() const
{
    return type_;
}

const EventValue& Event::GetValue() const
{
    return value_;
}

EventManager* EventManager::GetInstance()
{
    if (instance_ == nullptr)
    {
        instance_ = new EventManager;
        assert(instance_);
    }

    return instance_;
}

EventManager::EventManager() {}

void EventManager::PushEvent(const Event& event)
{
    queue_.push(event);
}

bool EventManager::PollEvent(Event* event)
{
    while (PollSDLEvent());

    if (queue_.empty())
    {
        return false;
    }

    *event = queue_.front();
    queue_.pop();
    return true;
}

bool EventManager::PollSDLEvent()
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
            queue_.push(Event(kQuit));
            break;
        }
        case SDL_KEYDOWN:
        {
            queue_.push(Event(kKeyDown, EventValue(event.key.keysym.scancode)));
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
        {
            mouse_button_pressed = true;
            queue_.push(Event(kMouseButtonPress, EventValue(Vec2<int>(event.button.x, event.button.y))));
            break;
        }
        case SDL_MOUSEBUTTONUP:
        {
            mouse_button_pressed = false;
            queue_.push(Event(kMouseButtonRelease,
                              EventValue(Vec2<int>(event.button.x, event.button.y))));
            queue_.push(Event(kMouseHover,
                              EventValue(Vec2<int>(event.button.x, event.button.y))));
            break;
        }
        case SDL_MOUSEMOTION:
        {
            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);
            queue_.push(Event(kMouseHover, EventValue(Vec2<int>(x, y))));

            if (!mouse_button_pressed)
            {
                return true;
            }

            queue_.push(Event(kMouseMotion,
                              EventValue(Vec2<int>(event.motion.x - event.motion.xrel,
                                                   event.motion.y - event.motion.yrel),
                                         Vec2<int>(event.motion.xrel, event.motion.yrel))));
            break;
        }
        default:
        {
            return false;
        }
    }

    return true;
}