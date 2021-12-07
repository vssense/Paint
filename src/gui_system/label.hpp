#ifndef _LABEL_HPP_INCLUDED
#define _LABEL_HPP_INCLUDED

#include "gui_component.hpp"

class Label : public GUIComponent
{
public:
    Label(const Rectangle& placement, const char* text, Color text_color);

    void SetText(const char* text);

    void Destroy();

private:
    Color text_color_;
};

#endif /* _LABEL_HPP_INCLUDED */