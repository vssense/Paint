#ifndef _GUICOMPONENT_COMMANDS_HPP_INCLUDED
#define _GUICOMPONENT_COMMANDS_HPP_INCLUDED

#include "../math/vector2.hpp"
#include "../math/rectangle.hpp"
#include "../event/event.hpp"

class IHitTestCommand
{
public:
    virtual ~IHitTestCommand() {}

    virtual bool Execute(Vec2<uint32_t> click) const = 0;

    virtual const Rectangle& GetPlaceToRender() const = 0;
};

class IOnMouseEventCommand
{
public:
    virtual ~IOnMouseEventCommand() {}

    virtual bool Execute(const Event& event) = 0;
};

#endif /* _GUICOMPONENT_COMMANDS_HPP_INCLUDED */