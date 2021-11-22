#include "canvas.hpp"
#include "../gui_system/button.hpp"
#include "../paint_gui_system/paint_gui_system.hpp"

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
    CanvasTitle(const Rectangle& placement, CanvasComponent* canvas);
    virtual bool ProcessMouseEvent   (const Event& event) override;
    virtual bool ProcessListenerEvent(const Event& event) override;

private:
    CanvasComponent* canvas_;
};

CanvasTitle::CanvasTitle(const Rectangle& placement, CanvasComponent* canvas) :
    GUIComponent(new Texture(placement.w, placement.h, kTitleColor), placement), canvas_(canvas)
{
    Attach(new Border(kBorderColor, placement_));
    Attach(new Button(Rectangle{placement.w - kTitleWidth, 0, kTitleWidth, kTitleWidth},
                      new CanvasClose(canvas_), new Texture("img/close.bmp"),
                      new Texture("img/close2.bmp")));

    Attach(new TextIcon(placement, "Canvas", kBlack));
}

bool CanvasTitle::ProcessListenerEvent(const Event& event)
{
    if (event.GetType() == kMouseMotion)
    {
        parent_->Move(event.GetValue().mouse.d);
        return true;
    }

    return ProcessMouseEvent(event);
}

bool CanvasTitle::ProcessMouseEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonPress:
        {
            system_->Subscribe(this, kMouseButtonRelease);
            system_->Subscribe(this, kMouseMotion);
            break;
        }
        case kMouseButtonRelease:
        {
            system_->UnSubscribe(kMouseButtonRelease);
            system_->UnSubscribe(kMouseMotion);
            break;
        }
        default:
        {
            break;
        }
    }

    return true;
}

class Canvas : public GUIComponent
{
public:
    Canvas(const Rectangle& placement) :
        GUIComponent(new Texture(placement.w, placement.h, kWhite), placement) {}

    virtual bool ProcessMouseEvent   (const Event& event) override;
    virtual bool ProcessListenerEvent(const Event& event) override;
};

bool Canvas::ProcessListenerEvent(const Event& event)
{
    if (event.GetType() == kMouseMotion)
    {
        Vec2<int> start = event.GetValue().mouse.coordinates;
        start.x -= placement_.x0;
        start.y -= placement_.y0;

        Vec2<int> end = start + event.GetValue().mouse.d;
        Renderer::GetInstance()->SetColor(kRed);
        Renderer::GetInstance()->DrawLine(texture_, start.x, start.y, end.x, end.y, 13);
        
        return true;
    }

    return ProcessMouseEvent(event);
}

bool Canvas::ProcessMouseEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonPress:
        {
            system_->Subscribe(this, kMouseMotion);
            system_->Subscribe(this, kMouseButtonRelease);
            break;
        }
        case kMouseButtonRelease:
        {
            system_->UnSubscribe(kMouseMotion);
            system_->UnSubscribe(kMouseButtonRelease);
            break;
        }
        default:
        {
            break;
        }
    }

    return true;
}

CanvasComponent::CanvasComponent(const Rectangle& placement) : GUIComponent(nullptr, placement)
{
    Attach(new CanvasTitle(Rectangle{0, 0, placement_.w, kTitleWidth}, this));

    Attach(new Border(kBorderColor, Rectangle{0, 0, placement_.w, placement.h}));

    Attach(new Canvas(Rectangle{0, kTitleWidth, placement_.w, placement_.h - kTitleWidth}));
}