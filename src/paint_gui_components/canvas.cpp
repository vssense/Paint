#include "canvas.hpp"
#include "../gui_system/button.hpp"
#include "../tool_manager/tool_texture.hpp"

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
            system_->Unsubscribe(kMouseButtonRelease);
            system_->Unsubscribe(kMouseMotion);
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
        GUIComponent(new Texture(placement.w, placement.h, kWhite), placement),
        tool_texture_(texture_) {}

    virtual bool ProcessMouseEvent   (const Event& event) override;
    virtual bool ProcessListenerEvent(const Event& event) override;

private:
    ToolTexture tool_texture_;
};

bool Canvas::ProcessListenerEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseMotion:
        {
            Vec2<int> start = event.GetValue().mouse.coordinates - placement_.Start();

            ITool* active_tool = ToolManager::GetInstance()->GetActiveTool();
            active_tool->Action(&tool_texture_, start.x, start.y,
                                event.GetValue().mouse.d.x,
                                event.GetValue().mouse.d.y);
            break;
        }
        case kMouseButtonRelease:
        {
            Vec2<int> coordinates = event.GetValue().mouse.coordinates - placement_.Start();

            ITool* active_tool = ToolManager::GetInstance()->GetActiveTool();

            active_tool->ActionEnd(&tool_texture_, coordinates.x, coordinates.y);

            system_->Unsubscribe(kMouseMotion);
            system_->Unsubscribe(kMouseButtonRelease);
            break;
        }
        default:
        {
            break;
        }
    }

    return true;
}

bool Canvas::ProcessMouseEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonPress:
        {
            Vec2<int> coordinates = event.GetValue().mouse.coordinates - placement_.Start();

            ITool* active_tool = ToolManager::GetInstance()->GetActiveTool();

            active_tool->ActionBegin(&tool_texture_, coordinates.x, coordinates.y);

            system_->Subscribe(this, kMouseMotion);
            system_->Subscribe(this, kMouseButtonRelease);
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

    Attach(new Canvas(Rectangle{0, kTitleWidth, placement_.w, placement_.h - kTitleWidth}));

    Attach(new Border(kBorderColor, Rectangle{0, 0, placement_.w, placement.h}));
}
