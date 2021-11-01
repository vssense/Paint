#ifndef _CANVAS_COMMANDS_HPP_INCLUDED
#define _CANVAS_COMMANDS_HPP_INCLUDED

#include "../gui_component_system/gui_component_commands.hpp"
#include "../gui_component_system/gui_component.hpp"

const Rectangle kDefaultCanvasPlacement{200, 200, 400, 400}; 

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
    SceneOnMouseEvent(Texture* texture) : texture_(texture) {}
    virtual bool Execute(const Event& event, Vec2<uint32_t> origin) override
    {
        switch (event.GetType())
        {
            case kMouseButtonPress:
            case kMouseButtonRelease:
            {
                Renderer* renderer = component_->GetRenderer();
                renderer->SetRenderTarget(texture_);
                renderer->SetColor(kYellow);
                renderer->DrawCircle(event.GetValue().coordinates - origin, 10);
                renderer->SetRenderTarget(nullptr);
                break;
            }
            case kMouseMotion:
            {
                Renderer* renderer = component_->GetRenderer();
                renderer->SetRenderTarget(texture_);
                renderer->SetColor(kYellow);

                Vec2<int> end_line(event.GetValue().motion.start.x - origin.x + event.GetValue().motion.d.x,
                                   event.GetValue().motion.start.y - origin.y + event.GetValue().motion.d.y);
                
                end_line.x = Max(end_line.x, 0);
                end_line.y = Max(end_line.y, 0);

                renderer->DrawLine(event.GetValue().motion.start.x - origin.x,
                                   event.GetValue().motion.start.y - origin.y,
                                   end_line.x, end_line.y, 20);
                renderer->SetRenderTarget(nullptr);
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
};


#endif /* _CANVAS_COMMANDS_HPP_INCLUDED */