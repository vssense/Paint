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
