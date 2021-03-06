#ifndef _CANVAS_HPP_INCLUDED
#define _CANVAS_HPP_INCLUDED

#include "../gui_system/gui_component.hpp"
#include "../paint_gui_system/paint_gui_system.hpp"
#include "../instruments/instrument_manager.hpp"
#include "../instruments/brush.hpp"
#include "paint_main_component.hpp"

class CanvasComponent : public GUIComponent
{
public:
    CanvasComponent(const Rectangle& placement);

    virtual void AddBorder(Color color, int rounding_size = kDefaultRoundingSize) override;
};

#endif /* _CANVAS_HPP_INCLUDED */
