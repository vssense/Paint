#ifndef _PAINT_GUI_SYSTEM_HPP_INCLUDED
#define _PAINT_GUI_SYSTEM_HPP_INCLUDED

#include "../gui_system/gui_system.hpp"
#include "../gui_system/button.hpp"
#include "brush.hpp"

class PaintGUISystem : public GUISystem
{
public:
    PaintGUISystem(Window* window, GUIComponent* root);
    virtual ~PaintGUISystem();

    Brush& GetBrush();
    void   SetBrush(const Brush& brush);

protected:
    Brush brush_;
};

#endif /* _PAINT_GUI_SYSTEM_HPP_INCLUDED */