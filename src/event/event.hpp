#ifndef _EVENT_HPP_INCLUDED
#define _EVENT_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <queue>
#include "../math/vector2.hpp"

const int kQScancode = 20;
const int kPlusScancode = 46;
const int kMinusScancode = 45;

enum EventType
{
    kQuit,
    kKeyDown,
    kMouseHover,
    kMouseButtonPress,
    kMouseButtonRelease,
    kMouseMotion,

    kEventsCount
};

struct MotionData
{
    Vec2<uint32_t> start;
    Vec2<int32_t> d;
};

union EventValue
{
    int scancode;
    Vec2<uint32_t> coordinates;
    MotionData motion;

    EventValue() {}
    ~EventValue() {}
};

class Event
{
public:
    Event() {}
    ~Event() {}
    bool PollEvent();
    EventType GetType() const { return type_; }
    const EventValue& GetValue() const { return value_; }

private:
    bool PollSDLEvent();
    
    EventType type_;
    EventValue value_;
    static std::queue<Event> queue_;
};

#endif /* _EVENT_HPP_INCLUDED */