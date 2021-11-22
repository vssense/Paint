#ifndef _PAINT_MAIN_COMPONENT_HPP_INCLUDED
#define _PAINT_MAIN_COMPONENT_HPP_INCLUDED

#include "../gui_system/gui_component.hpp"
#include "../gui_system/button.hpp"

const Color kBorderColor = kBlue;
const Color kTitleColor  = kLightPurple;

const int kTitleButtonsWidth = 90;
const int kTitleWidth        = 30;

const Rectangle kDefaultPlacement{200, 200, 400, 400};

class PaintMainComponent : public GUIComponent
{
public:
    PaintMainComponent(Texture* texture);
};

#endif /* _PAINT_MAIN_COMPONENT_HPP_INCLUDED */