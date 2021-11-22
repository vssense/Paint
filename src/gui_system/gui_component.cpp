#include "gui_component.hpp"
#include "gui_system.hpp"

GUIComponent::GUIComponent(Texture* texture, const Rectangle& relative_placement) :
    texture_(texture), placement_(relative_placement), parent_(nullptr), system_(nullptr) {}

GUIComponent::~GUIComponent()
{
    if (texture_ != nullptr)
    {
        delete texture_;
    }

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        delete (*it);
    }
}

bool GUIComponent::HitTest(Vec2<int> coordinates) const
{
    return IsInsideRectangle(placement_, coordinates);
}

bool GUIComponent::OnMouseEvent(const Event& event)
{
    if (!HitTest(event.GetValue().mouse.coordinates))
    {
        return false;
    }

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        if ((*it)->OnMouseEvent(event))
        {
            if (event.GetType() == kMouseButtonPress)
            {
                GUIComponent* processed_event = *it;
                children_.erase(it);
                children_.push_front(processed_event);
            }
            
            return true;
        }
    }

    return ProcessMouseEvent(event);
}

bool GUIComponent::ProcessMouseEvent(const Event& event)
{
    return true;
}

bool GUIComponent::ProcessListenerEvent(const Event& event)
{
    return ProcessMouseEvent(event);
}

void GUIComponent::Move(Vec2<int> d)
{
    placement_.x0 += d.x;
    placement_.y0 += d.y;

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        (*it)->Move(d);
    }
}

void GUIComponent::Render()
{
    if (texture_ != nullptr)
    {
        Renderer::GetInstance()->CopyTexture(texture_, placement_);
    }

    for (auto it = children_.end(); it != children_.begin();)
    {
        --it;
        (*it)->Render();
    }
}

void GUIComponent::Attach(GUIComponent* component)
{
    assert(component);

    children_.push_front(component);
    component->parent_ = this;
    component->SetGUISystem(system_);
    component->Move(Vec2<int32_t>(placement_.x0, placement_.y0));
}

void GUIComponent::Detach(GUIComponent* component)
{
    assert(component);

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        if (*it == component)
        {
            children_.erase(it);
            break;
        }
    }    
}

void GUIComponent::SetGUISystem(GUISystem* system)
{
    system_ = system;

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        (*it)->SetGUISystem(system);
    }
}

GUIComponent* GUIComponent::GetParent() const
{
    return parent_;
}

GUISystem* GUIComponent::GetSystem()
{
    return system_;
}


Bagel::Bagel(Vec2<int> center, uint32_t r1, uint32_t r2, Color color) :
    GUIComponent(new Texture(2 * r1, 2 * r1),
    Rectangle{center.x - static_cast<int>(r1),
              center.y - static_cast<int>(r1),
              2 * static_cast<int>(r1),
              2 * static_cast<int>(r1)}),
    center_(center), r1_(r1), r2_(r2)
{
    Renderer* renderer = Renderer::GetInstance();
    renderer->SetColor(color);
    renderer->DrawCircle(texture_, Vec2<int>(r1, r1), r1);
    renderer->SetColor(kTransparent);
    renderer->DrawCircle(texture_, Vec2<int>(r1, r1), r2);
}

bool Bagel::ProcessListenerEvent(const Event& event)
{
    return ProcessMouseEvent(event);
}

bool Bagel::ProcessMouseEvent(const Event& event)
{
    switch (event.GetType())
    {
        case kMouseButtonPress:
        {
            system_->Subscribe(this, kMouseHover);
            system_->Subscribe(this, kMouseMotion);
            system_->Subscribe(this, kMouseButtonRelease);            
            break;
        }
        case kMouseButtonRelease:
        {
            system_->UnSubscribe(kMouseHover);
            system_->UnSubscribe(kMouseMotion);
            system_->UnSubscribe(kMouseButtonRelease);            
            break;
        }
        case kMouseMotion:
        {
            Move(event.GetValue().mouse.d);
            break;
        }
        default:
        {
            break;
        }
        
    }

    return true;
}

bool IsInsideCircle(Vec2<int> center, uint32_t radius, Vec2<int> point)
{
    Vec2<int> r = center - point;
    return r.GetLength() <= static_cast<float>(radius);
}

bool Bagel::HitTest(Vec2<int> coordinates) const
{
    return IsInsideCircle(center_, r1_, coordinates) &&
          !IsInsideCircle(center_, r2_, coordinates);
}

void Bagel::Move(Vec2<int> d)
{
    placement_.x0 += d.x;
    placement_.y0 += d.y;
    center_ += d;

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        (*it)->Move(d);
    }
}


