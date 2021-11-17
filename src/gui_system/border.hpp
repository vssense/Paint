#ifndef _BORDER_HPP_INCLUDED
#define _BORDER_HPP_INCLUDED

#include "gui_component.hpp"

class Border : public GUIComponent
{
public:
    Border(Color color, const Rectangle& placement) :
        GUIComponent(new Texture(placement.w, placement.h, kTransparent, color), placement) {}

    virtual ~Border() override {}

    virtual bool ProcessMouseEvent(const Event& event)
    {
        return false;
    }
};

#endif /* _BORDER_HPP_INCLUDED */