#ifndef _BRUSH_COMMANDS_HPP_INCLUDED
#define _BRUSH_COMMANDS_HPP_INCLUDED

#include "../gui_component_system/gui_component_commands.hpp"
#include "../gui_component_system/gui_component_system.hpp"
#include "../gui_component_system/gui_component.hpp"

class SquareOnEvent : public IOnMouseEventCommand
{
public:
    SquareOnEvent(GUIComponentSystem* system, uint32_t color) : system_(system), color_(color) {}

    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
    {
        if (event.GetType() == kMouseButtonPress)
        {
            system_->GetBrush().SetColor(color_);
        }

        return true;
    }
private:
    GUIComponentSystem* system_;
    uint32_t color_;
};

// class YellowSquareOnEvent : public IOnMouseEventCommand
// {
// public:
//     YellowSquareOnEvent(GUIComponentSystem* system) : system_(system) {}

//     virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
//     {
//         if (event.GetType() == kMouseButtonPress)
//         {
//             system_->GetBrush().SetColor(kYellow);
//         }

//         return true;
//     }
// private:
//     GUIComponentSystem* system_;
// };

#endif /* _BRUSH_COMMANDS_HPP_INCLUDED */