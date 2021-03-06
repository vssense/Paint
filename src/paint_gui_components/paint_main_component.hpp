#ifndef _PAINT_MAIN_COMPONENT_HPP_INCLUDED
#define _PAINT_MAIN_COMPONENT_HPP_INCLUDED

#include <dlfcn.h>

#include "../graphics/texture_manager.hpp" 
#include "../gui_system/gui_component.hpp"
#include "../gui_system/button.hpp"
#include "../gui_system/drop_down_list.hpp"
#include "../../plugins/plugin.hpp"

const Color kBorderColor = kBlack;
const Color kTitleColor  = kLightPurple;

const int kTitleButtonsWidth = 90;
const int kTitleWidth        = 30;

const Rectangle kDefaultCanvasPlacement{200, 200, 500, 500};
const Rectangle kDefaultPalettePlacement{200, 100, 100, 200};

class PaintMainComponent : public GUIComponent
{
public:
    PaintMainComponent(Texture* texture);
};

#endif /* _PAINT_MAIN_COMPONENT_HPP_INCLUDED */