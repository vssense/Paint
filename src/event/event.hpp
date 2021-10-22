#ifndef _EVENT_HPP_INCLUDED
#define _EVENT_HPP_INCLUDED

#include <SDL2/SDL.h>
#include "../math/vector2.hpp"

enum EventType
{
    Quit,
    KeyDown,
    MouseClick
};

union EventValue
{
    int scancode;
    Vec2<uint32_t> coordinates;

    EventValue() {}
    ~EventValue() {}
};

class Event
{
public:
    Event() {}
    ~Event() {}
    bool PollEvent();
    EventType GetType() { return type_; }
    const EventValue& GetValue() { return value_; }
private:
    EventType type_;
    EventValue value_;
};

#endif /* _EVENT_HPP_INCLUDED */