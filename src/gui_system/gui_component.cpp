#include "gui_component.hpp"

GUIComponent::GUIComponent(Texture* texture, const Rectangle& relative_placement) :
    texture_(texture), placement_(relative_placement), parent_(nullptr)
{
    is_deleted_ = false;
}

GUIComponent::~GUIComponent()
{
    assert(texture_);
    delete texture_;

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        delete (*it);
    }
}

bool GUIComponent::HitTest(Vec2<uint32_t> coordinates) const
{
    return IsInsideRectangle(placement_, coordinates);
}

bool GUIComponent::OnMouseEvent(Vec2<uint32_t> coordinates, const Event& event)
{
    if (!HitTest(coordinates))
    {
        return false;
    }

    for (auto it = children_.begin(); it != children_.end(); ++it)
    {
        if ((*it)->OnMouseEvent(coordinates, event))
        {
            GUIComponent* processed_event = *it;
            children_.erase(it);
            if (processed_event->IsDeleted())
            {
                delete processed_event;
            }
            else
            {
                Attach(processed_event);
            }

            return true;
        }
    }

    return ProcessMouseEvent(event);
}

bool GUIComponent::ProcessMouseEvent(const Event& event)
{
    printf("Process event!\n");
    return true;
}

void GUIComponent::Move(Vec2<int32_t> d)
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
    Renderer* renderer = Renderer::GetInstance();
    assert(renderer);

    renderer->CopyTexture(texture_, placement_);

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
    component->Move(Vec2<int32_t>(placement_.x0, placement_.y0));
}

void GUIComponent::Delete()
{
    is_deleted_ = true;
}

bool GUIComponent::IsDeleted() const
{
    return is_deleted_;
}
