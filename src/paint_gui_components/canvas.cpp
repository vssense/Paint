#include "canvas.hpp"
#include "../gui_system/button.hpp"

class CanvasClose : public ICommand
{
public:
    CanvasClose(CanvasComponent* canvas) : canvas_(canvas) {}

    virtual void Execute() override
    {
        EventManager::GetInstance()->PushEvent(Event(kCanvasClose, EventValue(canvas_)));
    }

private:
    CanvasComponent* canvas_;
};

class CanvasTitle : public GUIComponent
{
public:
    CanvasTitle(const Rectangle& placement, CanvasComponent* canvas) :
        GUIComponent(new Texture(placement.w, placement.h, kTitleColor), placement), canvas_(canvas)
    {
        Attach(new Border(kBorderColor, placement_));
        Attach(new Button(Rectangle{placement.w - kTitleWidth, 0, kTitleWidth, kTitleWidth},
                          new CanvasClose(canvas_), new Texture("img/close.bmp"),
                          new Texture("img/close2.bmp")));
    }

private:
    CanvasComponent* canvas_;
};

CanvasComponent::CanvasComponent(const Rectangle& placement) : GUIComponent(nullptr, placement)
{
    Attach(new CanvasTitle(Rectangle{0, 0, placement_.w, kTitleWidth}, this));
    Attach(new Border(kBorderColor, Rectangle{0, 0, placement_.w, placement.h}));
}
