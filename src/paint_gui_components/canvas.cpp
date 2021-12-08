#include "canvas.hpp"
#include "../gui_system/button.hpp"
#include "../gui_system/slider.hpp"
#include "../api/api_texture.hpp"

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
    AddBorder(kBorderColor);
    Attach(new Button(Rectangle{placement.w - kTitleWidth, 0, kTitleWidth, kTitleWidth},
                      new ComponentClose(canvas_), new Texture("img/close.bmp"),
                      nullptr, new Texture("img/close2.bmp")));

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

class Canvas;

class CanvasHorizontalSliderCallback : public ISliderResponse
{
public:
    CanvasHorizontalSliderCallback(Canvas* canvas) : canvas_(canvas) {}
    virtual void Respond(float old_value, float current_value) override;

private:
    Canvas* canvas_;
};

class CanvasVerticalSliderCallback : public ISliderResponse
{
public:
    CanvasVerticalSliderCallback(Canvas* canvas) : canvas_(canvas) {}
    virtual void Respond(float old_value, float current_value) override;

private:
    Canvas* canvas_;
};

class Canvas : public GUIComponent
{
public:
    Canvas(const Rectangle& placement, Vec2<int> max_size = Vec2<int>(kWindowWidth, kWindowHeight)) :
        GUIComponent(new Texture(max_size.x, max_size.y, kWhite), placement),
        tool_texture_(texture_),
        shown_part_{0, 0, placement.w, placement.h},
        max_size_(max_size)
    {
        Attach(new HorizontalSlider(Rectangle{0, placement_.h, placement_.w, 30},
                                    new Texture(placement_.w, 30, kWhite), new CanvasHorizontalSliderCallback(this)));
        Attach(new VerticalSlider  (Rectangle{placement_.w, 0, 30, placement_.h},
                                    new Texture(30, placement_.h, kWhite), new CanvasVerticalSliderCallback(this)));

    }

    virtual void Render() override;

    virtual bool ProcessMouseEvent   (const Event& event) override;
    virtual bool ProcessListenerEvent(const Event& event) override;

    void SetOrigin(Vec2<int> origin);
    void SetXOrigin(int origin_x);
    void SetYOrigin(int origin_y);
    const Rectangle& GetShownPart() const;
    const Vec2<int>& GetMaxSize() const;

private:
    APITexture tool_texture_;
    Rectangle shown_part_;

    Vec2<int> max_size_;
};

void Canvas::Render()
{
    Renderer::GetInstance()->CopyTexture(texture_, shown_part_, placement_);

    for (auto it = children_.end(); it != children_.begin();)
    {
        --it;
        (*it)->Render();
    }
}

void CanvasHorizontalSliderCallback::Respond(float old_value, float current_value)
{
    int max_size = canvas_->GetMaxSize().x;
    int shown_part_size = canvas_->GetShownPart().w;
    canvas_->SetXOrigin(current_value * (max_size - shown_part_size));
}

void CanvasVerticalSliderCallback::Respond(float old_value, float current_value)
{
    int max_size = canvas_->GetMaxSize().y;
    int shown_part_size = canvas_->GetShownPart().h;
    canvas_->SetYOrigin(current_value * (max_size - shown_part_size));
}

void Canvas::SetOrigin(Vec2<int> origin)
{
    SetXOrigin(origin.x);
    SetYOrigin(origin.y);
}

void Canvas::SetXOrigin(int origin_x)
{
    shown_part_.x0 = origin_x;

    shown_part_.x0 = std::max(0, shown_part_.x0);
    shown_part_.x0 = std::min(max_size_.x - shown_part_.w, shown_part_.x0);
}

void Canvas::SetYOrigin(int origin_y)
{
    shown_part_.y0 = origin_y;
    
    shown_part_.y0 = std::max(0, shown_part_.y0);
    shown_part_.y0 = std::min(max_size_.y - shown_part_.h, shown_part_.y0);
}

const Rectangle& Canvas::GetShownPart() const
{
    return shown_part_;
}

const Vec2<int>& Canvas::GetMaxSize() const
{
    return max_size_;
}

bool Canvas::ProcessListenerEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseMotion:
        {
            Vec2<int> start = event.GetValue().mouse.coordinates - placement_.Start();
            start += shown_part_.Start();

            ITool* active_tool = Manager<ITool>::GetInstance()->GetActive();
            active_tool->Action(&tool_texture_, start.x, start.y,
                                event.GetValue().mouse.d.x,
                                event.GetValue().mouse.d.y);
            break;
        }
        case kMouseButtonRelease:
        {
            Vec2<int> coordinates = event.GetValue().mouse.coordinates - placement_.Start();
            coordinates += shown_part_.Start();

            ITool* active_tool = Manager<ITool>::GetInstance()->GetActive();

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
            coordinates += shown_part_.Start();

            ITool* active_tool = Manager<ITool>::GetInstance()->GetActive();

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

    AddBorder(kBorderColor);
}

void CanvasComponent::AddBorder(Color color, int rounding_size)
{
    border_ = new Border(Vec2<int>(placement_.w, placement_.h), color, rounding_size);
    border_->SetParent(this);
}
