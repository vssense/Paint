#ifndef _EVENT_HPP_INCLUDED
#define _EVENT_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <queue>
#include "../math/vector2.hpp"

class GUIComponent;

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
    kCanvasClose,

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
    GUIComponent* canvas;

    EventValue() {}
    EventValue(int scancode) : scancode(scancode) {}
    EventValue(Vec2<uint32_t> coordinates) : coordinates(coordinates) {}
    EventValue(const MotionData& motion) : motion(motion) {}
    EventValue(GUIComponent* canvas) : canvas(canvas) {}
    ~EventValue() {}
};

class Event
{
public:
    Event() {}
    Event(EventType type) : type_(type) {}
    Event(EventType type, const EventValue& value) : type_(type), value_(value) {}
    ~Event() {}
    bool PollEvent();
    EventType GetType() const;
    const EventValue& GetValue() const;

private:
    EventType type_;
    EventValue value_;
};

class EventManager
{
private:
    EventManager();
public:
    static EventManager* GetInstance();

    bool PollEvent(Event* event);
    void PushEvent(const Event& event);

private:
    bool PollSDLEvent();

    std::queue<Event> queue_;
    static EventManager* instance_;
};

#endif /* _EVENT_HPP_INCLUDED */