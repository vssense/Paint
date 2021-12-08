#ifndef _LABEL_HPP_INCLUDED
#define _LABEL_HPP_INCLUDED

#include "gui_component.hpp"

class Label : public GUIComponent
{
public:
    Label(const Rectangle& placement, const char* text, Color text_color);

    void SetText(const char* text);
    virtual void Move(Vec2<int> d) override;

    void Destroy();

private:
    Color text_color_;

    Rectangle max_size_;
};

#endif /* _LABEL_HPP_INCLUDED */