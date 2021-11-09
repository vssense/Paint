#ifndef _CANVAS_COMMANDS_HPP_INCLUDED
#define _CANVAS_COMMANDS_HPP_INCLUDED

#include "../gui_system/gui_component_commands.hpp"
#include "../gui_system/gui_component.hpp"
#include "../math/swap.hpp"

const Rectangle kDefaultCanvasPlacement{200, 200, 500, 500}; 

class CanvasTitleOnMouseEvent : public IOnMouseEventCommand
{
public:
    CanvasTitleOnMouseEvent(GUIComponent* canvas) : canvas_(canvas) {}

    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
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

class SceneOnMouseEvent : public IOnMouseEventCommand
{
public:
    SceneOnMouseEvent(Texture* texture, PaintGUISystem* system) : texture_(texture), system_(system) {}
    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
    {
        switch (event.GetType())
        {
            case kMouseButtonPress:
            case kMouseButtonRelease:
            {
                Renderer* renderer = Renderer::GetInstance();
                renderer->SetColor(system_->GetBrush().GetColor());
                renderer->DrawCircle(texture_, event.GetValue().coordinates - origin, system_->GetBrush().GetThickness());
                break;
            }
            case kMouseMotion:
            {
                Renderer* renderer = Renderer::GetInstance();
                renderer->SetColor(system_->GetBrush().GetColor());

                Vec2<int> end_line(event.GetValue().motion.start.x - origin.x + event.GetValue().motion.d.x,
                                   event.GetValue().motion.start.y - origin.y + event.GetValue().motion.d.y);
                
                end_line.x = Max(end_line.x, 0);
                end_line.y = Max(end_line.y, 0);

                renderer->DrawLine(texture_, event.GetValue().motion.start.x - origin.x,
                                             event.GetValue().motion.start.y - origin.y,
                                             end_line.x, end_line.y,
                                             system_->GetBrush().GetThickness());
                break;
            }
            default:
            {
                break;
            }
        }

        return true;
    }
private:
    Texture* texture_;
    PaintGUISystem* system_;
};


#endif /* _CANVAS_COMMANDS_HPP_INCLUDED */