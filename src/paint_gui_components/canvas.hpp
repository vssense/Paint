#ifndef _CANVAS_HPP_INCLUDED
#define _CANVAS_HPP_INCLUDED

#include "../gui_system/gui_component.hpp"
#include "../paint_gui_system/paint_gui_system.hpp"
#include "../tool_manager/tool_manager.hpp"
#include "../tool_manager/brush.hpp"
#include "paint_main_component.hpp"

class CanvasComponent : public GUIComponent
{
public:
    CanvasComponent(const Rectangle& placement);
};

#endif /* _CANVAS_HPP_INCLUDED */
