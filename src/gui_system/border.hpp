#ifndef _BORDER_HPP_INCLUDED
#define _BORDER_HPP_INCLUDED

#include "gui_component.hpp"

const float kPower = 4;

class Border : public GUIComponent
{
public:
    Border(Texture* to_border, Color color, int rounding_size = kDefaultRoundingSize);
    Border(Vec2<int> size, Color color, int rounding_size);


    virtual bool ProcessMouseEvent(const Event& event) override;
    virtual void Render() override;
};

#endif /* _BORDER_HPP_INCLUDED */
