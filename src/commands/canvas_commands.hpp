#ifndef _CANVAS_COMMANDS_HPP_INCLUDED
#define _CANVAS_COMMANDS_HPP_INCLUDED

#include "../gui_component_system/gui_component_commands.hpp"
#include "../gui_component_system/gui_component.hpp"

const Rectangle kDefaultCanvasPlacement{200, 200, 400, 400}; 

class CanvasTitleOnMouseEvent : public IOnMouseEventCommand
{
public:
    CanvasTitleOnMouseEvent(GUIComponent* canvas) : canvas_(canvas) {}

    virtual bool Execute(const Event& event) override
    {
        if (event.GetType() == kMouseMotion)
        {
            canvas_->Move(event.GetValue().motion.d);
        }

        return true;
    }

private:
    GUIComponent* canvas_;
};

#endif /* _CANVAS_COMMANDS_HPP_INCLUDED */