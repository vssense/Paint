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
    kComponentClose,
    kRightButtonClick,

    kEventsCount
};

struct MouseData
{
    Vec2<int> coordinates;
    Vec2<int> d;

    MouseData(Vec2<int> coordinates) :
        coordinates(coordinates), d(0, 0) {}
    MouseData(Vec2<int> coordinates, Vec2<int> d) :
        coordinates(coordinates), d(d) {}
};

union EventValue
{
    int scancode;
    MouseData mouse;
    GUIComponent* component;

    EventValue() {}
    EventValue(int scancode) : scancode(scancode) {}
    EventValue(Vec2<int> coordinates) : mouse(coordinates) {}
    EventValue(Vec2<int> coordinates, Vec2<int> d) :
               mouse(coordinates, d) {}
    EventValue(GUIComponent* component) : component(component) {}
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
