#ifndef _CANVAS_HPP_INCLUDED
#define _CANVAS_HPP_INCLUDED

#include "../gui_system/gui_component.hpp"
#include "paint_main_component.hpp"

class CanvasComponent : public GUIComponent
{
public:
    CanvasComponent(const Rectangle& placement);
};

#endif /* _CANVAS_HPP_INCLUDED */